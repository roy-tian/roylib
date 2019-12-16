#ifndef ROYSLIST_H
#define ROYSLIST_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "trivials/royinit.h"

struct RoySList_ {
  void             * data;
  struct RoySList_ * next;
};

/// @brief RoySList: a container implemented as a singly-linked list which supports fast insertion and removal from anywhere in the container. fast random access is not supported.
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
 * @note - Always call this function after the work is done by the given 'slist' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_slist_delete(RoySList * slist, ROperate deleter);

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
void roy_slist_push_front(RoySList * slist, void * data);

/**
 * @brief Removes the first element from 'slist',
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'slist' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_slist_pop_front(RoySList * slist, ROperate deleter);

/**
 * @brief Removes the specified element from 'slist'.
 * @param position - where the element should be removed.
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'slist' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_slist_erase(RoySList * slist, size_t position, ROperate deleter);

/**
 * @brief Removes all the elements from 'slist'.
 * @param deleter - a function for element deleting.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_slist_clear(RoySList * slist, ROperate deleter);

/* LIST OPERATIONS */

/**
 * @brief Removes all elements equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_remove(RoySList * slist, const void * data, RCompare comparer, ROperate deleter);

/**
 * @brief Removes all elements meet 'condition'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_remove_if(RoySList * slist, RCondition condition, ROperate deleter);

/// @brief Reverses the order of the elements in 'slist'.
void roy_slist_reverse(RoySList * slist);

/**
 * @brief Removes all consecutive duplicate elements from 'slist', only the first element in each group of equal elements is left.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'slist'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_slist_unique(RoySList *slist, RCompare comparer, ROperate deleter);

/**
 * @brief Sorts the elements in ascending order.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @note - This version uses shell sort strategy and may have unsatisfied performance, may be updated in future version.
 */
void roy_slist_sort(RoySList *slist, RCompare comparer);

/**
 * @brief Finds the first element equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @return The iterator to the target element.
 */
RoySList * roy_slist_find(RoySList * slist, const void * data, RCompare comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'slist' sequentially.
 * @param operate - a function for element traversing.
 */
void roy_slist_for_each(RoySList * slist, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'slist'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_slist_for_which(RoySList * slist, RCondition condition, ROperate operate);

#endif // ROYSLIST_H