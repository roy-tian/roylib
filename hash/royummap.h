#ifndef ROYUMMAP_H
#define ROYUMMAP_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "../trivials/royinit.h"
#include "../trivials/roypair.h"
#include "royumset.h"

struct RoyUMMap_ {
  RoyUMSet * umset;
};

/**
 * @brief RoyUMMap [aka Unordered Multi-Map] is an associative container that contains key-value pairs, duplicated keys are allowed.
 * Search, insertion, and removal of elements have average constant-time complexity.
 * Internally, the elements are not sorted in any particular order, but organized into buckets.
 * Which bucket an element is placed into depends entirely on the hash of its key.
 * This allows fast access to individual elements, since once the hash is computed, it refers to the exact bucket the element is placed into.
 */
typedef struct RoyUMMap_ RoyUMMap;

/* CONSTRUCTION & DESTRUCTION */

/**
 * @brief Creates a RoyUMMap.
 * @param seed - a hash seed.
 * @param hash - a hash function, NULL to use the default MurmurHash.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return a pointer to a newly build RoyUMMap.
 */
RoyUMMap * roy_ummap_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyUMMap - 'ummap' itself.
 * @note - Always call this function after the work is done by the given 'ummap' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_ummap_delete(RoyUMMap * ummap);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified RoyPair.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a const pointer to the specified RoyPair.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'ummap' is empty.
 */
const RoyPair * roy_ummap_cpointer(const RoyUMMap * ummap, size_t bucket_index, size_t bucket_position);

/* CAPACITY */

/// @brief Returns the number of elements in 'ummap'.
size_t roy_ummap_size(const RoyUMMap * ummap);

/**
 * @brief Checks whether 'ummap' is empty.
 * @retval true - there is no element in 'ummap'.
 * @retval false - otherwise.
 */
bool roy_ummap_empty(const RoyUMMap * ummap);

/* MODIFIERS */

/**
 * @brief Hashes a RoyPair combined by 'key' and 'value' into 'ummap', duplicated keys are allowed.
 * @param key - a pointer to the new key.
 * @param key_size - total memory the new key takes.
 * @param comparer - a function to compare two keys, acting like <=> operator in C++.
 * @note - The behavior is undefined if 'key' or 'value' is uninitialized.
 */
void roy_ummap_insert(RoyUMMap * ummap, void * key, size_t key_size, void * value);

/**
 * @brief Removes specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return true - the removal is successful.
 * @return false - 'bucket_index' or 'bucket_position' exceeds, or 'ummap' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_ummap_erase(RoyUMMap * ummap, size_t bucket_index, size_t bucket_position);

/**
 * @brief Removes all RoyPairs with key equivalent to 'key'.
 * @param key - a pointer to the new key.
 * @param key_size - total memory the new key takes.
 * @return the number of elements being removed from 'ummap'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_ummap_remove(RoyUMMap * ummap, const void * key, size_t key_size);

/**
 * @brief Removes all the elements from 'ummap'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_ummap_clear(RoyUMMap * ummap);

/* LOOKUPS */

/**
 * @brief Finds the first RoyPair with key equivalent to 'key'.
 * @param key - a pointer to the comparable key.
 * @param key_size - total memory the key takes.
 * @return The const pointer to the value of the target RoyPair.
 */
const void * roy_ummap_find(const RoyUMMap * ummap, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

/// @brief Returns the number of buckets in 'ummap'.
size_t roy_ummap_bucket_count(const RoyUMMap * ummap);

/// @brief Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_ummap_bucket_size(const RoyUMMap * ummap, size_t bucket_index);

/**
 * @param key - a pointer to the comparable key.
 * @param key_size - total memory the key takes.
 * @return the index of the buckets for 'key' calculated by hash function of 'ummap'.
 */
int64_t roy_ummap_bucket(const RoyUMMap * ummap, const void * data, size_t data_size);

/**
 * @brief Returns the average number of elements per buckets,
 * that is, size() divided by bucket_count().
 */
double roy_ummap_load_factor(const RoyUMMap * ummap);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'ummap'.
 * @param operate - a function for element traversing.
 */
void roy_ummap_for_each(RoyUMMap * ummap, ROperate oeprate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'ummap'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_ummap_for_which(RoyUMMap * ummap, RCondition condition, ROperate operate);

#endif // ROYUMAP_H
