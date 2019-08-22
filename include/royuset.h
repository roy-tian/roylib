#ifndef ROYUSET_H
#define ROYUSET_H

#include "royinit.h"
#include "royslist.h"

struct _RoyUSet {
  size_t  (* hash)(const void * elem, size_t set_size);
  bool    (* equal)(const void * elem1, const void * elem2);
  size_t     size;
  void     * table;
};

// RoyUSet (aka 'Unordered Set' / 'Hash Set'): an associative container that contains a set of unique objects.
// Search, insertion, and removal have average constant-time complexity.
// Elements are not sorted in any particular order, but organized into buckets,
// which bucket an element is placed into depends entirely on the hash of its value.
// Do not modify any elements, or it's hash could be changed and the container could be corrupted.
typedef struct _RoyUSet RoyUSet;



#endif // ROYUSET_H