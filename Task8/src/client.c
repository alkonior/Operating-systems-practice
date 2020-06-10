#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

#define MAXBUF 1023

int main() {
    char buff[MAXBUF + 1];
    int sockfd;
    fd_set all_set; //file descriptors
    struct sockaddr_in servaddr, cli;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(9037);

    if ((connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1) {
        printf("Connection with the server failed...\n");
        exit(EXIT_FAILURE);
    }

    int maxfd = sockfd + 1;
    FD_ZERO(&all_set);
    FD_SET(STDIN_FILENO, &all_set);
    FD_SET(sockfd, &all_set);

    struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

    int server_exist=1;

    puts("Enter message: ");
    while (server_exist){
        fd_set rset = all_set;
        select(maxfd, &rset, NULL, NULL, &tv);

        if(FD_ISSET(STDIN_FILENO, &rset)){ //stdin
            bzero(buff, sizeof(buff));
            int bytes = read(STDIN_FILENO, buff, MAXBUF);
            buff[bytes - 1] = '\0';
            if(send(sockfd, buff, bytes + 1, 0) < 0)
            {
                perror("Client send failed");
                exit(EXIT_FAILURE);
            }
        }

        if(FD_ISSET(sockfd, &rset)){
            bzero(buff, sizeof(buff));
            int byte;
            if((byte=recv(sockfd, buff, MAXBUF + 1, 0))< 0){ //server
                perror("Client recv failed");
                exit(EXIT_FAILURE);
            }else
            if (byte==0)
            {
                printf("Server was destroyed");
                server_exist=0;
            } else {
                printf("From server:\n%s\n", buff);
                //buff[0] = '\0';
                puts("Enter message:");
            }
        }
    }
    close(sockfd);
    return EXIT_SUCCESS;
}