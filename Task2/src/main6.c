#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int pipefd[2];
    char buf;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int rc = fork();
    if (rc == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (rc == 0) {
        //child
        close(pipefd[1]);
        while (read(pipefd[0], &buf, 1) > 0)  //Чтение из потока
            printf("%c",buf);
        printf("\n");

        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {
        //parent
        close(pipefd[0]);
        write(pipefd[1], "Hello child", strlen("Hello child")); //Пишем впоток
        close(pipefd[1]);

        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    return 0;
}