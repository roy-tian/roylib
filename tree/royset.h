#ifndef ROYSET_H
#define ROYSET_H

#include "../trivial/royinit.h"

struct RoySet_ {
  struct RoySet_ * left;
  struct RoySet_ * right;
  void           * key;
};

/**
 * @brief RoySet: an associative container that contains a sorted set of unique objects of type key.
 * Sorting is done using the key comparison function 'comparer'.
 * Search, removal, and insertion operations have logarithmic complexity.
 */
typedef struct RoySet_ RoySet;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates a RoySet.
 * @return an empty RoySet node.
 */
RoySet * roy_set_new(void);

/**
 * @brief Releases all the elements and destroys the RoySet - 'set' itself.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - Always call this function after the work is done by the given 'set' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_set_delete(RoySet * set, ROperate deleter, void * user_data);

/* ITERATORS */

/**
 * @return an iterator to the minimum element of 'set'.
 * @return NULL - 'set' is empty.
 */
RoySet * roy_set_min(RoySet * set);

/**
 * @return a const iterator to the minimum element of 'set'.
 * @return NULL - 'set' is empty.
 */
const RoySet * roy_set_cmin(const RoySet * set);

/**
 * @return an iterator to the maximum element of 'set'.
 * @return NULL - 'set' is empty.
 */
RoySet * roy_set_max(RoySet * set);

/**
 * @return a const iterator to the maximum element of 'set'.
 * @return NULL - 'set' is empty.
 */
const RoySet * roy_set_cmax(const RoySet * set);

/* CAPACITY */

/// @brief Returns the number of elements in 'set'.
size_t roy_set_size(const RoySet * set);

/**
 * @brief Checks whether 'set' is empty.
 * @retval true - there is no element in 'set'.
 * @retval false - otherwise.
 */
bool roy_set_empty(const RoySet * set);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'set' by ascending order,
 * if 'set' doesn't already contain an element with an equivalent key.
 * @param key - a pointer to the new element.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @return the 'set' after the operation.
 * @note - The behavior is undefined if 'key' is uninitialized.
 */
RoySet * roy_set_insert(RoySet ** restrict set, void * restrict key, RCompare comparer);

/**
 * @brief Removes all the elements from 'set'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_set_clear(RoySet * set, ROperate deleter, void * user_data);

/**
 * @brief Removes the element equivalents to 'key' from 'set'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @return the 'set' after the operation.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
RoySet * roy_set_remove(RoySet ** set, const void * key, RCompare comparer, ROperate deleter, void * user_data);

/* LOOKUP */

/**
 * @brief Finds the element equivalent to 'key'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'key'.
 * @return The iterator to the target element.
 */
RoySet * roy_set_find(RoySet * set, const void * key, RCompare comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'set' in ascending order.
 * @param operate - a function for element traversing.
 * @param user_data - data to cooperate with 'deleter'.
 */
void roy_set_for_each(RoySet * set, ROperate operate, void * user_data);

/**
 * @brief Traverses elements whichever meets 'condition' in 'set'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 * @param user_data - data to cooperate with 'deleter'.
 */
void roy_set_for_which(RoySet * set, RCondition condition, ROperate operate, void * user_data);

#endif // ROYSET_H