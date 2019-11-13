#ifndef ROYDEQUE_H
#define ROYDEQUE_H

#include "roylist.h"

struct RoyDeque_ {
  RoyList * head;
  RoyList * tail;
  size_t    size;
  size_t    element_size;
};

// RoyDeque: a double ended queue powered by a RoyDeque inside,
// which supports fast insertion and removal from both end of the queue.
typedef struct RoyDeque_ RoyDeque;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyDeque. 
RoyDeque * roy_deque_new(size_t element_size);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'deque', or memory leak will occur.)
void roy_deque_delete(RoyDeque * deque);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'deque' where the element takes place.
// (If 'position' is in small half of the deque, iteration will start at head, and vice versa.)
// (Returns NULL if position is out of range.)
RData roy_deque_pointer(RoyDeque * deque, size_t position);

// Returns an iterator to the element at front end.
RData roy_deque_front(RoyDeque * deque);

// Returns an iterator to the element at back end.
RData roy_deque_back(RoyDeque * deque);

// Returns an iterator to 'position' in 'deque' where the element takes place.
// (If 'position' is in small half of the deque, iteration will start at head, and vice versa.)
// (Returns NULL if position is out of range.)
RCData roy_deque_cpointer(const RoyDeque * deque, size_t position);

// Returns an const iterator to the element at front end.
RCData roy_deque_cfront(const RoyDeque * deque);

// Returns an const iterator to the element at back end.
RCData roy_deque_cback(const RoyDeque * deque);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
RData roy_deque_element(RData dest, const RoyDeque * deque, size_t position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_deque_at(deque, element_type, position) ((element_type *)(roy_deque_pointer((deque), (position))))

/* CAPACITY */

// Returns the number of elements in 'deque'.
size_t roy_deque_size(const RoyDeque * deque);

// Returns whether there is any elements in 'deque'.
bool roy_deque_empty(const RoyDeque * deque);

/* MODIFIERS */

// Add an element named 'data' into 'deque' at 'position'.
bool roy_deque_insert(RoyDeque * deque, size_t position, RCData data);

// Adds an element named 'data' at the beginning of 'deque'.
void roy_deque_push_front(RoyDeque * deque, RCData data);

// Adds an element named 'data' at the end of 'deque'.
void roy_deque_push_back(RoyDeque * deque, RCData data);

// Removes an element from 'deque' at 'position'.
bool roy_deque_erase(RoyDeque * deque, size_t position);

// Removes the first element from 'deque'.
bool roy_deque_pop_front(RoyDeque * deque);

// Removes the last element from 'deque'.
bool roy_deque_pop_back(RoyDeque * deque);

// Removes all the element from 'deque'.
void roy_deque_clear(RoyDeque * deque);

/* TRAVERSE */

// Traverses all elements in 'deque' using 'operate'.
void roy_deque_for_each(RoyDeque * deque, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'deque' using 'operate'.
void roy_deque_for_which(RoyDeque * deque, RCondition condition, ROperate operate);

#endif // ROYDEQUE_H