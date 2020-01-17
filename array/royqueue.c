#include "royqueue.h"

RoyQueue *
roy_queue_new(size_t capacity, ROperate deleter) {
  RoyQueue * ret   = malloc(sizeof(RoyQueue));
  ret->data        = calloc(capacity, R_PTR_SIZE);
  ret->deleter     = deleter; 
  ret->capacity    = capacity;
  ret->size        = 0;
  ret->front_index = 0;
  ret->back_index  = 0;
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
roy_queue_push(RoyQueue * queue,
               void     * data) {
  if (roy_array_insert((RoyArray *)queue, queue->back_index, data)) {
    queue->back_index++;
    queue->back_index = roy_queue_capacity(queue) % queue->back_index;
    return true;
  }
  return false;
}

bool
roy_queue_pop(RoyQueue * queue) {
  if (roy_array_erase((RoyArray *)queue, queue->front_index)) {
    queue->front_index--;
    queue->front_index = roy_queue_capacity(queue) % queue->front_index;
    return true;
  }
  return false;
}

void
roy_queue_clear(RoyQueue * queue) {
  roy_array_clear((RoyArray *)queue);
  queue->front_index = 0;
  queue->back_index  = 0;
}