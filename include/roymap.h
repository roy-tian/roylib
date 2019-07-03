#ifndef ROYMAP_H
#define ROYMAP_H

#include "royinit.h"
#include "royset.h"

struct _RoyMap {
  RoySet * root;
  size_t   key_size;
  size_t   value_size;
  int   (* comp)(const void *, const void *);
};

// RoyMap: an associative container that contains a sorted map of unique objects of type Key.
// Sorting is done using the key comparison function 'comp'. Search, removal, and insertion operations have logarithmic complexity.
typedef struct _RoyMap RoyMap;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoyMap. 
RoyMap * roy_map_new(size_t key_size, size_t value_size, int (* comp)(const void *, const void *));

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'map', or memory leak will occur.)
void roy_map_delete(RoyMap * map);

/* ELEMENT ACCESS */

// Returns an pointer to the value of the minimum element of 'map'.
void * roy_map_pmin(RoyMap * map);

// Returns an pointer to the value of the maximum element of 'map'.
void * roy_map_pmax(RoyMap * map);

// Returns a const pointer to the value of the minimum element of 'map'.
const void * roy_map_const_pmin(const RoyMap * map);

// Returns a const pointer to the value of the maximum element of 'map'.
const void * roy_map_const_pmax(const RoyMap * map);

#define roy_map_at(map, value_type, key) (value_type *)roy_map_find((map), (key))

/* CAPACITY */

// Returns the number of elements in 'map'.
size_t roy_map_size(const RoyMap * map);

// Returns whether there is any elements in 'map'.
bool roy_map_empty(const RoyMap * map);

/* MODIFIERS */

// Adds a 'key_size'-sized key contains a 'value_size'-sized value into 'map' by ascending order.
RoyMap * roy_map_insert(RoyMap * map, const void * key, const void * value);

// Removes the element equals to 'key' from 'map'.
RoyMap * roy_map_erase(RoyMap * map, const void * key);

// Removes all the element from 'map'.
RoyMap * roy_map_clear(RoyMap * map);

/* LOOKUP */

void * roy_map_find(RoyMap * map, const void * key);

/* TRAVERSE */

// Traverses all elements in 'map' using 'operate'.
void roy_map_for_each(RoyMap * map, void(* operate)(void *));

// Traverses all elements whichever meets 'condition' in 'map' using 'operate'.
void roy_map_for_which(RoyMap * map, bool(* condition)(const void *), void(* operate)(void *));

#endif // ROYMAP_H