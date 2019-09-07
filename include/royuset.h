#ifndef ROYUSET_H
#define ROYUSET_H

#include "royinit.h"
#include "royslist.h"
#include <stdint.h>

struct RoyUSet_ {
  size_t      bucket_count;
  size_t      element_size;
  size_t      size;
  uint64_t    seed;
  uint64_t (* hash)(const void * key, size_t key_size, uint64_t seed);
  int      (* compare)(const void * key1, const void * key2);
  RoySList ** buckets;
};

// RoyUSet (aka 'Unordered Set' / 'Hash Set'): an associative container that contains a set of unique objects.
// Search, insertion, and removal have average constant-time complexity.
// Elements are not sorted in any particular order, but organized into buckets,
// which bucket an element is placed into depends entirely on the hash of its value.
// Do not modify any elements, or it's hash could be changed and the container could be corrupted.
typedef struct RoyUSet_ RoyUSet;

/* CONSTRUCTION & DESTRCUTION */

// Returns a pointer to a newly build RoyUSet.
// using a hash seed, a hash function and a compare function(NULL if you want to use default versions).
RoyUSet * roy_uset_new(size_t bucket_count, size_t element_size, uint64_t seed, uint64_t(* hash)(const void *, size_t, uint64_t), int(* compare)(const void *, const void *));

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'uset', or memory leak will occur.)
void roy_uset_delete(RoyUSet * uset);

/* ELEMENT ACCESS */

// Returns an pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
const void * roy_uset_const_pointer(const RoyUSet * uset, int bucket_index, int bucket_position);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_uset_element(void * dest, RoyUSet * uset, int bucket_index, int bucket_position);


// Returns an typed pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
#define roy_uset_at(uset, element_type, bucket_index, bucket_position) \
        ((element_type *)(roy_uset_const_pointer(uset, bucket_index, bucket_position)))

/* CAPACITY */

// Returns the number of elements in 'uset'.
size_t roy_uset_size(const RoyUSet * uset);

// Returns whether there is any elements in 'uset'.
bool roy_uset_empty(const RoyUSet * uset);

/* MODIFIERS */

// Hashes an element named 'data' into 'uset'.
RoyUSet * roy_uset_insert(RoyUSet * uset, const void * data);

// Removes an element which is the 'bucket_position'-th one on 'bucket_index'-th buckets of 'uset'.
RoyUSet * roy_uset_erase(RoyUSet * uset, int bucket_index, int bucket_position);

// Removes all elements in 'uset' equal to 'data'.
RoyUSet * roy_uset_remove(RoyUSet * uset, const void * data);

// Removes all elements from 'uset'.
RoyUSet * roy_uset_clear(RoyUSet * uset);

/* LOOKUPS */

// Finds an element equivalent to 'key'.
const void * roy_uset_find(const RoyUSet * uset, const void * data);

/* HASH SET SPECIFIC */

// Returns the number of buckets in 'uset'.
size_t roy_uset_bucket_count(const RoyUSet * uset);

// Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_uset_bucket_size(const RoyUSet * uset, int bucket_index);

// Returns the index of the buckets for key 'data' calculated by hash function of 'uset'.
int64_t roy_uset_bucket(const RoyUSet * uset, const void * data);

// Returns the average number of elements per buckets.
double roy_uset_load_factor(const RoyUSet * uset);

// Sets the number of buckets to count and rehashes 'uset'.
RoyUSet * roy_uset_rehash(RoyUSet * uset, size_t bucket_count, uint64_t seed);

/* TRAVERSE */

// Traverses all elements in 'uset' using 'operate'.
void roy_uset_for_each(RoyUSet * uset, void (*oeprate)(void *));

// Traverses all elements whichever meets 'condition' in 'uset' using 'operate'.
void roy_uset_for_which(RoyUSet * uset, bool (*condition)(const void *), void (*oeprate)(void *));

#endif // ROYUSET_H