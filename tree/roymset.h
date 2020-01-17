#ifndef ROYMSET_H
#define ROYMSET_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "../trivials/royinit.h"

struct RoyMSet_ {
  struct RoyMSet_ * left;
  struct RoyMSet_ * right;
  void            * key;
};

/**
 * @brief RoyMSet [aka Multi-Set]: an associative container that contains a sorted set of objects of type Key, duplicated objectss are allowed.
 * Sorting is done using the key comparison function 'comparer'.
 * Search, removal, and insertion operations have logarithmic complexity.
 */
typedef struct RoyMSet_ RoyMSet;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates a RoyMSet.
 * @return an empty RoyMSet node.
 */
RoyMSet * roy_mset_new(void);

/**
 * @brief Releases all the elements and destroys the RoyMSet - 'mset' itself.
 * @param deleter - a function for element deleting.
 * @note - Always call this function after the work is done by the given 'mset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mset_delete(RoyMSet * mset, ROperate deleter);


/* ITERATORS */

/**
 * @return an iterator to first the minimum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
RoyMSet * roy_mset_min(RoyMSet *mset);

/**
 * @return a iterator to the last maximum element of 'set'.
 * @return NULL - 'set' is empty.
 */
RoyMSet * roy_mset_max(RoyMSet *mset);

/**
 * @return an const iterator to first the minimum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
const RoyMSet * roy_mset_cmin(const RoyMSet *mset);

/**
 * @return a const iterator to the last maximum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
const RoyMSet * roy_mset_cmax(const RoyMSet *mset);

/* CAPACITY */

/// @brief Returns the number of elements in 'mset'.
size_t roy_mset_size(const RoyMSet * mset);

/**
 * @brief Checks whether 'mset' is empty.
 * @retval true - there is no element in 'mset'.
 * @retval false - otherwise.
 */
bool roy_mset_empty(const RoyMSet * mset);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'mset' by ascending order, duplicated elements are allowed.
 * @param key - a pointer to the new element.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @return the 'mset' after the operation.
 * @note - The behavior is undefined if 'key' is uninitialized.
 */
RoyMSet * roy_mset_insert(RoyMSet ** mset, void * key, RCompare comparer);

/**
 * @brief Removes all the elements from 'mset'.
 * @param deleter - a function for element deleting.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mset_clear(RoyMSet * mset, ROperate deleter);

/**
 * @brief Removes the element equivalents to 'key' from 'mset'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the 'mset' after the operation.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
RoyMSet * roy_mset_remove(RoyMSet ** mset, const void * key, RCompare comparer, ROperate deleter);

/* LOOKUP */

/**
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @return the number of elements equivalent to 'key'.
 */
size_t roy_mset_count(const RoyMSet * mset, const void * key, RCompare comparer);

/**
 * @brief Finds the first element equivalent to 'key'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'key'.
 * @return The iterator to the target element.
 */
RoyMSet * roy_mset_find(const RoyMSet * mset, const void * key, RCompare comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'mset' in ascending order.
 * @param operate - a function for element traversing.
 */
void roy_mset_for_each(RoyMSet * mset, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'mset'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_mset_for_which(RoyMSet * mset, RCondition condition, ROperate operate);

#endif // ROYMSET_H