#ifndef ROYUMMAP_H
#define ROYUMMAP_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "trivials/royinit.h"
#include "trivials/roypair.h"
#include "royumset.h"

struct RoyUMMap_ {
  RoyUMSet * umset;
};

typedef struct RoyUMMap_ RoyUMMap;

/* CONSTRUCTION & DESTRUCTION */

// Returns a pointer to a newly build RoyUMMap.
// using a hash seed, a hash function and a comparer function(NULL if you want to use default versions).
RoyUMMap * roy_ummap_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'ummap', or memory leak will occur.)
void roy_ummap_delete(RoyUMMap * ummap);

/* ELEMENT ACCESS */

// Returns an pointer to the pair which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
const RoyPair * roy_ummap_cpointer(const RoyUMMap * ummap, size_t bucket_index, size_t bucket_position);

/* CAPACITY */

// Returns the number of elements in 'ummap'.
size_t roy_ummap_size(const RoyUMMap * ummap);

// Returns whether there is any elements in 'ummap'.
bool roy_ummap_empty(const RoyUMMap * ummap);

/* MODIFIERS */

// Hashes a pair conbined by 'key' and 'value' into 'ummap'.
bool roy_ummap_insert(RoyUMMap * ummap, void * key, size_t key_size, void * value);

// Removes a pair which is the 'bucket_position'-th one on 'bucket_index'-th buckets of 'ummap'.
bool roy_ummap_erase(RoyUMMap * ummap, size_t bucket_index, size_t bucket_position);

// Removes the pair in 'ummap' of which 'key' is equal to given 'key'.
size_t roy_ummap_remove(RoyUMMap * ummap, const void * key, size_t key_size);

// Removes all elements from 'ummap'.
void roy_ummap_clear(RoyUMMap * ummap);

/* LOOKUPS */

// Finds the value of pair of which 'key' equivalent to given 'key'.
const void * roy_ummap_find(const RoyUMMap * ummap, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

// Returns the number of buckets in 'ummap'.
size_t roy_ummap_bucket_count(const RoyUMMap * ummap);

// Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_ummap_bucket_size(const RoyUMMap * ummap, size_t bucket_index);

// Returns the index of the buckets for key 'data' calculated by hash function of 'ummap'.
int64_t roy_ummap_bucket(const RoyUMMap * ummap, const void * data, size_t data_size);

// Returns the average number of elements per buckets.
double roy_ummap_load_factor(const RoyUMMap * ummap);

/* TRAVERSE */

// Traverses all elements in 'ummap' using 'operate'.
void roy_ummap_for_each(RoyUMMap * ummap, ROperate oeprate);

// Traverses all elements whichever meets 'condition' in 'ummap' using 'operate'.
void roy_ummap_for_which(RoyUMMap * ummap, RCondition condition, ROperate operate);

#endif // ROYUMAP_H
