#ifndef ROYMMAP_H
#define ROYMMAP_H

#include "../trivial/royinit.h"
#include "roymset.h"

struct RoyMMap_ {
  RoyMSet  * root;
  RCompare   comparer;
  ROperate   deleter;
};

/**
 * @brief RoyMMap[aka Multi-Map]: an associative container that contains a sorted multi map of objects of type Key.
 * Sorting is done using the key comparison function 'comparer'.
 * Search, removal, and insertion operations have logarithmic complexity.
 */
typedef struct RoyMMap_ RoyMMap;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyMMap.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyMMap.
 * @note The behavior is undefined if any immature RoyMaps are operated.
 */
RoyMMap * roy_mmap_new(RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyMMap - 'mmap' itself.
 * @note - Always call this function after the work is done by the given 'mmap' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mmap_delete(RoyMMap * mmap);

/* ELEMENT ACCESS */

/**
 * @return a pointer to the value of the first minimum element of 'mmap'.
 * @return NULL - 'mmap' is empty.
 */
void * roy_mmap_min(RoyMMap * mmap);

/**
 * @return a const pointer to the value of the first minimum element of 'mmap'.
 * @return NULL - 'mmap' is empty.
 */
const void * roy_mmap_cmin(const RoyMMap * mmap);

/**
 * @return a pointer to the value of the last maximum element of 'mmap'.
 * @return NULL - 'mmap' is empty.
 */
void * roy_mmap_max(RoyMMap * mmap);

/**
 * @return a const pointer to the value of the last maximum element of 'mmap'.
 * @return NULL - 'mmap' is empty.
 */
const void * roy_mmap_cmax(const RoyMMap * mmap);

/**
 * @brief Accesses specified value.
 * @return a typed pointer to the mapped value of the first element with key equivalent to 'key'.
 * @return NULL - 'map' does not have an element with the specified key.
 */
#define roy_mmap_at(mmap, value_type, key) \
        ((value_type *)roy_mmap_find((mmap), (key)))

/* CAPACITY */

/// @brief Returns the number of elements in 'mmap'.
size_t roy_mmap_size(const RoyMMap * mmap);

/**
 * @brief Checks whether 'mmap' is empty.
 * @retval true - there is no element in 'mmap'.
 * @retval false - otherwise.
 */
bool roy_mmap_empty(const RoyMMap * mmap);

/* MODIFIERS */

/**
 * @brief Inserts a 'key'-'value' pair into 'mmap' in ascending order by 'key', duplicated pairs are allowed.
 * @param key - a pointer to the new key.
 * @param value - a pointer to the new value.
 * @return the 'mmap' after the operation.
 * @note - The behavior is undefined if 'key' or 'value' is uninitialized.
 */
RoyMMap * roy_mmap_insert(RoyMMap * mmap, void * key, void * value);

/**
 * @brief Removes all elements with an equivalent key from 'mmap'.
 * @param key - a key for comparision.
 * @return the 'mmap' after the operation.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
RoyMMap * roy_mmap_remove(RoyMMap * mmap, const void * key);

/**
 * @brief Removes all the elements from 'mmap'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mmap_clear(RoyMMap * mmap);

/* LOOKUP */

/**
 * @param key - a pointer to the element with a comparable 'key'.
 * @return the number of elements equivalent to 'key'.
 */
size_t roy_mmap_count(const RoyMMap * mmap, const void * key);

/**
 * @brief Finds the first element with an equivalent key.
 * @param key - a key for comparision.
 * @return a pointer to the value of target element.
 */
void * roy_mmap_find(RoyMMap * mmap, const void * key);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'mmap' in ascending order.
 * @param operate - a function for element traversing.
 */
void roy_mmap_for_each(RoyMMap * mmap, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'mmap'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_mmap_for_which(RoyMMap * mmap, RCondition condition, ROperate operate);

#endif // ROYMMAP_H