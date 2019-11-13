#ifndef ROYLIST_H
#define ROYLIST_H

#include "royinit.h"

struct RoyList_ {
  void            * data;
  struct RoyList_ * next;
  struct RoyList_ * prev;
};

// RoyList: a container implemented as a double-linked list which supports fast insertion and removal from anywhere in the container.
// Fast random access is not supported.
typedef struct RoyList_ RoyList;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyList's head for navigating.
// It contains no data, the real data takes places from the 2nd element.
RoyList * roy_list_new(void);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'list', or memory leak will occur.)
void roy_list_delete(RoyList * list);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
RoyList * roy_list_iterator(RoyList * list_head, size_t position);

// Returns an reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
RoyList * roy_list_riterator(RoyList * list_tail, size_t rposition);

// Returns an iterator to the first element.
RoyList * roy_list_begin(RoyList * list_head);

// Returns an reversed iterator to the last element.
RoyList * roy_list_rbegin(RoyList * list_tail);

// Returns a const iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
const RoyList * roy_list_citerator(const RoyList * list_head, size_t position);

// Returns an const reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
const RoyList * roy_list_criterator(const RoyList * list_tail, size_t rposition);

// Returns a const iterator to the first element.
const RoyList * roy_list_cbegin(const RoyList *list_head);

// Returns a const reversed iterator to the last element.
const RoyList * roy_list_crbegin(const RoyList *list_tail);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_list_element(void * dest, const RoyList * list_head, size_t element_size, size_t position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_list_at(list_head, element_type, position) ((element_type *)(roy_list_iterator((list_head), (position))->data))

/* CAPACITY */

// Returns the number of elements from 'list_head'.
size_t roy_list_size(const RoyList * list_head);

// Returns the number of elements from 'list_tail'.
size_t roy_list_rsize(const RoyList * list_tail);

// Returns whether there is any elements from 'list_head'.
bool roy_list_empty(const RoyList * list_head);

// Returns whether there is any elements from 'list_head'.
bool roy_list_rempty(const RoyList * list_tail);

/* MODIFIERS */

// Adds an 'element_size'-sized element named 'data' into 'list' at 'position'.
bool roy_list_insert(RoyList * list_head, size_t position, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' into 'list_tail' at 'rposition' rightmost.
bool roy_list_insert_reverse(RoyList * list_tail, size_t rposition, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the beginning of the list.
void roy_list_push_front(RoyList * list_head, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the end of the list.
void roy_list_push_back(RoyList * list_tail, const void * data, size_t element_size);

// Removes an element from 'list_head' at 'position'.
bool roy_list_erase(RoyList * list_head, size_t position);

// Removes an element from 'list_tail' at 'rposition'.
bool roy_list_erase_reverse(RoyList * list_tail, size_t rposition);

// Removes the first element from 'list_head'.
bool roy_list_pop_front(RoyList * list_head);

// Removes the last element from 'list_tail'.
bool roy_list_pop_back(RoyList * list_tail);

// Removes all the element from 'list'.
void roy_list_clear(RoyList * list_head);

/* LIST OPERATIONS */

// Removes all elements in 'list' equivalent to data.
size_t roy_list_remove(RoyList * list, const void * data, RCompare compare);

// Removes all elements in 'list' which meet 'condition'.
size_t roy_list_remove_if(RoyList * list, RCondition condition);

// Reverses the order of the elements in 'list'.
void roy_list_reverse(RoyList ** list);

// Removes all consecutive duplicate elements from 'list', only the first element in each group of equal elements is left. 
void roy_list_unique(RoyList * list, RCompare compare);

// Sorts the elements in ascending order, using quick sort strategy.
void roy_list_sort(RoyList * list, RCompare compare);

/* TRAVERSE */

// Traverses all elements in 'list' using 'operate'.
void roy_list_for_each(RoyList * list, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'list' using 'operate'.
void roy_list_for_which(RoyList * list, RCondition condition, ROperate operate);

#endif // ROYLIST_H