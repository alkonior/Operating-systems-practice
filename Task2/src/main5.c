#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    int status;

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        //child process
        printf("child\n");
        fclose(STDOUT_FILENO);
        printf("child\n");
    } else {
        //parent process
        wait(&status);
        printf("parent begin\n");
        printf("parent wait end with %i\n",WEXITSTATUS(status));
    }
    return 0;
}