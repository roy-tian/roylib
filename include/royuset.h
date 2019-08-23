#ifndef ROYUSET_H
#define ROYUSET_H

#include "royinit.h"
#include "royvector.h"

struct _RoyUSet {
  size_t   (* hash)(const void * elem);
  bool     (* equal)(const void * elem1, const void * elem2);
  size_t      capacity;
  size_t      element_size;
  RoyVector * table;
};

// RoyUSet (aka 'Unordered Set' / 'Hash Set'): an associative container that contains a set of unique objects.
// Search, insertion, and removal have average constant-time complexity.
// Elements are not sorted in any particular order, but organized into buckets,
// which bucket an element is placed into depends entirely on the hash of its value.
// Do not modify any elements, or it's hash could be changed and the container could be corrupted.
typedef struct _RoyUSet RoyUSet;

RoyUSet * roy_uset_new(size_t capacity, size_t element_size, size_t(* hash)(const void *),bool(* equal)(const void *, const void *));

void roy_uset_delete(RoyUSet * uset);

#endif // ROYUSET_H