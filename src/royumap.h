#ifndef ROYUMAP_H
#define ROYUMAP_H

#include "trivials/royinit.h"
#include "trivials/roypair.h"
#include "royuset.h"

struct RoyUMap_ {
  RoyUSet * uset;
};

typedef struct RoyUMap_ RoyUMap;


/* CONSTRUCTION & DESTRUCTION */

// Returns a pointer to a newly build RoyUMap.
// using a hash seed, a hash function and a comparer function(NULL if you want to use default versions).
RoyUMap * roy_umap_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

// De-allocates all the memory allocated.
// (Always call this function after the work is done by the given 'umap', or memory leak will occur.)
void roy_umap_delete(RoyUMap * umap);

/* ELEMENT ACCESS */

// Returns an pointer to the pair which is the 'bucket_position'-th one on 'bucket_index'-th buckets.
// (Returns NULL if position is out of range.)
const RoyPair * roy_umap_cpointer(const RoyUMap * umap, size_t bucket_index, size_t bucket_position);

/* CAPACITY */

// Returns the number of elements in 'umap'.
size_t roy_umap_size(const RoyUMap * umap);

// Returns whether there is any elements in 'umap'.
bool roy_umap_empty(const RoyUMap * umap);

/* MODIFIERS */

// Hashes a pair conbined by 'key' and 'value' into 'umap'.
bool roy_umap_insert(RoyUMap * umap, void * key, size_t key_size, void * value);

// Removes a pair which is the 'bucket_position'-th one on 'bucket_index'-th buckets of 'umap'.
bool roy_umap_erase(RoyUMap * umap, size_t bucket_index, size_t bucket_position);

// Removes the pair in 'umap' of which 'key' is equal to given 'key'.
size_t roy_umap_remove(RoyUMap * umap, const void * key, size_t key_size);

// Removes all elements from 'umap'.
void roy_umap_clear(RoyUMap * umap);

/* LOOKUPS */

// Finds the value of pair of which 'key' equivalent to given 'key'.
const void * roy_umap_find(const RoyUMap * umap, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

// Returns the number of buckets in 'umap'.
size_t roy_umap_bucket_count(const RoyUMap * umap);

// Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_umap_bucket_size(const RoyUMap * umap, size_t bucket_index);

// Returns the index of the buckets for key 'data' calculated by hash function of 'umap'.
int64_t roy_umap_bucket(const RoyUMap * umap, const void * data, size_t data_size);

// Returns the average number of elements per buckets.
double roy_umap_load_factor(const RoyUMap * umap);

/* TRAVERSE */

// Traverses all elements in 'umap' using 'operate'.
void roy_umap_for_each(RoyUMap * umap, ROperate oeprate);

// Traverses all elements whichever meets 'condition' in 'umap' using 'operate'.
void roy_umap_for_which(RoyUMap * umap, RCondition condition, ROperate operate);

#endif // ROYUMAP_H
