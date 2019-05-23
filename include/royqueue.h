#ifndef ROYQUEUE_H
#define ROYQUEUE_H

#include "royarray.h"

struct _RoyQueue {
  void   * data;
  size_t   size;
  size_t   capacity;
  size_t   element_size;
  int      front_index;
  int      back_index;
};

/* CONSTRUCTION AND DESTRUCTION */

// RoyQueue: a container adapter that gives the functionality of a FIFO data structure,
// which inplemented as an cycled linear list.
typedef struct _RoyQueue RoyQueue;


// Allocates sufficient memory for an RoyQueue and returns a pointer to it.
// The queue can store 'capacity' elements with each size 'element_size' .
// (Operations on un-newed RoyQueues will cause undefined behavior.)
RoyQueue * roy_queue_new(size_t capacity, size_t element_size);

// Deallocates the memory allocated by 'roy_queue_new'.
// (Always call this function after the work is done by the given 'queue', or memory leak will occur.)
void roy_queue_delete(RoyQueue * queue);

/* ELEMENT ACCESS */

#define roy_queue_front(queue, element_type)  \
        (roy_queue_empty(queue)) ? NULL :       \
        ((element_type*)roy_array_pointer((ROY_ARRAY(queue)), (queue->front_index)))

/* CAPACITY */

// Returns the number of elements in 'queue'.
size_t roy_queue_size(const RoyQueue * queue);

// Returns the capacity of 'queue'.
size_t roy_queue_capacity(const RoyQueue * queue);

// Returns whether there is any elements in 'queue'.
bool roy_queue_empty(const RoyQueue * queue);

// Returns whether the number of elements in 'queue' reaches its capacity.
bool roy_queue_full(const RoyQueue * queue);

/* MODIFIERS */

// Adds an element named 'data' into 'queue' next to the last element.
// (The behavior is undefined if 'data' is uninitialized.)
RoyQueue * roy_queue_push(RoyQueue * queue, const void * data);

// Removes the last element.
RoyQueue * roy_queue_pop(RoyQueue * queue);

// Removes all the elements in 'array'.
RoyQueue * roy_queue_clear(RoyQueue * queue);

#endif // ROYQUEUE_H