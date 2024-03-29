#ifndef ROYMSET_H
#define ROYMSET_H

#include "../util/rpre.h"

struct RoyMSet_ {
  struct RoyMSet_ * left;
  struct RoyMSet_ * right;
  void            * key;
};

/**
 * @brief RoyMSet [aka Multi-Set]: an associative container that contains a sorted set of objects of type Key,
 *        duplicated objects are allowed.
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
 * @param user_data - data to cooperate with 'deleter'.
 * @note - Always call this function after the work is done by the given 'mset' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mset_delete(RoyMSet * mset, RDoer deleter, void * user_data);


/* ITERATORS */

/**
 * @return an iterator to first the minimum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
RoyMSet * roy_mset_min(RoyMSet * mset);

/**
 * @return a iterator to the last maximum element of 'set'.
 * @return NULL - 'set' is empty.
 */
RoyMSet * roy_mset_max(RoyMSet * mset);

/**
 * @return an const iterator to first the minimum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
const RoyMSet * roy_mset_cmin(const RoyMSet * mset);

/**
 * @return a const iterator to the last maximum element of 'mset'.
 * @return NULL - 'mset' is empty.
 */
const RoyMSet * roy_mset_cmax(const RoyMSet * mset);

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
RoyMSet * roy_mset_insert(RoyMSet ** restrict mset, void * restrict key, RComparer comparer);

/**
 * @brief Removes all the elements from 'mset'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_mset_clear(RoyMSet * mset, RDoer deleter, void * user_data);

/**
 * @brief Removes the element equivalents to 'key' from 'mset'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @return the 'mset' after the operation.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
RoyMSet * roy_mset_remove(RoyMSet ** mset, const void * key, RComparer comparer, RDoer deleter, void * user_data);

/* LOOKUP */

/**
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @return the number of elements equivalent to 'key'.
 */
size_t roy_mset_count(const RoyMSet * mset, const void * key, RComparer comparer);

/**
 * @brief Finds the first element equivalent to 'key'.
 * @param key - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'key'.
 * @return The iterator to the target element.
 */
RoyMSet * roy_mset_find(const RoyMSet * mset, const void * key, RComparer comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'mset' in ascending order.
 * @param doer - a function for element traversing.
 * @param user_data - data to cooperate with 'doer'.
 */
void roy_mset_for_each(RoyMSet * mset, RDoer doer, void * user_data);

/**
 * @brief Traverses elements whichever meets 'checker' in 'mset'.
 * @param checker - a function to check whether the given element meet the checker.
 * @param doer - a function for element traversing.
 * @param user_data - data to cooperate with 'doer'.
 */
void roy_mset_for_which(RoyMSet * mset, RChecker checker, RDoer doer, void * user_data);

#endif // ROYMSET_H