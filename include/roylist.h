#ifndef ROYLIST_H
#define ROYLIST_H

#include "royinit.h"

struct _RoyList {
  RoyElement data;
  struct _RoyList * next;
  struct _RoyList * prev;
};

// RoyList: a container implemented as a double-linked list which supports fast insertion and removal from anywhere in the container.
// Fast random access is not supported.
typedef struct _RoyList * RoyList;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyList's head for navigating.
// It contains no data, the real data takes places from the 2nd element.
RoyList roy_list_new(void);

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'list', or memory leak will occur.)
void roy_list_delete(RoyList list);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
RoyList roy_list_iterator(RoyList list_head, int position);

// Returns an reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
RoyList roy_list_reverse_iterator(RoyList list_tail, int reverse_position);

// Returns an iterator to the first element.
RoyList roy_list_begin(RoyList list_head);

// Returns an reversed iterator to the last element.
RoyList roy_list_rbegin(RoyList list_tail);

// Returns a const iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
const RoyList roy_list_const_iterator(const RoyList list_head, int position);

// Returns an const reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
const RoyList roy_list_const_reverse_iterator(const RoyList list_tail, int reverse_position);

// Returns a const iterator to the first element.
const RoyList roy_list_cbegin(const RoyList list_head);

// Returns a const reversed iterator to the last element.
const RoyList roy_list_crbegin(const RoyList list_tail);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
RoyElement roy_list_element(RoyElement dest, size_t element_size, const RoyList list_head, int position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_list_at(list_head, type_name, position) (type_name *)(roy_list_iterator((list_head), (position))->data)

/* CAPACITY */

// Returns the number of elements in 'list'.
size_t roy_list_size(const RoyList list);

// Returns whether there is any elements in 'list'.
bool roy_list_empty(const RoyList list);

/* MODIFIERS */

// Adds an 'element_size'-sized element named 'data' into 'list' at 'position'.
RoyList roy_list_insert(RoyList list_head, int position, const RoyElement data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' into 'list_tail' at 'reverse_position' rightmost.
RoyList roy_list_insert_reverse(RoyList list_tail, int reverse_position, const RoyElement data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the beginning of the list.
RoyList roy_list_push_front(RoyList list_head, const RoyElement data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the end of the list.
RoyList roy_list_push_back(RoyList list_tail, const RoyElement data, size_t element_size);

// Removes an element from 'list_head' at 'position'.
RoyList roy_list_erase(RoyList list_head, int position);

// Removes an element from 'list_tail' at 'reverse_position'.
RoyList roy_list_erase_reverse(RoyList list_tail, int reverse_position);

// Removes the first element from 'list_head'.
RoyList roy_list_pop_front(RoyList list_head);

// Removes the last element from 'list_tail'.
RoyList roy_list_pop_back(RoyList list_tail);

// Removes all the element from 'list'.
RoyList roy_list_clear(RoyList list_head);

/* LIST OPERATIONS */

RoyList roy_list_remove_if(RoyList list, RoyCondition condition);

RoyList roy_list_reverse(RoyList list);

RoyList roy_list_unique(RoyList list, RoyCompare compare);

RoyList roy_list_sort(RoyList list, RoyCompare compare);

/* TRAVERSE */

// Traverses all elements in 'list' using 'operate'.
void roy_list_for_each(RoyList list, RoyOperate operate);

// Traverses all elements whichever meets 'condition' in 'list' using 'operate'.
void roy_list_for_which(RoyList list, RoyCondition condition, RoyOperate operate);

#endif // ROYLIST_H