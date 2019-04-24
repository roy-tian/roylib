#ifndef ROYDEQUE_H
#define ROYDEQUE_H

#include "roylist.h"

struct _RoyDeque {
  RoyList * head;
  RoyList * tail;
  size_t    length;
  size_t    element_size;
};

// RoyDeque: a double ended queue with a RoyList inside,
// which supports fast insertion and removal from both end of the queue.
typedef struct _RoyDeque RoyDeque;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyDeque. 
RoyDeque * roy_deque_new(size_t element_size);

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'deque', or memory leak will occur.)
void roy_deque_delete(RoyDeque * deque);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'deque' where the element takes place.
// (If 'position' is in small half of the list, iteration will start at head, or it will start at tail reversely.)
// (Returns NULL if position is out of range.)
void * roy_deque_pointer(RoyDeque * deque, int position);

// Returns an iterator to the element at front end.
void * roy_deque_front(RoyDeque * deque);

// Returns an iterator to the element at back end.
void * roy_deque_back(RoyDeque * deque);

// Returns an iterator to 'position' in 'deque' where the element takes place.
// (If 'position' is in small half of the list, iteration will start at head, or it will start at tail reversely.)
// (Returns NULL if position is out of range.)
const void * roy_deque_const_pointer(const RoyDeque * deque, int position);

// Returns an const iterator to the element at front end.
const void * roy_deque_const_front(const RoyDeque * deque);

// Returns an const iterator to the element at back end.
const void * roy_deque_const_back(const RoyDeque * deque);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_deque_element(void * dest, const RoyDeque * deque, int position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_deque_at(deque, element_type, position)               \
        (element_type*)(roy_deque_pointer(list, position)->data)

/* CAPACITY */

// Returns the number of elements in 'deque'.
size_t roy_deque_length(const RoyDeque * deque);

// Returns whether there is any elements in 'deque'.
bool roy_deque_empty(const RoyDeque * deque);

/* MODIFIERS */

// Add an element named 'data' into 'deque' at 'position'.
RoyDeque * roy_deque_insert(RoyDeque * deque, int position, const void * data);

// Adds an element named 'data' at the beginning of 'deque'.
RoyDeque * roy_deque_push_front(RoyDeque * deque, const void * data);

// Adds an element named 'data' at the end of 'deque'.
RoyDeque * roy_deque_push_back(RoyDeque * deque, const void * data);

// Removes an element from 'deque' at 'position'.
RoyDeque * roy_deque_erase(RoyDeque * deque, int position);

// Removes the first element from 'deque'.
RoyDeque * roy_deque_pop_front(RoyDeque * deque);

// Removes the last element from 'deque'.
RoyDeque * roy_deque_pop_back(RoyDeque * deque);

// Removes all the element from 'deque'.
RoyDeque * roy_deque_clear(RoyDeque * deque);

#endif // ROYDEQUE_H