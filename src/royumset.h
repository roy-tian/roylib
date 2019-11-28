#ifndef ROYUMSET_H
#define ROYUMSET_H

#include "trivials/royinit.h"
#include "royslist.h"

struct RoyUMSet_ {
  RoySList ** buckets;
  uint64_t    seed;
  RHash       hash;
  RCompare    comparer;
  ROperate    deleter;
  size_t      bucket_count;
  size_t      size;
};

// RoyUMSet (aka 'Unordered Multi-Set' / 'Hash Multi-Set'): an associative container that contains a set of objects.
// Search, insertion, and removal have average constant-time complexity.
// Elements are not sorted in any particular order, but organized into buckets,
// which bucket an element is placed into depends entirely on the hash of its value.
// Do not modify any elements, or it's hash could be changed and the container could be corrupted.
typedef struct RoyUMSet_ RoyUMSet;

/* CONSTRUCTION & DESTRUCTION */

// Returns a pointer to a newly build RoyUMSet.
// using a hash seed, a hash function and a comparer function(NULL if you want to use default versions).
RoyUMSet * roy_umset_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'umset', or memory leak will occur.)
void roy_umset_delete(RoyUMSet * umset);

/* ELEMENT ACCESS */

// Returns an pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
const void * roy_umset_cpointer(const RoyUMSet * umset, int bucket_index, int bucket_position);

// Returns an typed pointer to the element which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
#define roy_umset_at(umset, element_type, bucket_index, bucket_position) \
        ((element_type *)(roy_umset_cpointer(umset, bucket_index, bucket_position)))

/* CAPACITY */

// Returns the number of elements in 'umset'.
size_t roy_umset_size(const RoyUMSet * umset);

// Returns whether there is any elements in 'umset'.
bool roy_umset_empty(const RoyUMSet * umset);

/* MODIFIERS */

// Hashes an element named 'data' into 'umset'.
void roy_umset_insert(RoyUMSet * umset, void * data, size_t data_size);

// Removes an element which is the 'bucket_position'-th one on 'bucket_index'-th buckets of 'umset'.
bool roy_umset_erase(RoyUMSet * umset, int bucket_index, int bucket_position);

// Removes all elements in 'umset' equal to 'data'.
size_t roy_umset_remove(RoyUMSet * umset, const void * data, size_t data_size);

// Removes all elements from 'umset'.
void roy_umset_clear(RoyUMSet * umset);

/* LOOKUPS */

// Finds an element equivalent to 'key'.
const void * roy_umset_find(const RoyUMSet * umset, const void * data, size_t data_size);

/* HASH SET SPECIFIC */

// Returns the number of buckets in 'umset'.
size_t roy_umset_bucket_count(const RoyUMSet * umset);

// Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_umset_bucket_size(const RoyUMSet * umset, int bucket_index);

// Returns the index of the buckets for key 'data' calculated by hash function of 'umset'.
int64_t roy_umset_bucket(const RoyUMSet * umset, const void * data, size_t data_size);

// Returns the average number of elements per buckets.
double roy_umset_load_factor(const RoyUMSet * umset);

/* TRAVERSE */

// Traverses all elements in 'umset' using 'operate'.
void roy_umset_for_each(RoyUMSet * umset, ROperate oeprate);

// Traverses all elements whichever meets 'condition' in 'umset' using 'operate'.
void roy_umset_for_which(RoyUMSet * umset, RCondition condition, ROperate oeprate);

#endif // ROYUMSET_H