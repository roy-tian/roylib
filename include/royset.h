#ifndef ROYSET_H
#define ROYSET_H

#include "royinit.h"

struct _RoySet {
  struct _RoySet * left;
  struct _RoySet * right;
  void           * key;
};

// RoySet: an associative container that contains a sorted set of unique objects.
// Sorting is done using the key comparison function 'comp'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct _RoySet RoySet;

/* ELEMENT ACCESS */

// Returns an iterator to the minimum element of 'set'.
RoySet * roy_set_min(RoySet *set);

// Returns an iterator to the maximum element of 'set'.
RoySet * roy_set_max(RoySet *set);

// Returns a const iterator to the minimum element of 'set'.
const RoySet * roy_set_const_min(const RoySet *set);

// Returns a const iterator to the maximum element of 'set'.
const RoySet * roy_set_const_max(const RoySet *set);

/* CAPACITY */

// Returns the number of elements in 'set'.
size_t roy_set_size(const RoySet * set);

// Returns whether there is any elements in 'set'.
bool roy_set_empty(const RoySet * set);

/* MODIFIERS */

// Adds an 'key_size'-sized key into 'set' by ascending order.
RoySet * roy_set_insert(RoySet ** set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

// Removes the element equals to 'key' from 'set'.
RoySet * roy_set_erase(RoySet ** set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

// Removes all the element from 'set'.
RoySet * roy_set_clear(RoySet * set);

/* LOOKUP */

RoySet * roy_set_find(RoySet * set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoySet * roy_set_lower_bound(RoySet * set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoySet * roy_set_upper_bound(RoySet * set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

/* TRAVERSE */

// Traverses all elements in 'set' using 'iterate'.
void roy_set_for_each(RoySet * set, void(* iterate)(void *));

// Traverses all elements whichever meets 'condition' in 'set' using 'iterate'.
void roy_set_for_which(RoySet * set, bool(* condition)(const void *), void(* iterate)(void *));

#endif // ROYSET_H