#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "queue/utils.h"
#include "queue/queue.h"

typedef struct {
    Shared * shared;
    int from;
    int to;
    int* complited;
} MyShared;


MyShared *make_myshared(int l, int from, int to, int* ar)
{
    MyShared *shared = check_malloc(sizeof(MyShared));
    shared->shared = make_shared(l);
    shared->from=from;
    shared->to=to;
    shared->complited=ar;
    return shared;
}

pthread_t make_mythread(void *(*entry)(void *), MyShared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

void *my_producer_entry(void *arg)
{
    int i;
    MyShared *shared = (MyShared *) arg;
    for (i=shared->from; i<shared->to; i++) {
        queue_push(shared->shared->queue, i);
    }
    pthread_exit(NULL);
}

void *my_consumer_entry(void *arg)
{
    int i;
    int item;
    MyShared *shared = (MyShared *) arg;

    for (i=shared->from; i<shared->to; i++) {
        item = queue_pop(shared->shared->queue);
        shared->complited[item]++;
    }
    pthread_exit(NULL);
}


int main() {
    printf("Starting tests!\n\n");
    printf("Thread test:\n");
    for (int m = 0; m < 100; ++m) {


        int nums[1000];

        for (int j = 0; j < 1000; ++j) {
            nums[j]=0;
        }

        pthread_t prod[100];
        pthread_t cons[10];

        MyShared *shared = make_myshared(1001,0,10,nums);

        MyShared prod_shared[100];

        for (int l = 0; l < 100; ++l) {
            prod_shared[l].shared=shared->shared;
            prod_shared[l].from=l*10;
            prod_shared[l].to=(l+1)*10;
        }

        for (int i = 0; i < 100; ++i) {
            prod[i] = make_mythread(my_producer_entry, &prod_shared[i]);
        }

        MyShared cons_shared[10];

        for (int l = 0; l < 10; ++l) {
            cons_shared[l].shared=shared->shared;
            cons_shared[l].from=l*100;
            cons_shared[l].to=l*100+100;
            cons_shared[l].complited=nums;
        }

        for (int i = 0; i < 100; i++) {
            join_thread(prod[i]);
        }

        for (int i = 0; i < 10; ++i) {
            cons[i] = make_mythread(my_consumer_entry, &cons_shared[i]);
        }

        for (int i = 0; i < 10; i++) {
            join_thread(cons[i]);
        }

        for (int k = 0; k < 1000; ++k) {
            if (nums[k]!=1)
            {
                printf("Test failed\n");
                return 0;
            }
        }
    }
    printf("Test complited\n\n");


    printf("Condition variable test:\n");
    for (int m = 0; m < 100; ++m) {


        int nums[1000];

        for (int j = 0; j < 1000; ++j) {
            nums[j]=0;
        }

        pthread_t prod[100];
        pthread_t cons[10];

        MyShared *shared = make_myshared(300,0,10,nums);

        MyShared prod_shared[100];

        for (int l = 0; l < 100; ++l) {
            prod_shared[l].shared=shared->shared;
            prod_shared[l].from=l*10;
            prod_shared[l].to=(l+1)*10;
        }

        for (int i = 0; i < 100; ++i) {
            prod[i] = make_mythread(my_producer_entry, &prod_shared[i]);
        }

        MyShared cons_shared[10];

        for (int l = 0; l < 10; ++l) {
            cons_shared[l].shared=shared->shared;
            cons_shared[l].from=l*100;
            cons_shared[l].to=l*100+100;
            cons_shared[l].complited=nums;
        }

        for (int i = 0; i < 10; ++i) {
            cons[i] = make_mythread(my_consumer_entry, &cons_shared[i]);
        }

        for (int i = 0; i < 100; i++) {
            join_thread(prod[i]);
        }


        for (int i = 0; i < 10; i++) {
            join_thread(cons[i]);
        }

        for (int k = 0; k < 1000; ++k) {
            if (nums[k]!=1)
            {
                printf("Test failed\n");
                return 0;
            }
        }
    }
    printf("Test complited\n");

    return 0;
}
