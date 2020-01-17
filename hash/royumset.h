#ifndef ROYUMSET_H
#define ROYUMSET_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "../trivials/royinit.h"
#include "../list/royslist.h"

struct RoyUMSet_ {
  RoySList ** buckets;
  uint64_t    seed;
  RHash       hash;
  RCompare    comparer;
  ROperate    deleter;
  size_t      bucket_count;
  size_t      size;
};

/**
 * RoyUMSet (aka 'Unordered Multi-Set' / 'Hash Multi-Set'): an associative container that contains a set of objects.
 * Search, insertion, and removal have average constant-time complexity.
 * Elements are not sorted in any particular order, but organized into buckets,
 * which bucket an element is placed into depends entirely on the hash of its value.
 * @note - Do not modify any elements, or it's hash could be changed and the container could be corrupted.
 */
typedef struct RoyUMSet_ RoyUMSet;

/* CONSTRUCTION & DESTRUCTION */

/**
 * @brief Creates a RoyUMset.
 * @param seed - a hash seed.
 * @param hash - a hash function, NULL to use the default MurmurHash.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return a pointer to a newly build RoyUMSet.
 */
RoyUMSet * roy_umset_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyUMSet - 'umset' itself.
 * @note - Always call this function after the work is done by the given 'umset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_umset_delete(RoyUMSet * umset);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a const pointer to the specified element.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'umset' is empty.
 */
const void * roy_umset_cpointer(const RoyUMSet * umset, int bucket_index, int bucket_position);

/**
 * @brief Accesses specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a typed pointer to the specified element.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'umset' is empty.
 */
#define roy_umset_at(umset, element_type, bucket_index, bucket_position) \
        ((element_type *)(roy_umset_cpointer(umset, bucket_index, bucket_position)))

/* CAPACITY */

/// @brief Returns the number of elements in 'umset'.
size_t roy_umset_size(const RoyUMSet * umset);

/**
 * @brief Checks whether 'uset' is empty.
 * @retval true - there is no element in 'uset'.
 * @retval false - otherwise.
 */
bool roy_umset_empty(const RoyUMSet * umset);

/* MODIFIERS */

/**
 * @brief Hashes an element into 'umset', duplicated keys are allowed.
 * @param key - a pointer to the new element.
 * @param key_size - total memory the new element takes.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @note - The behavior is undefined if 'key' is uninitialized.
 */
void roy_umset_insert(RoyUMSet * umset, void * key, size_t key_size);

/**
 * @brief Removes specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return true - the removal is successful.
 * @return false - 'bucket_index' or 'bucket_position' exceeds, or 'umset' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_umset_erase(RoyUMSet * umset, int bucket_index, int bucket_position);

/**
 * @brief Removes all elements equivalent to 'key'.
 * @param key - a pointer to the new element.
 * @param key_size - total memory the new element takes.
 * @return the number of elements being removed from 'umset'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_umset_remove(RoyUMSet * umset, const void * key, size_t key_size);

/**
 * @brief Removes all the elements from 'umset'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_umset_clear(RoyUMSet * umset);

/* LOOKUPS */

/**
 * @brief Finds the first element equivalent to 'key'.
 * @param key - a pointer to the comparable element.
 * @param key_size - total memory the element takes.
 * @return The const pointer to the target element.
 */
const void * roy_umset_find(const RoyUMSet * umset, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

/// @brief Returns the number of buckets in 'umset'.
size_t roy_umset_bucket_count(const RoyUMSet * umset);

/// @brief Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_umset_bucket_size(const RoyUMSet * umset, int bucket_index);

/**
 * @param key - a pointer to the comparable element.
 * @param key_size - total memory the element takes.
 * @return the index of the buckets for key 'key' calculated by hash function of 'umset'.
 */
int64_t roy_umset_bucket(const RoyUMSet * umset, const void * key, size_t key_size);

/**
 * @brief Returns the average number of elements per buckets,
 * that is, size() divided by bucket_count().
 */
double roy_umset_load_factor(const RoyUMSet * umset);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'umset'.
 * @param operate - a function for element traversing.
 */
void roy_umset_for_each(RoyUMSet * umset, ROperate oeprate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'umset'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_umset_for_which(RoyUMSet * umset, RCondition condition, ROperate oeprate);

#endif // ROYUMSET_H