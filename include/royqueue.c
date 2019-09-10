#include "royqueue.h"

RoyQueue *
roy_queue_new(size_t capacity,
              size_t element_size) {
  RoyQueue * ret    = (RoyQueue *)malloc(sizeof(RoyQueue));
  assert(ret != NULL);
  ret->data         = calloc(capacity, element_size);
  assert(ret->data != NULL);
  ret->size         = 0;
  ret->capacity     = capacity;
  ret->element_size = element_size;
  ret->front_index  = 0;
  ret->back_index   = 0;
  return ret;
}

void
roy_queue_delete(RoyQueue * queue) {
  roy_array_delete((RoyArray *)queue);
}

size_t
roy_queue_size(const RoyQueue * queue) {
  assert(queue != NULL);
  return roy_array_size((RoyArray *)queue);
}

size_t
roy_queue_capacity(const RoyQueue * queue) {
  assert(queue != NULL);
  return roy_array_capacity((RoyArray *)queue);
}

bool
roy_queue_empty(const RoyQueue * queue) {
  assert(queue != NULL);
  return roy_array_empty((RoyArray *)queue);
}

bool
roy_queue_full(const RoyQueue * queue) {
  assert(queue != NULL);
  return roy_array_full((RoyArray *)queue);
}

RoyQueue *
roy_queue_push(RoyQueue   * queue,
               const void * data) {
  assert(queue != NULL);
  assert(data != NULL);
  if (!roy_queue_full(queue)) {
    roy_array_insert((RoyArray *)queue, queue->back_index++, data);
    if (queue->back_index == roy_queue_capacity(queue)) {
      queue->back_index = 0;
    }
  }
  return queue; 
}

RoyQueue *
roy_queue_pop(RoyQueue * queue) {
  assert(queue != NULL);
  if (!roy_queue_empty(queue)) {
    queue->size--;
    queue->front_index++;
    if (queue->front_index == roy_queue_capacity(queue)) {
      queue->front_index = 0;
    }
  }
  return queue;
}

RoyQueue *
roy_queue_clear(RoyQueue * queue) {
  assert(queue != NULL);
  queue->size        = 0;
  queue->front_index = 0;
  queue->back_index  = 0;
  return queue;
}