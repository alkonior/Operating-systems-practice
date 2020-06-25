#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "utils.h"

typedef struct {
    int *array;
    int length;
    int next_in;
    int next_out;
    Mutex *mutex;
    Cond *nonempty;
    Cond *nonfull;
} Queue;

typedef struct {
    Queue *queue;
} Shared;

Queue *make_queue(int length);
void queue_push(Queue *queue, int item);
int queue_pop(Queue *queue);
Shared *make_shared(int l);

pthread_t make_thread(void *(*entry)(void *), Shared *shared);

