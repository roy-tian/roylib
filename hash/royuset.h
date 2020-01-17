#ifndef ROYUSET_H
#define ROYUSET_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "../trivial/royinit.h"
#include "../list/royslist.h"

struct RoyUSet_ {
  RoySList ** buckets;
  uint64_t    seed;
  RHash       hash;
  RCompare    comparer;
  ROperate    deleter;
  size_t      bucket_count;
  size_t      size;
};

/**
 * @brief RoyUSet (aka 'Unordered Set' / 'Hash Set'): an associative container that contains a set of unique objects.
 * Search, insertion, and removal have average constant-time complexity.
 * Elements are not sorted in any particular order, but organized into buckets,
 * which bucket an element is placed into depends entirely on the hash of its value.
 * @note - Do not modify any elements, or it's hash could be changed and the container could be corrupted.
 */
typedef struct RoyUSet_ RoyUSet;

/* CONSTRUCTION & DESTRUCTION */

/**
 * @brief Creates a RoyUSet.
 * @param seed - a hash seed.
 * @param hash - a hash function, NULL to use the default MurmurHash.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return a pointer to a newly build RoyUSet.
 */
RoyUSet * roy_uset_new(size_t bucket_count, uint64_t seed, RHash hash, RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyUSet - 'uset' itself.
 * @note - Always call this function after the work is done by the given 'uset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_uset_delete(RoyUSet * uset);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a const pointer to the specified element.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'uset' is empty.
 */
const void * roy_uset_cpointer(const RoyUSet * uset, size_t bucket_index, size_t bucket_position);

/**
 * @brief Accesses specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return a typed pointer to the specified element.
 * @return NULL - 'bucket_index' or 'bucket_position' exceeds, or 'uset' is empty.
 */
#define roy_uset_at(uset, bucket_index, bucket_position, element_type) \
        ((element_type *)roy_uset_cpointer(uset, bucket_index, bucket_position))

/* CAPACITY */

/// @brief Returns the number of elements in 'uset'.
size_t roy_uset_size(const RoyUSet * uset);

/**
 * @brief Checks whether 'uset' is empty.
 * @retval true - there is no element in 'uset'.
 * @retval false - otherwise.
 */
bool roy_uset_empty(const RoyUSet * uset);

/* MODIFIERS */

/**
 * @brief Hashes an element into 'uset', if 'uset' doesn't already contain an element with an equivalent key.
 * @param key - a pointer to the new element.
 * @param key_size - total memory the new element takes.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @return true - the insertion is successful.
 * @return false - 'uset' already contain an element with an equivalent key.
 * @note - The behavior is undefined if 'key' is uninitialized.
 */
bool roy_uset_insert(RoyUSet * uset, void * key, size_t key_size);

/**
 * @brief Removes specified element.
 * @param bucket_index - the serial number of the target bucket.
 * @param bucket_position - the position where the element takes place in the target bucket.
 * @return true - the removal is successful.
 * @return false - 'bucket_index' or 'bucket_position' exceeds, or 'uset' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_uset_erase(RoyUSet * uset, size_t bucket_index, size_t bucket_position);

/**
 * @brief Removes all elements equivalent to 'key'
 * @param key - a pointer to the new element.
 * @param key_size - total memory the new element takes.
 * @return the number of elements being removed from 'uset'.
 * (since there are no duplicated elements in 'uset', the return value would be no more than 1.)
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_uset_remove(RoyUSet * uset, const void * key, size_t key_size);

/**
 * @brief Removes all the elements from 'uset'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_uset_clear(RoyUSet * uset);

/* LOOKUPS */

/**
 * @brief Finds the element equivalent to 'key'.
 * @param key - a pointer to the comparable element.
 * @param key_size - total memory the element takes.
 * @return The const pointer to the target element.
 */
const void * roy_uset_find(const RoyUSet * uset, const void * key, size_t key_size);

/* HASH SET SPECIFIC */

/// @brief Returns the number of buckets in 'uset'.
size_t roy_uset_bucket_count(const RoyUSet * uset);

/// @brief Returns the number of elements in the buckets with index 'bucket_index'.
size_t roy_uset_bucket_size(const RoyUSet * uset, size_t bucket_index);

/**
 * @param key - a pointer to the comparable element.
 * @param key_size - total memory the element takes.
 * @return the index of the buckets for key 'key' calculated by hash function of 'uset'.
 */
int64_t roy_uset_bucket(const RoyUSet * uset, const void * key, size_t key_size);

/**
 * @brief Returns the average number of elements per buckets,
 * that is, size() divided by bucket_count().
 */
double roy_uset_load_factor(const RoyUSet * uset);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'uset'.
 * @param operate - a function for element traversing.
 */
void roy_uset_for_each(RoyUSet * uset, ROperate oeprate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'uset'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_uset_for_which(RoyUSet * uset, RCondition condition, ROperate operate);

#endif // ROYUSET_H