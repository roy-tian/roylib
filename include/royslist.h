#ifndef ROYSLIST_H
#define ROYSLIST_H

#include <stddef.h>
#include <stdbool.h>

struct _RoySList {
  void             * data;
  struct _RoySList * next;
};

// RoySList: a container implemented as a singly-linked list which supports fast insertion and removal
// from anywhere in the container. Fast random access is not supported.
typedef struct _RoySList RoySList;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoySList's head for navigating, it contains no data, 
// the real data takes places from the 2nd element.
RoySList * roy_slist_new(void);

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'slist', or memory leak will occur.)
void roy_slist_delete(RoySList * slist);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'slist' where the element takes place.
// (Returns the head of 'slist' if position is negative, NULL if position exceeds.)
RoySList * roy_slist_pointer(RoySList * slist, int position);

// Returns an iterator to the first element.
RoySList * roy_slist_front(RoySList * slist);

// Returns an iterator to the last element.
RoySList * roy_slist_back(RoySList * slist);

// Returns a const iterator to 'position' in 'slist' where the element takes place.
// (Returns the head of 'slist' if position is negative, NULL if position exceeds.)
const RoySList * roy_slist_const_pointer(const RoySList * slist, int position);

// Returns a const iterator to the first element.
const RoySList * roy_slist_const_front(const RoySList * slist);

// Returns a const iterator to the last element.
const RoySList * roy_slist_const_back(const RoySList * slist);

// Returns a copy of the element at 'position'.
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_slist_element(void * dest, size_t element_size, const RoySList * slist, int position);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_slist_at(slist, element_type, position)             \
        (element_type*)roy_slist_pointer(slist, position)->data

/* CAPACITY */

// Returns the number of elements in 'slist'.
size_t roy_slist_length(const RoySList * slist);

// Returns whether there is any elements in 'slist'.
bool roy_slist_empty(const RoySList * slist);

/* MODIFIERS */

// Add an 'element_size'-sized element named 'data' into 'slist' at 'position'.
RoySList * roy_slist_insert(RoySList * slist, int position, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the beginning of 'slist'.
RoySList * roy_slist_push_front(RoySList * slist, const void * data, size_t element_size);

// Adds an 'element_size'-sized element named 'data' at the end of 'slist'.
RoySList * roy_slist_push_back(RoySList * slist, const void * data, size_t element_size);

// Removes an element from 'slist' at 'position'.
RoySList * roy_slist_erase(RoySList * slist, int position);

// Removes the first element from 'slist'.
RoySList * roy_slist_pop_front(RoySList * slist);

// Removes the last element from 'slist'.
RoySList * roy_slist_pop_back(RoySList * slist);

// Removes all the element from 'slist'.
RoySList * roy_slist_clear(RoySList * slist);

#endif // ROYSLIST_H