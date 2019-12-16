#ifndef ROYUMAP_H
#define ROYUMAP_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "trivials/royinit.h"
#include "trivials/roypair.h"
#include "royuset.h"

struct RoyUMap_ {
  RoyUSet * uset;
};

/**
 * @brief RoyUMap [aka Unordered Map] is an associative container that contains key-value pairs with unique keys.
 * Search, insertion, and removal of elements have average constant-time complexity.
 * Internally, the elements are not sorted in any particular order, but organized into buckets.
 * Which bucket an element is placed into depends entirely on the hash of its key.
 * This allows fast access to individual elements, since once the hash is computed, it refers to the exact bucket the element is placed into.
 */
typedef struct RoyUMap_ RoyUMap;


/* CONSTRUCTION & DESTRUCTION */

/**
 * @brief Creates a RoyUMap.
 * @param seed - a hash seed.
 * @param hash - a hash function, NULL to use the default MurmurHash.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return a pointer to a newly build RoyUMap.
 */
RoyUMap * roy_umap_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyUSet - 'umap' itself.
 * @note - Always call this function after the work is done by the given 'uset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_umap_delete(RoyUMap * umap);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified RoyPair.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a const pointer to the specified RoyPair.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'umap' is empty.
 */
const RoyPair * roy_umap_cpointer(const RoyUMap * umap, size_t bucket_index, size_t bucket_position);

/* CAPACITY */

/// @brief Returns the number of elements in 'umap'.
size_t roy_umap_size(const RoyUMap * umap);

/**
 * @brief Checks whether 'umap' is empty.
 * @retval true - there is no element in 'umap'.
 * @retval false - otherwise.
 */
bool roy_umap_empty(const RoyUMap * umap);

/* MODIFIERS */

/**
 * @brief Hashes a RoyPair combined by 'key' and 'value' into 'umap', if 'umap' doesn't already contain an element with an equivalent key.
 * @param key - a pointer to the new key.
 * @param key_size - total memory the new key takes.
 * @param comparer - a function to compare two keys, acting like <=> operator in C++.
 * @return true - the insertion is successful.
 * @return false - 'umap' already contain an element with an equivalent key.
 * @note - The behavior is undefined if 'key' or 'value' is uninitialized.
 */
bool roy_umap_insert(RoyUMap * umap, void * key, size_t key_size, void * value);

/**
 * @brief Removes specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return true - the removal is successful.
 * @return false - 'bucket_index' or 'bucket_position' exceeds, or 'umap' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_umap_erase(RoyUMap * umap, size_t bucket_index, size_t bucket_position);

/**
 * @brief Removes all RoyPairs with key equivalent to 'key'.
 * @param key - a pointer to the new key.
 * @param key_size - total memory the new key takes.
 * @return the number of elements being removed from 'umap'.
 * (since there are no duplicated RoyPairs in 'umap', the return value would be no more than 1.)
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_umap_remove(RoyUMap * umap, const void * key, size_t key_size);

/**
 * @brief Removes all the elements from 'umap'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_umap_clear(RoyUMap * umap);

/* LOOKUPS */

/**
 * @brief Finds the RoyPair with key equivalent to 'key'.
 * @param key - a pointer to the comparable key.
 * @param key_size - total memory the key takes.
 * @return The const pointer to the value of the target RoyPair.
 */
const void * roy_umap_find(const RoyUMap * umap, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

/// @brief Returns the number of buckets in 'umap'.
size_t roy_umap_bucket_count(const RoyUMap * umap);

/// @brief Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_umap_bucket_size(const RoyUMap * umap, size_t bucket_index);

/**
 * @param key - a pointer to the comparable key.
 * @param key_size - total memory the key takes.
 * @return the index of the buckets for 'key' calculated by hash function of 'umap'.
 */
int64_t roy_umap_bucket(const RoyUMap * umap, const void * data, size_t data_size);

/**
 * @brief Returns the average number of elements per buckets,
 * that is, size() divided by bucket_count().
 */
double roy_umap_load_factor(const RoyUMap * umap);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'umap'.
 * @param operate - a function for element traversing.
 */
void roy_umap_for_each(RoyUMap * umap, ROperate oeprate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'umap'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_umap_for_which(RoyUMap * umap, RCondition condition, ROperate operate);

#endif // ROYUMAP_H
