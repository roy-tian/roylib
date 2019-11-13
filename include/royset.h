#ifndef ROYSET_H
#define ROYSET_H

#include "royinit.h"

struct RoySet_ {
  struct RoySet_ * left;
  struct RoySet_ * right;
  void           * key;
};

// RoySet: an associative container that contains a sorted set of unique objects.
// Sorting is done using the key comparison function 'compare'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct RoySet_ RoySet;

/* ELEMENT ACCESS */

// Returns an iterator to the minimum element of 'set'.
RoySet * roy_set_min(RoySet *set);

// Returns an iterator to the maximum element of 'set'.
RoySet * roy_set_max(RoySet *set);

// Returns a const iterator to the minimum element of 'set'.
const RoySet * roy_set_cmin(const RoySet *set);

// Returns a const iterator to the maximum element of 'set'.
const RoySet * roy_set_cmax(const RoySet *set);

/* CAPACITY */

// Returns the number of elements in 'set'.
size_t roy_set_size(const RoySet * set);

// Returns whether there is any elements in 'set'.
bool roy_set_empty(const RoySet * set);

/* MODIFIERS */

// Adds an 'key_size'-sized key into 'set' by ascending order.
RoySet * roy_set_insert(RoySet ** set, RCData key, size_t key_size, RCompare compare);

// Removes the element equals to 'key' from 'set'.
RoySet * roy_set_erase(RoySet ** set, RCData key, size_t key_size, RCompare compare);

// Removes all the element from 'set'.
void roy_set_clear(RoySet * set);

/* LOOKUP */

// Finds an element equivalent to 'key' using compare function 'compare', returns an iterator to it.
RoySet * roy_set_find(RoySet * set, RCData key, RCompare compare);

/* TRAVERSE */

// Traverses all elements in 'set' using 'operate'.
void roy_set_for_each(RoySet * set, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'set' using 'operate'.
void roy_set_for_which(RoySet * set, RCondition condition, ROperate operate);

#endif // ROYSET_H