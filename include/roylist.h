#ifndef ROYLIST_H
#define ROYLIST_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyList {
  void            * data;
  struct _RoyList * next;
  struct _RoyList * prev;
};

// RoyList: a container implemented as a double-linked list which supports fast insertion and removal
// from anywhere in the container. Fast random access is not supported.
typedef struct _RoyList RoyList;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyList's head for navigating, it contains no data, 
// the real data takes places from the 2nd element.
RoyList * roy_list_new(void);

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'list', or memory leak will occur.)
void roy_list_delete(RoyList * list);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
RoyList * roy_list_pointer(RoyList * list_head, int position);

// Returns an reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
RoyList * roy_list_reverse_pointer(RoyList * list_tail, int reverse_position);

// Returns an iterator to the first element.
RoyList * roy_list_front(RoyList * list_head);

// Returns an reversed iterator to the last element.
RoyList * roy_list_back(RoyList * list_tail);

// Returns a const iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
const RoyList * roy_list_const_pointer(const RoyList * list_head, int position);

// Returns an const reversed iterator to 'position' right most in 'list' where the element takes place.
// (Returns the tail of 'list' if position is negative, NULL if position exceeds.)
const RoyList * roy_list_const_reverse_pointer(const RoyList * list_tail, int reverse_position);

// Returns a const iterator to the first element.
const RoyList * roy_list_const_front(const RoyList * list_head);

// Returns a const reversed iterator to the last element.
const RoyList * roy_list_const_back(const RoyList * list_tail);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_list_element(void * dest, size_t element_size, const RoyList * list_head, int position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_list_at(list_head, element_type, position)          \
        (element_type*)(roy_list_pointer(list, position)->data)

/* CAPACITY */

// Returns the number of elements in 'list'.
size_t roy_list_size(const RoyList * list);

// Returns whether there is any elements in 'list'.
bool roy_list_empty(const RoyList * list);

/* MODIFIERS */

// Add an 'element_size'-sized element named 'data' into 'list' at 'position'.
RoyList * roy_list_insert(RoyList * list_head, int position, const void * data, size_t element_size);

// Add an 'element_size'-sized element named 'data' into 'list_tail' at 'reverse_position' rightmost.
RoyList * roy_list_insert_reverse(RoyList * list_tail, int reverse_position, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the beginning of the list.
RoyList * roy_list_push_front(RoyList * list_head, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the end of the list.
RoyList * roy_list_push_back(RoyList * list_tail, const void * data, size_t element_size);

// Removes an element from 'list_head' at 'position'.
RoyList * roy_list_erase(RoyList * list_head, int position);

// Removes an element from 'list_tail' at 'reverse_position'.
RoyList * roy_list_erase_reverse(RoyList * list_tail, int reverse_position);

// Removes the first element from 'list_head'.
RoyList * roy_list_pop_front(RoyList * list_head);

// Removes the last element from 'list_tail'.
RoyList * roy_list_pop_back(RoyList * list_tail);

// Removes all the element from 'list'.
RoyList * roy_list_clear(RoyList * list_head);

/* LIST OPERATIONS */

RoyList * roy_list_remove(RoyList * list, const void * data);

RoyList * roy_list_remove_if(RoyList * list, bool (*condition)(const void *));

RoyList * roy_list_reverse(RoyList * list);

RoyList * roy_list_unique(RoyList * list, int (*compare)(const void *, const void *));

RoyList * roy_list_sort(RoyList * list, int (*compare)(const void *, const void *));

/* TRAVERSE */

// Traverses all elements in 'vector' using 'operate'.
void roy_list_for_each(RoyList * list, void(* iterate)(void *));

// Traverses all elements whichever meets 'condition' in 'vector' using 'operate'.
void roy_list_for_which(RoyList * list, bool(* condition)(const void *), void(* iterate)(void *));

#endif // ROYLIST_H