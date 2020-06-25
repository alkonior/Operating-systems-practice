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
  return queue;
}

int queue_incr(Queue *queue, int i)
{
  return (i+1) % queue->length;
}

int queue_empty(Queue *queue)
{
  // queue is empty if next_in and next_out are the same
  return (queue->next_in == queue->next_out);
}

int queue_full(Queue *queue)
{
  // queue is full if incrementing next_in lands on next_out
  return (queue_incr(queue, queue->next_in) == queue->next_out);
}

void queue_push(Queue *queue, int item) {
  if (queue_full(queue)) {
    perror_exit("queue is full");
  }
  
  queue->array[queue->next_in] = item;
  queue->next_in = queue_incr(queue, queue->next_in);
}

int queue_pop(Queue *queue) {
  if (queue_empty(queue)) {
    perror_exit("queue is empty");
  }
  
  int item = queue->array[queue->next_out];
  queue->next_out = queue_incr(queue, queue->next_out);
  return item;
}

// SHARED

Shared *make_shared(int l)
{
  Shared *shared = check_malloc(sizeof(Shared));
  shared->queue = make_queue(l);
  return shared;
}

// TEST CODE

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

