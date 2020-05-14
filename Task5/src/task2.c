#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <zconf.h>

typedef unsigned long long ull;

const char *file = "bif.txt";

ull current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1e6 + t.tv_usec;
}

void a(const char* file, int num) { // часть А.
    char c = 'a';
    int f = creat(file, S_IWRITE);
    for (unsigned i = 0; i < num; i++) {
        write(f, &c, 1);             //write
    }
    close(f);
}

void b(const char* file, int num) { // часть B.
    char c = 'b';
    FILE *f = fopen(file, "w");
    for (unsigned i = 0; i < num; i++) {
        fwrite(&c, 1, 1, f);           //fwrite
        fflush(f);
    }
    //fflush(f);
    fclose(f);
}

int main(int argv, const char** argc) {

    if (argv < 2)
    {
        printf("Error: expecting file name");
        exit(0);
    }
    unsigned int n = 3;
    ull start_time = 0;
    ull end_time = 0;
    const char* file= "test.txt";

    for (int i = 0; i < 5; ++i) {

        start_time = current_time();
        a(file,n);
        end_time = current_time();
        printf("Write: %llu\n",end_time - start_time);



        start_time = current_time();
        b(file,n);
        end_time = current_time();
        printf("FWrite: %llu\nNum: %i\n\n",end_time - start_time,n);
        n = n*10;
    }
    return 0;
}