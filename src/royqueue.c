#include "../include/royqueue.h"

RoyQueue *
roy_queue_new(size_t capacity,
              size_t element_size) {
  RoyQueue * ret    = (RoyQueue *)malloc(sizeof(RoyQueue));
  ret->data         = calloc(capacity, element_size);
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
  return roy_array_size((RoyArray *)queue);
}

size_t
roy_queue_capacity(const RoyQueue * queue) {
  return roy_array_capacity((RoyArray *)queue);
}

bool
roy_queue_empty(const RoyQueue * queue) {
  return roy_array_empty((RoyArray *)queue);
}

bool
roy_queue_full(const RoyQueue * queue) {
  return roy_array_full((RoyArray *)queue);
}

bool
roy_queue_push(RoyQueue   * queue,
               const void * data) {
  bool success = roy_array_insert((RoyArray *)queue, queue->back_index, data);
  if (success) {
    queue->back_index++;
    queue->back_index = roy_queue_capacity(queue) % queue->back_index;
  }
  return success;
}

bool
roy_queue_pop(RoyQueue * queue) {
  bool success = roy_array_erase((RoyArray *)queue, queue->front_index);
  if (success) {
    queue->front_index--;
    queue->front_index = roy_queue_capacity(queue) % queue->front_index;
  }
  return success;
}

void
roy_queue_clear(RoyQueue * queue) {
  roy_array_clear((RoyArray *)queue);
  queue->front_index = 0;
  queue->back_index  = 0;
}