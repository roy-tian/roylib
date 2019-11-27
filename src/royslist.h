#ifndef ROYSLIST_H
#define ROYSLIST_H

#include "trivials/royinit.h"

struct RoySList_ {
  void             * data;
  struct RoySList_ * next;
};

// RoySList: a container implemented as a singly-linked list which supports fast insertion and removal
// from anywhere in the container. Fast random access is not supported.
typedef struct RoySList_ RoySList;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoySList's head for navigating, it contains no data, 
// the real data takes places from the 2nd element.
RoySList * roy_slist_new(void);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'slist', or memory leak will occur.)
void roy_slist_delete(RoySList * slist, ROperate deleter);

/* ELEMENT ACCESS */

// Returns an iterator to 'position' in 'slist' where the element takes place, or NULL if 'position' exceeds.
RoySList * roy_slist_iterator(RoySList * slist, size_t position);

// Returns a const iterator to 'position' in 'slist' where the element takes place, or NULL if 'position' exceeds.
const RoySList * roy_slist_citerator(const RoySList * slist, size_t position);

// Returns an iterator to the first element.
RoySList * roy_slist_begin(RoySList * slist);

// Returns a const iterator to the first element.
const RoySList * roy_slist_cbegin(const RoySList * slist);

// Returns a typed pointer to the element at 'position', NULL if position exceeds.
#define roy_slist_at(slist, position, element_type)    \
        ((element_type *)roy_slist_iterator((list_head), (position))->data)

/* CAPACITY */

// Returns the number of elements in 'slist'.
size_t roy_slist_size(const RoySList * slist);

// Returns whether there is any elements in 'slist'.
bool roy_slist_empty(const RoySList * slist);

/* MODIFIERS */

// Adds an 'element_size'-sized element named 'data' at the beginning of 'slist'.
void roy_slist_push_front(RoySList * slist, void * data);

// Removes the first element from 'slist', returns whether the operation is successful.
// (Fails if 'slist' is empty.)
bool roy_slist_pop_front(RoySList * slist, ROperate deleter);

// Removes the 'position'-th element from 'slist', returns whether the operation is successful.
// (Fails if 'slist' is empty.)
bool roy_slist_erase(RoySList * slist, size_t position, ROperate deleter);

// Removes all the elements from 'slist'.
void roy_slist_clear(RoySList * slist, ROperate deleter);

/* LIST OPERATIONS */

// Removes all elements in 'slist' equivalent to data, returns how many elements are removed from 'slist'.
size_t roy_slist_remove(RoySList * slist, const void * data, RCompare comparer, ROperate deleter);

// Removes all elements in 'slist' which meet 'condition', returns how many elements are removed from 'slist'.
size_t roy_slist_remove_if(RoySList * slist, RCondition condition, ROperate deleter);

// Reverses the order of the elements in 'slist'.
void roy_slist_reverse(RoySList * slist);

// Removes all consecutive duplicate elements from 'slist', only left the first element in each group of equal elements is left.
size_t roy_slist_unique(RoySList *slist, RCompare comparer, ROperate deleter);

// Sorts the elements in ascending order, using quick sort strategy.
void roy_slist_sort(RoySList *slist, RCompare comparer);

/* TRAVERSE */

// Traverses all elements in 'vector' using 'operate'.
void roy_slist_for_each(RoySList * slist, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'vector' using 'operate'.
void roy_slist_for_which(RoySList * slist, RCondition condition, ROperate operate);

#endif // ROYSLIST_H