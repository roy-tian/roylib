#ifndef ROYMSET_H
#define ROYMSET_H

#include "royinit.h"

struct RoyMSet_ {
  struct RoyMSet_ * left;
  struct RoyMSet_ * right;
  void            * key;
};

// RoyMSet [aka Multi-Set]: an associative container that contains a sorted set of objects of type Key, duplicated objects is allowed.
// Sorting is done using the key comparison function 'compare'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct RoyMSet_ RoyMSet;

/* ELEMENT ACCESS */

// Returns an iterator to the minimum element of 'mset'.
RoyMSet * roy_mset_min(RoyMSet *mset);

// Returns an iterator to the maximum element of 'mset'.
RoyMSet * roy_mset_max(RoyMSet *mset);

// Returns a const iterator to the minimum element of 'mset'.
const RoyMSet * roy_mset_cmin(const RoyMSet *mset);

// Returns a const iterator to the maximum element of 'mset'.
const RoyMSet * roy_mset_cmax(const RoyMSet *mset);

/* CAPACITY */

// Returns the number of elements in 'mset'.
size_t roy_mset_size(const RoyMSet * mset);

// Returns whether there is any elements in 'mset'.
bool roy_mset_empty(const RoyMSet * mset);

/* MODIFIERS */

// Adds an 'key_size'-sized key into 'mset' by ascending order.
RoyMSet * roy_mset_insert(RoyMSet ** mset, RCData key, size_t key_size, RCompare compare);

// Removes the element equals to 'key' from 'mset'.
RoyMSet * roy_mset_erase(RoyMSet ** mset, RCData key, size_t key_size, RCompare compare);

// Removes all the element from 'mset'.
void roy_mset_clear(RoyMSet * mset);

/* LOOKUP */

size_t roy_mset_count(const RoyMSet * mset, RCData key, RCompare compare);

RoyMSet * roy_mset_lower_bound(const RoyMSet * mset, RCData key, RCompare compare);

RoyMSet * roy_mset_upper_bound(const RoyMSet * mset, RCData key, RCompare compare);

/* TRAVERSE */

// Traverses all elements in 'mset' using 'operate'.
void roy_mset_for_each(RoyMSet * mset, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'mset' using 'operate'.
void roy_mset_for_which(RoyMSet * mset, RCondition condition, ROperate operate);

#endif // ROYMSET_H