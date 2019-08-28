#ifndef ROYUMSET_H
#define ROYUMSET_H

#include "royinit.h"
#include "royslist.h"
#include <stdint.h>

struct RoyUMSet_ {
  size_t      bucket_count;
  size_t      element_size;
  size_t      size;
  uint64_t    seed;
  uint64_t (* hash)(const void * key, size_t key_size, uint64_t seed);
  int      (* compare)(const void * key1, const void * key2);
  RoySList ** buckets;
};

// RoyUMSet (aka 'Unordered Multi-Set' / 'Hash Multi-Set'): an associative container that contains a set of objects.
// Search, insertion, and removal have average constant-time complexity.
// Elements are not sorted in any particular order, but organized into buckets,
// which bucket an element is placed into depends entirely on the hash of its value.
// Do not modify any elements, or it's hash could be changed and the container could be corrupted.
typedef struct RoyUMSet_ RoyUMSet;

/* CONSTRUCTION & DESTRCUTION */

// Returns a pointer to a newly build RoyUMSet.
// using a hash seed, a hash function and a compare function(NULL if you want to use default versions).
RoyUMSet * roy_umset_new(size_t bucket_count, size_t element_size, uint64_t seed, uint64_t(* hash)(const void *, size_t, uint64_t), int(* compare)(const void *, const void *));

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'umset', or memory leak will occur.)
void roy_umset_delete(RoyUMSet * umset);

/* ELEMENT ACCESS */

// Returns an pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
const void * roy_umset_const_pointer(const RoyUMSet * umset, int bucket_index, int bucket_position);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_umset_element(void * dest, RoyUMSet * umset, int bucket_index, int bucket_position);


// Returns an typed pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
#define roy_umset_at(umset, element_type, bucket_index, bucket_position) \
        ((element_type *)(roy_umset_const_pointer(umset, bucket_index, bucket_position)))

/* CAPACITY */

// Returns the number of elements in 'umset'.
size_t roy_umset_size(const RoyUMSet * umset);

// Returns whether there is any elements in 'umset'.
bool roy_umset_empty(const RoyUMSet * umset);

/* MODIFIERS */

// Hashes an element named 'data' into 'umset'.
RoyUMSet * roy_umset_insert(RoyUMSet * umset, const void * data);

// Removes an element which is the 'bucket_position'-th one on 'bucket_index'-th buckets of 'umset'.
RoyUMSet * roy_umset_erase(RoyUMSet * umset, int bucket_index, int bucket_position);

// Removes all elements in 'umset' equal to 'data'.
RoyUMSet * roy_umset_remove(RoyUMSet * umset, const void * data);

// Removes all elements from 'umset'.
RoyUMSet * roy_umset_clear(RoyUMSet * umset);

/* LOOKUPS */

// Finds an element equivalent to 'key'.
const void * roy_umset_find(const RoyUMSet * umset, const void * data);

/* HASH SET SPECIFIC */

// Returns the number of buckets in 'umset'.
size_t roy_umset_bucket_count(const RoyUMSet * umset);

// Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_umset_bucket_size(const RoyUMSet * umset, int bucket_index);

// Returns the index of the buckets for key 'data' calculated by hash function of 'umset'.
int64_t roy_umset_bucket(const RoyUMSet * umset, const void * data);

// Returns the average number of elements per buckets.
double roy_umset_load_factor(const RoyUMSet * umset);

// Sets the number of buckets to count and rehashes 'umset'.
RoyUMSet * roy_umset_rehash(RoyUMSet * umset, size_t bucket_count, uint64_t seed);

/* TRAVERSE */

// Traverses all elements in 'umset' using 'operate'.
void roy_umset_for_each(RoyUMSet * umset, void (*oeprate)(void *));

// Traverses all elements whichever meets 'condition' in 'umset' using 'operate'.
void roy_umset_for_which(RoyUMSet * umset, bool (*condition)(const void *), void (*oeprate)(void *));

#endif // ROYUMSET_H