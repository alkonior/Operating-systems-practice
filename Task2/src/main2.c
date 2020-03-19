#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int
main(int argc, char *argv[])
{
    int parent = getpid();
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello\n");
        kill(parent,1);         // Отправляем сигнал с дочернего процесса
    } else {
        int x = 0;
        // parent
        int i = gsignal(rc);         //Ждем сигрнал от дочернего процесса
        printf("goodbye\n");
    }
    return 0;
}