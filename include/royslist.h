#ifndef ROYSLIST_H
#define ROYSLIST_H

#include "royinit.h"

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

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'slist', or memory leak will occur.)
void roy_slist_delete(RoySList * slist);

/* ELEMENT ACCESS */

// Returns an iterator to the first element.
RoySList * roy_slist_begin(RoySList * slist);

// Returns a const iterator to the first element.
const RoySList * roy_slist_cbegin(const RoySList * slist);

/* CAPACITY */

// Returns the number of elements in 'slist'.
size_t roy_slist_size(const RoySList * slist);

// Returns whether there is any elements in 'slist'.
bool roy_slist_empty(const RoySList * slist);

/* MODIFIERS */

// Adds an 'element_size'-sized element named 'data' at the beginning of 'slist'.
RoySList * roy_slist_push_front(RoySList * slist, const void * data, size_t element_size);

// Removes the first element from 'slist'.
RoySList * roy_slist_pop_front(RoySList * slist);

// Removes all the element from 'slist'.
RoySList * roy_slist_clear(RoySList * slist);

/* LIST OPERATIONS */

RoySList * roy_slist_remove_if(RoySList * slist, bool (*condition)(const void *));

RoySList * roy_slist_reverse(RoySList * slist);

RoySList * roy_slist_unique(RoySList *slist, int (*comp)(const void *, const void *));

RoySList * roy_slist_sort(RoySList *slist, int (*comp)(const void *, const void *));

/* TRAVERSE */

// Traverses all elements in 'vector' using 'operate'.
void roy_slist_for_each(RoySList * slist, void(* operate)(void *));

// Traverses all elements whichever meets 'condition' in 'vector' using 'operate'.
void roy_slist_for_which(RoySList * slist, bool(* condition)(const void *), void(* operate)(void *));

#endif // ROYSLIST_H