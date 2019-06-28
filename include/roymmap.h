#ifndef ROYMMAP_H
#define ROYMMAP_H

#include "royinit.h"
#include "roymset.h"

struct _RoyMMap {
  RoyMSet * root;
  size_t   key_size;
  size_t   value_size;
  int   (* comp)(const void *, const void *);
};

// RoyMMap: an associative container that contains a sorted multi map of unique objects of type Key.
// Sorting is done using the key comparison function 'comp'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct _RoyMMap RoyMMap;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyMMap. 
RoyMMap * roy_mmap_new(size_t key_size, size_t value_size, int (* comp)(const void *, const void *));

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'mmap', or memory leak will occur.)
void roy_mmap_delete(RoyMMap * mmap);

/* ELEMENT ACCESS */

// Returns an pointer to the value of the minimum element of 'mmap'.
void * roy_mmap_pmin(RoyMMap * mmap);

// Returns an pointer to the value of the maximum element of 'mmap'.
void * roy_mmap_pmax(RoyMMap * mmap);

// Returns a const pointer to the value of the minimum element of 'mmap'.
const void * roy_mmap_const_pmin(const RoyMMap * mmap);

// Returns a const pointer to the value of the maximum element of 'mmap'.
const void * roy_mmap_const_pmax(const RoyMMap * mmap);

#define roy_mmap_at(mmap, value_type, key)    \
        ((value_type *)((roy_mmap_find((mmap), (key))) ? (roy_mmap_find((mmap), (key))) : NULL))

/* CAPACITY */

// Returns the number of elements in 'mmap'.
size_t roy_mmap_size(const RoyMMap * mmap);

// Returns whether there is any elements in 'mmap'.
bool roy_mmap_empty(const RoyMMap * mmap);

/* MODIFIERS */

// Adds a 'key_size'-sized key contains a 'value_size'-sized value into 'mmap' by ascending order.
RoyMMap * roy_mmap_insert(RoyMMap * mmap, const void * key, const void * value);

// Removes the element equals to 'key' from 'mmap'.
RoyMMap * roy_mmap_erase(RoyMMap * mmap, const void * key);

// Removes all the element from 'mmap'.
RoyMMap * roy_mmap_clear(RoyMMap * mmap);

/* LOOKUP */

RoyMMap * roy_mmap_find(RoyMMap * mmap, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoyMMap * roy_mmap_lower_bound(RoyMMap * mmap, const void * key, size_t key_size, int (*comp)(const void *, const void *));

RoyMMap * roy_mmap_upper_bound(RoyMMap * mmap, const void * key, size_t key_size, int (*comp)(const void *, const void *));

/* TRAVERSE */

// Traverses all elements in 'mmap' using 'operate'.
void roy_mmap_for_each(RoyMMap * mmap, void(* operate)(void *));

// Traverses all elements whichever meets 'condition' in 'mmap' using 'operate'.
void roy_mmap_for_which(RoyMMap * mmap, bool(* condition)(const void *), void(* operate)(void *));

#endif // ROYMMAP_H