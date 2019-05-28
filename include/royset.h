#include "royinit.h"

struct _RoySet {
  struct _RoySet * left;
  struct _RoySet * right;
  void           * key;
};

// RoySet: an associative container that contains a sorted set of unique objects of type Key.
// Sorting is done using the key comparison function Compare. Search, removal, and insertion operations have logarithmic complexity.
typedef struct _RoySet RoySet;

/* CONSTRUCTION AND DESTRUCTION */

// Returns a pointer to a newly build RoySet's root for navigating.
RoySet * roy_set_new(void);

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'set', or memory leak will occur.)
void roy_set_delete(RoySet * set);

/* ELEMENT ACCESS */

// Returns an iterator to the minimum element of 'set'.
RoySet * roy_set_min(RoySet * set);

// Returns an iterator to the maximum element of 'set'.
RoySet * roy_set_max(RoySet * set);

// Returns a const iterator to the minimum element of 'set'.
const RoySet * roy_set_const_min(const RoySet * set);

// Returns a const iterator to the maximum element of 'set'.
const RoySet * roy_set_const_max(const RoySet * set);

/* CAPACITY */

// Returns the number of elements in 'set'.
size_t roy_set_size(const RoySet * set);

// Returns whether there is any elements in 'set'.
bool roy_set_empty(const RoySet * set);

/* MODIFIERS */

// Adds an 'key_size'-sized key into 'set' by ascending order.
RoySet * roy_set_insert(RoySet * set, const void * key, size_t key_size, int (*comp)(const void *, const void *));

// Removes the element equals to 'key' from 'set'.
RoySet * roy_set_erase(RoySet * set, const void * key, size_t key_size);

// Removes all the element from 'set'.
RoySet * roy_set_clear(RoySet * set);

/* TRAVERSE */

// Traverses all elements in 'set' using 'iterate'.
void roy_set_for_each(RoySet * set, void(* iterate)(void *));

// Traverses all elements whichever meets 'condition' in 'set' using 'iterate'.
void roy_set_for_which(RoySet * set, bool(* condition)(const void *), void(* iterate)(void *));
