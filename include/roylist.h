#ifndef ROYLIST_H
#define ROYLIST_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyList {
  void            * data;
  struct _RoyList * next;
  struct _RoyList * prev;
};

// RoyList: a container implemented as a singly-linked list which supports fast insertion and removal
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
RoyList * roy_list_pointer(RoyList * list, int position);

// Returns an iterator to the first element.
RoyList * roy_list_front(RoyList * list);

// Returns an iterator to the last element.
RoyList * roy_list_back(RoyList * list);

// Returns a const iterator to 'position' in 'list' where the element takes place.
// (Returns the head of 'list' if position is negative, NULL if position exceeds.)
const RoyList * roy_list_const_pointer(const RoyList * list, int position);

// Returns a const iterator to the first element.
const RoyList * roy_list_const_front(const RoyList * list);

// Returns a const iterator to the last element.
const RoyList * roy_list_const_back(const RoyList * list);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_list_element(void * dest, size_t element_size, const RoyList * list, int position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_list_at(list, element_type, position)             \
        (element_type*)roy_list_pointer(list, position)->data

/* CAPACITY */

// Returns the number of elements in 'list'.
size_t roy_list_length(const RoyList * list);

// Returns whether there is any elements in 'list'.
bool roy_list_empty(const RoyList * list);

/* MODIFIERS */

// Add an 'element_size'-sized element named 'data' into 'list' at 'position'.
RoyList * roy_list_insert(RoyList * list, int position, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the beginning of 'list'.
RoyList * roy_list_push_front(RoyList * list, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the end of 'list'.
RoyList * roy_list_push_back(RoyList * list, const void * data, size_t element_size);

// Removes an element from 'list' at 'position'.
RoyList * roy_list_erase(RoyList * list, int position);

// Removes the first element from 'list'.
RoyList * roy_list_pop_front(RoyList * list);

// Removes the last element from 'list'.
RoyList * roy_list_pop_back(RoyList * list);

// Removes all the element from 'list'.
RoyList * roy_list_clear(RoyList * list);

#endif // ROYLIST_H