#ifndef ROYSLIST_H
#define ROYSLIST_H

#include "../util/rpre.h"

/**
 * @brief RoySList: a container implemented as a singly-linked list which supports fast insertion and removal
 *        from anywhere in the container. fast random access is not supported.
 */
typedef struct RoySList_ RoySList;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoySList for navigating.
 * @return an empty RoySList node.
 * @note - The real data takes places from the 2nd element.
 */
RoySList * roy_slist_new(void);

/**
 * @brief Releases all the elements and destroys the RoySList - 'slist' itself.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - Always call this function after the work is done by the given 'slist' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_slist_delete(RoySList * slist, RDoer deleter, void * user_data);

/* ITERATORS */

/**
 * @param position - where the element takes place.
 * @return an iterator to the 'position'-th element in 'slist'.
 * @return NULL - 'position' exceeds.
 */
RoySList * roy_slist_iterator(RoySList * slist, size_t position);

/**
 * @param position - where the element takes place.
 * @return a const iterator to the 'position'-th element in 'slist'.
 * @return NULL - 'position' exceeds.
 */
const RoySList * roy_slist_citerator(const RoySList * slist, size_t position);

/**
 * @return an iterator to the first element in 'slist'.
 * @return NULL - 'slist' is empty.
 */
RoySList * roy_slist_begin(RoySList * slist);

/**
 * @return a const iterator to the first element in 'slist'.
 * @return NULL - 'slist' is empty.
 */
const RoySList * roy_slist_cbegin(const RoySList * slist);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified element.
 * @return a typed pointer to the element at 'position'.
 * @return NULL - 'position' exceeds or 'slist' is empty.
 */
#define roy_slist_at(slist, position, element_type)    \
        ((element_type *)roy_slist_iterator((list_head), (position))->data)

/* CAPACITY */

/// @brief Returns the number of elements in 'slist'.
size_t roy_slist_size(const RoySList * slist);

/**
 * @brief Checks whether 'slist' is empty.
 * @retval true - there is no element in 'slist'.
 * @retval false - otherwise.
 */
bool roy_slist_empty(const RoySList * slist);

/* MODIFIERS */

/**
 * @brief Adds an element at the beginning of 'slist'.
 * @param data - a pointer to the new element.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_slist_push_front(RoySList * restrict slist, void * restrict data);

/**
 * @brief Removes the first element from 'slist',
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @retval true - the removal is successful.
 * @retval false - 'slist' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_slist_pop_front(RoySList * slist, RDoer deleter, void * user_data);

/**
 * @brief Removes the specified element from 'slist'.
 * @param position - where the element should be removed.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'slist' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_slist_erase(RoySList * slist, size_t position, RDoer deleter, void * user_data);

/**
 * @brief Removes all the elements from 'slist'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_slist_clear(RoySList * slist, RDoer deleter, void * user_data);

/* LIST OPERATIONS */

/**
 * @brief Removes all elements equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_remove(RoySList * slist, const void * data, RComparer comparer, RDoer deleter, void * user_data);

/**
 * @brief Removes all elements meet 'checker'.
 * @param checker - a function to check whether the given element meet the checker.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_remove_if(RoySList * slist, RChecker checker, RDoer deleter, void * user_data);

/// @brief Reverses the order of the elements in 'slist'.
void roy_slist_reverse(RoySList * slist);

/**
 * @brief Removes all consecutive duplicate elements from 'slist',
 *        only the first element in each group of equal elements is left.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @param user_data - data to cooperate with 'deleter'.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_unique(RoySList *slist, RComparer comparer, RDoer deleter, void * user_data);

/**
 * @brief Sorts the elements in ascending order.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @note - This version uses heap sort strategy powered by RoyMSet.
 */
void roy_slist_sort(RoySList *slist, RComparer comparer);

/**
 * @brief Finds the first element equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @return The iterator to the target element.
 */
RoySList * roy_slist_find(RoySList * slist, const void * data, RComparer comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'slist' sequentially.
 * @param user_data - data to cooperate with 'doer'.
 * @param doer - a function for element traversing.
 */
void roy_slist_for_each(RoySList * slist, RDoer doer, void * user_data);

/**
 * @brief Traverses elements whichever meets 'checker' in 'slist'.
 * @param checker - a function to check whether the given element meet the checker.
 * @param doer - a function for element traversing.
 * @param user_data - data to cooperate with 'doer'.
 */
void roy_slist_for_which(RoySList * slist, RChecker checker, RDoer doer, void * user_data);

#endif // ROYSLIST_H