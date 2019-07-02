#include "../include/royqueue.h"

RoyQueue *
roy_queue_new(size_t capacity,
              size_t element_size) {
  RoyQueue * ret    = ROY_QUEUE(malloc(sizeof(RoyQueue)));
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
  roy_array_delete(ROY_ARRAY(queue));
}

size_t
roy_queue_size(const RoyQueue * queue) {
  return roy_array_size(ROY_ARRAY(queue));
}

size_t
roy_queue_capacity(const RoyQueue * queue) {
  return roy_array_capacity(ROY_ARRAY(queue));
}

bool
roy_queue_empty(const RoyQueue * queue) {
  return roy_array_empty(ROY_ARRAY(queue));
}

bool
roy_queue_full(const RoyQueue * queue) {
  return roy_array_full(ROY_ARRAY(queue));
}

RoyQueue *
roy_queue_push(RoyQueue * queue, const void * data) {
  if (!roy_queue_full(queue)) {
    roy_array_insert(ROY_ARRAY(queue), queue->back_index++, data);
    if (queue->back_index == roy_queue_capacity(queue)) {
      queue->back_index = 0;
    }
  }
  return queue; 
}

RoyQueue *
roy_queue_pop(RoyQueue * queue) {
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
  queue->size        = 0;
  queue->front_index = 0;
  queue->back_index  = 0;
  return queue;
}