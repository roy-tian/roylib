#ifndef ROYMAP_H
#define ROYMAP_H

#include "../util/rpre.h"
#include "royset.h"

struct RoyMap_ {
  RoySet   * root;
  RCompare   comparer;
  ROperate   deleter;
};

/**
 * @brief RoyMap: an associative container that contains a sorted map of unique objects of type Key.
 * Sorting is done using the key comparison function 'comparer'.
 * Search, removal, and insertion operations have logarithmic complexity.
 */
typedef struct RoyMap_ RoyMap;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyMap.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyMap.
 * @note The behavior is undefined if any immature RoyMaps are operated.
 */
RoyMap * roy_map_new(RCompare comparer, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyMap - 'map' itself.
 * @note - Always call this function after the work is done by the given 'map' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_map_delete(RoyMap * map, void * user_data);

/* ELEMENT ACCESS */

/**
 * @return a pointer to the value of the minimum element of 'map'.
 * @return NULL - 'map' is empty.
 */
void * roy_map_min(RoyMap * map);

/**
 * @return a const pointer to the value of the minimum element of 'map'.
 * @return NULL - 'map' is empty.
 */
const void * roy_map_cmin(const RoyMap * map);

/**
 * @return a pointer to the value of the maximum element of 'map'.
 * @return NULL - 'map' is empty.
 */
void * roy_map_max(RoyMap * map);

/**
 * @return a const pointer to the value of the maximum element of 'map'.
 * @return NULL - 'map' is empty.
 */
const void * roy_map_cmax(const RoyMap * map);

/**
 * @brief Accesses specified value.
 * @return a typed pointer to the mapped value of the element with key equivalent to 'key'.
 * @return NULL - 'map' does not have an element with the specified key.
 */
#define roy_map_at(map, key, value_type) \
        ((value_type *)roy_map_find((map), (key)))

/* CAPACITY */

/// @brief Returns the number of elements in 'map'.
size_t roy_map_size(const RoyMap * map);

/**
 * @brief Checks whether 'map' is empty.
 * @retval true - there is no element in 'map'.
 * @retval false - otherwise.
 */
bool roy_map_empty(const RoyMap * map);

/* MODIFIERS */

/**
 * @brief Inserts a 'key'-'value' pair into 'map' in ascending order by 'key',
 * if 'map' doesn't already contain an element with an equivalent key.
 * @param key - a pointer to the new key.
 * @param value - a pointer to the new value.
 * @return the 'map' after the operation.
 * @note - The behavior is undefined if 'key' or 'value' is uninitialized.
 */
RoyMap * roy_map_insert(RoyMap * restrict map, void * restrict key, void * restrict value);

/**
 * @brief Removes the element with an equivalent key from 'map'.
 * @param key - a key for comparision.
 * @return the 'map' after the operation.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
RoyMap * roy_map_remove(RoyMap * map, const void * key);

/**
 * @brief Removes all the elements from 'map'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_map_clear(RoyMap * map, void * user_data);

/* LOOKUP */

/**
 * @brief Finds the element with an equivalent key.
 * @param key - a key for comparision.
 * @return a pointer to the value of target element.
 */
void * roy_map_find(RoyMap * map, const void * key);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'map' in ascending order.
 * @param operate - a function for element traversing.
 * @param user_data - data to cooperate with 'operate'.
 */
void roy_map_for_each(RoyMap * map, ROperate operate, void * user_data);

/**
 * @brief Traverses elements whichever meets 'condition' in 'map'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 * @param user_data - data to cooperate with 'operate'.
 */
void roy_map_for_which(RoyMap * map, RCondition condition, ROperate operate, void * user_data);

#endif // ROYMAP_H