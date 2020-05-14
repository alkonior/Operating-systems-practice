#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <zconf.h>

typedef unsigned long long ull;

unsigned long long current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1e6 + t.tv_usec;
}

int main(int argv, const char** argc) {

    if (argv < 2)
    {
        printf("Error: expecting file name");
        exit(0);
    }
    const unsigned int n = 300000;
    ull start_time = 0;
    ull end_time = 0;
    char *buff = malloc(n);                   //buffer

    start_time = current_time();
    int f = creat(argc[1], S_IWRITE);    //create
    end_time = current_time();
    printf("Create: %llu\n\n",end_time - start_time);

    if (f < 0) {
        printf("Error in create\n");
    }

    start_time = current_time();
    int was_write = write(f, buff, n);          //write
    end_time = current_time();
    printf("Write: %llu\n\n",end_time - start_time);

    if (was_write != n) {
        printf("Error in write!\n");
    }

    start_time = current_time();
    fsync(f);                                   //fflush
    end_time = current_time();
    printf("Fflush: %llu\n\n",end_time - start_time);

    start_time = current_time();
    close(f);                                   //close
    end_time = current_time();
    printf("Close: %llu\n\n",end_time - start_time);

    start_time = current_time();
    remove(argc[0]);                    //delete
    end_time = current_time();
    printf("Fflush: %llu\n\n",end_time - start_time);

    free(buff); // освободили буфер
    return 0;
}