#ifndef ROYMMAP_H
#define ROYMMAP_H

#include "trivials/royinit.h"
#include "roymset.h"

struct RoyMMap_ {
  RoyMSet  * root;
  RCompare   compare;
  ROperate   deleter;
};

// RoyMMap[aka Multi-Map]: an associative container that contains a sorted multi map of unique objects of type Key.
// Sorting is done using the key comparison function 'compare'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct RoyMMap_ RoyMMap;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyMMap. 
RoyMMap * roy_mmap_new(RCompare compare, ROperate deleter);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'mmap', or memory leak will occur.)
void roy_mmap_delete(RoyMMap * mmap);

/* ELEMENT ACCESS */

// Returns an pointer to the value of the minimum element of 'mmap'.
void * roy_mmap_min(RoyMMap * mmap);

// Returns an pointer to the value of the maximum element of 'mmap'.
void * roy_mmap_max(RoyMMap * mmap);

// Returns a const pointer to the value of the minimum element of 'mmap'.
const void * roy_mmap_cmin(const RoyMMap * mmap);

// Returns a const pointer to the value of the maximum element of 'mmap'.
const void * roy_mmap_cmax(const RoyMMap * mmap);

#define roy_mmap_at(mmap, value_type, key)    \
        (value_type *)(roy_mmap_find((mmap), (key)))

/* CAPACITY */

// Returns the number of elements in 'mmap'.
size_t roy_mmap_size(const RoyMMap * mmap);

// Returns whether there is any elements in 'mmap'.
bool roy_mmap_empty(const RoyMMap * mmap);

/* MODIFIERS */

// Adds a 'key_size'-sized key contains a 'value_size'-sized value into 'mmap' by ascending order.
RoyMMap * roy_mmap_insert(RoyMMap * mmap, void * key, void * value);

// Removes the element equals to 'key' from 'mmap'.
RoyMMap * roy_mmap_erase(RoyMMap * mmap, const void * key);

// Removes all the element from 'mmap'.
void roy_mmap_clear(RoyMMap * mmap);

/* LOOKUP */

size_t roy_mmap_count(const RoyMSet * mset, const void * key);

RoyMMap * roy_mmap_lower_bound(RoyMMap * mmap, const void * key);

RoyMMap * roy_mmap_upper_bound(RoyMMap * mmap, const void * key);

/* TRAVERSE */

// Traverses all elements in 'mmap' using 'operate'.
void roy_mmap_for_each(RoyMMap * mmap, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'mmap' using 'operate'.
void roy_mmap_for_which(RoyMMap * mmap, RCondition condition, ROperate operate);

#endif // ROYMMAP_H