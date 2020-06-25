/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include "queue.h"


// QUEUE

Queue *make_queue(int length)
{
  Queue *queue = (Queue *) malloc(sizeof(Queue));
  queue->length = length;
  queue->array = (int *) malloc(length * sizeof(int));
  queue->next_in = 0;
  queue->next_out = 0;
  queue->mutex = make_mutex();
  return queue;
}

int queue_incr(Queue *queue, int i)
{
  // NOTE: you must hold the mutex to call this function.
  return (i+1) % queue->length;
}

int queue_empty(Queue *queue)
{
  // NOTE: you must hold the mutex to call this function.
  // queue is empty if next_in and next_out are the same
  int res = (queue->next_in == queue->next_out);
  return res;
}

int queue_full(Queue *queue)
{
  // NOTE: you must hold the mutex to call this function.
  // queue is full if incrementing next_in lands on next_out
  int res = (queue_incr(queue, queue->next_in) == queue->next_out);
  return res;
}

void queue_push(Queue *queue, int item) {
  mutex_lock(queue->mutex);
  if (queue_full(queue)) {
    mutex_unlock(queue->mutex);
    perror_exit("queue is full");
  }
  
  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in);
  mutex_unlock(queue->mutex);
}

int queue_pop(Queue *queue) {
  mutex_lock(queue->mutex);
  if (queue_empty(queue)) {
    mutex_unlock(queue->mutex);
    perror_exit("queue is empty");
  }
  
  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue, queue->next_out);
  mutex_unlock(queue->mutex);
  return item;
}

// SHARED

Shared *make_shared(int l)
{
  Shared *shared = check_malloc(sizeof(Shared));
  shared->queue = make_queue(l);
  return shared;
}

// THREAD
// PRODUCER-CONSUMER


void queue_test()
{
  int i;
  int item;
  int length = 128;

  Queue *queue = make_queue(length);
  assert(queue_empty(queue));
  for (i=0; i<length-1; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i=0; i<10; i++) {
    item = queue_pop(queue);
    assert(i == item);
  }
  assert(!queue_empty(queue));
  assert(!queue_full(queue));
  for (i=0; i<10; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i=0; i<10; i++) {
    item = queue_pop(queue);
  }  
  assert(item == 19);
}
