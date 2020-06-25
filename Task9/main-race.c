#include <stdio.h>

#include "mythreads.h"

int balance = 0;

void* worker(void* arg) {
    for (int i = 0; i < 10000; ++i) {
        balance++; // unprotected access
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    for (int i = 0; i < 10000; ++i) {
        balance++; // unprotected access
    }
    Pthread_join(p, NULL);
    printf("%i\n",balance);
    return 0;
}
