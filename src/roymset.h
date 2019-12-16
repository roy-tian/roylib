#ifndef ROYMSET_H
#define ROYMSET_H

#include "trivials/royinit.h"

struct RoyMSet_ {
  struct RoyMSet_ * left;
  struct RoyMSet_ * right;
  void            * key;
};

/**
 * @brief RoyMSet [aka Multi-Set]: an associative container that contains
 * a sorted set of objects of type Key, duplicated objects is allowed.
 * Sorting is done using the key comparison function 'comparer'.
 * Search, removal, and insertion operations have logarithmic complexity.
 */
typedef struct RoyMSet_ RoyMSet;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates a RoyMSet.
 * @return an empty RoyMSet node.
 */
RoyMSet * roy_mset_new(void);

/**
 * @brief Releases all the elements and destroys the RoyMSet - 'mset' itself.
 * @param deleter - a function for element deleting.
 * @note - Always call this function after the work is done by the given 'mset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mset_delete(RoyMSet * mset, ROperate deleter);


/* ITERATORS */

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
RoyMSet * roy_mset_insert(RoyMSet ** mset, void * key, RCompare comparer);

// Removes all elements from 'mset'.
void roy_mset_clear(RoyMSet * mset, ROperate deleter);

// Removes all elements equals to 'key' from 'mset'.
RoyMSet * roy_mset_remove(RoyMSet ** mset, const void * key, RCompare comparer, ROperate deleter);

/* LOOKUP */

size_t roy_mset_count(const RoyMSet * mset, const void * key, RCompare comparer);

RoyMSet * roy_mset_find(const RoyMSet * mset, const void * key, RCompare comparer);

/* TRAVERSE */

// Traverses all elements in 'mset' using 'operate'.
void roy_mset_for_each(RoyMSet * mset, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'mset' using 'operate'.
void roy_mset_for_which(RoyMSet * mset, RCondition condition, ROperate operate);

#endif // ROYMSET_H