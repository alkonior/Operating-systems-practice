#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <aio.h>
#include <asm/errno.h>

#define PORT 9037
#define SA struct sockaddr
#define MAXLINE 1024
#define MAXCACHE 10
#define MAX_CBS_COUNT (64)

struct aiocb cbs[MAX_CBS_COUNT];
size_t cbs_count = 0;

int master_socket = 0; //основной сокет
int is_running = 1;

void free_files() {
    for (int i = 0; i < cbs_count; ++i) {
        while (aio_error(cbs + i) == EINPROGRESS) {
            // Wait.
        }
        free(cbs[i].aio_buf);
    }
    cbs_count = 0;
}

char * open_file(char *filename) {
    FILE* fd;
    char *buff;
    struct stat st;
    fd = fopen(filename, "r");
    if (fd == NULL) {
        perror("Can`t open file ");
        return "Error: Can`t open file ";
    }
    stat(filename, &st);
    if((buff=(char *) malloc(st.st_size))== NULL)
    {
        perror("Allocation fail");
        return "Error: Allocation fail ";
    }

    fread(buff,1, st.st_size,fd);

    fclose(fd);

    return buff;
}

void interrupt_signal(int signal) {
    is_running = 0;
    free_files();
    printf("Interrupt received: Server exit.\n");
    close(master_socket);
    exit(0);
}

const char* m_time = "time";
const char* m_read = "file";

int wait_request(int sockfd) {
    char buff[MAXLINE];
    int bytes;

    char* send ;
    bzero(buff, sizeof(buff));
    if ((bytes = recv(sockfd, buff, MAXLINE, 0)) > 0) {  //resieve
        printf("From client: %s\n", buff);

        if (strcmp(m_time, buff) == 0) { //time
            time_t now = time(0);
            char *time_str = ctime(&now);
            send = malloc((strlen(time_str)+1)*sizeof(char));
            strcpy(send,time_str);
            send[strlen(time_str)] = '\0';
        }

        if (strncmp(m_read, buff, 4) == 0 && strlen(buff) > 5) { //file + //
            char *str = (char *) malloc(1 + strlen(buff) - 2);
            strncpy(str, buff + 5, strlen(buff) - 5);
            send = open_file(str);
        }

        if (cbs_count==MAX_CBS_COUNT)
        {
            free_files();
        }

        {
            struct aiocb *aiocb = cbs + cbs_count++;
            memset(aiocb, 0, sizeof(struct aiocb));
            aiocb->aio_fildes = sockfd;
            aiocb->aio_buf = send;
            aiocb->aio_nbytes = strlen(send) - 1;
            if (aio_write(aiocb) == -1) {
                perror("aio_write");
                interrupt_signal(EXIT_FAILURE);
            }
        }
    }

    if (bytes < 0) {
        perror("Server recv error");
    }

    return bytes;
}



int main() {
    signal(SIGINT, interrupt_signal);

    fd_set master; //main FD
    struct sockaddr_in servaddr, cli;
    socklen_t len;
    int option = 1;



    FD_ZERO(&master);

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { //socket creation
        perror("Socket creation failed\n");
        exit(1);
    }

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) != 0) {
        perror("Socket setsockopt failed\n");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr)); // IP socket
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(master_socket, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        perror("Socket bind failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully binded..\n");

    if (listen(master_socket, 10) != 0) {  //listener
        perror("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Server listening..\n");

    FD_SET(master_socket, &master); //

    fd_set allset; //All socets for select
    FD_ZERO(&allset);

    while (is_running) {
        allset = master;
        if (select(FD_SETSIZE, &allset, NULL, NULL, NULL) == -1) {
            perror("Server select error\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < FD_SETSIZE; ++i) {

            if (!FD_ISSET(i, &allset)) {
                continue;
            }

            if (i == master_socket) //new client
            {
                len = sizeof(cli);
                int newfd;
                if ((newfd = accept(master_socket, (SA *) &cli, &len)) < 0) { //accept
                    perror("Server accept failed\n");
                    exit(EXIT_FAILURE);
                }

                fcntl(newfd, F_SETFL, O_NONBLOCK); //make socket ulockable

                FD_SET(newfd, &master); //Increase FD_MAX
                printf("New connection , socket fd is %d , ip is : %s , port : %d\n",
                       newfd, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

            } else {  //old client
                int response_code = wait_request(i);
                if (response_code > 0) {
                    continue;
                }

                if (response_code == 0) {   //client end
                    printf("Server: socket %d hung up\n", i);
                }
                close(i);
                FD_CLR(i, &master);
            }
        }
    }
}