#ifndef ROYMSET_H
#define ROYMSET_H

#include "royinit.h"

struct _RoyMSet {
  void            * key;
  struct _RoyMSet * left;
  struct _RoyMSet * right;
};

// RoyMSet [Multi Set]: an associative container that contains a sorted set of objects of type Key, duplicated objects is allowed.
// Sorting is done using the key comparison function 'comp'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct _RoyMSet RoyMSet;

/* ELEMENT ACCESS */

// Returns an iterator to the minimum element of 'mset'.
RoyMSet * roy_mset_front(RoyMSet * mset);

// Returns an iterator to the maximum element of 'mset'.
RoyMSet * roy_mset_back(RoyMSet * mset);

// Returns a const iterator to the minimum element of 'mset'.
const RoyMSet * roy_mset_const_front(const RoyMSet * mset);

// Returns a const iterator to the maximum element of 'mset'.
const RoyMSet * roy_mset_const_back(const RoyMSet * mset);

/* CAPACITY */

// Returns the number of elements in 'mset'.
size_t roy_mset_size(const RoyMSet * mset);

// Returns whether there is any elements in 'mset'.
bool roy_mset_empty(const RoyMSet * mset);

/* MODIFIERS */

// Adds an 'key_size'-sized key into 'mset' by ascending order.
RoyMSet * roy_mset_insert(RoyMSet ** mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

// Removes the element equals to 'key' from 'mset'.
RoyMSet * roy_mset_erase(RoyMSet ** mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

// Removes all the element from 'mset'.
RoyMSet * roy_mset_clear(RoyMSet * mset);

/* LOOKUP */

RoyMSet * roy_mset_count(const RoyMSet * mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoyMSet * roy_mset_find(const RoyMSet * mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoyMSet * roy_mset_lower_bound(const RoyMSet * mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoyMSet * roy_mset_upper_bound(const RoyMSet * mset, const void * key, size_t key_size, int (*comp)(const void *, const void *));

/* TRAVERSE */

// Traverses all elements in 'mset' using 'iterate'.
void roy_mset_for_each(RoyMSet * mset, void(* iterate)(void *));

// Traverses all elements whichever meets 'condition' in 'mset' using 'iterate'.
void roy_mset_for_which(RoyMSet * mset, bool(* condition)(const void *), void(* iterate)(void *));

#endif // ROYMSET_H