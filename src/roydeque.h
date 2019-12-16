#ifndef ROYDEQUE_H
#define ROYDEQUE_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "roylist.h"

struct RoyDeque_ {
  RoyList  * head;
  RoyList  * tail;
  ROperate   deleter;
  size_t     size;
};

/// @brief RoyDeque: a double ended queue powered by a RoyDeque inside, which supports fast insertion and removal from both end of the queue.
typedef struct RoyDeque_ RoyDeque;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyDeque.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyVector.
 * @note The behavior is undefined if any immature RoyVectors are operated.
 */
RoyDeque * roy_deque_new(ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyDeque - 'deque' itself.
 * @param deleter - a function for element deleting.
 * @note - Always call this function after the work is done by the given 'deque' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_deque_delete(RoyDeque * deque);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specific element.
 * @return a pointer to the element at 'position' in 'deque'.
 * @return NULL - 'position' exceeds.
 * @note - The iteration begins from the front end if 'position' is in smaller half of 'deque', and vise versa.
 */
void * roy_deque_pointer(RoyDeque * deque, size_t position);

/**
 * @brief Accesses specific element.
 * @return a const pointer to the element at 'position' in 'deque'.
 * @return NULL - 'position' exceeds or 'deque' is empty.
 * @note - The iteration begins from the front end if 'position' is in smaller half of 'deque', and vise versa.
 */
const void * roy_deque_cpointer(const RoyDeque * deque, size_t position);

/**
 * @return a pointer to the first element in 'deque'.
 * @return NULL - 'deque' is empty.
 */
void * roy_deque_front(RoyDeque * deque);

/**
 * @return a const pointer to the first element in 'deque'.
 * @return NULL - 'deque' is empty.
 */
const void * roy_deque_cfront(const RoyDeque * deque);

/**
 * @return a pointer to the last element in 'deque'.
 * @return NULL - 'deque' is empty.
 */
void * roy_deque_back(RoyDeque * deque);

/**
 * @return a const pointer to the last element in 'deque'.
 * @return NULL - 'deque' is empty.
 */
const void * roy_deque_cback(const RoyDeque * deque);

/**
 * @brief Accesses specific element.
 * @return a typed pointer to the element at 'position' in 'deque'.
 * @return NULL - 'position' exceeds or 'deque' is empty.
 * @note - The iteration begins from the front end if 'position' is in smaller half of 'deque', and vise versa.
 */
#define roy_deque_at(deque, position, element_type)  \
        ((element_type *)roy_deque_pointer((deque), (position)))

/* CAPACITY */

/// @brief Returns the number of elements in 'deque'.
size_t roy_deque_size(const RoyDeque * deque);

/**
 * @brief Checks whether 'deque' is empty.
 * @retval true - there is no element in 'vector'.
 * @retval false - otherwise.
 */
bool roy_deque_empty(const RoyDeque * deque);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'deque'.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds.
 * @note - The iteration begins from the front end if 'position' is in smaller half of 'deque', and vise versa.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_deque_insert(RoyDeque * deque, size_t position, void * data);

/**
 * @brief Adds an element at the beginning end of 'deque'.
 * @param data - a pointer to the new element.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_deque_push_front(RoyDeque * deque, void * data);

/**
 * @brief Adds an element at the back end of 'deque'.
 * @param data - a pointer to the new element.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_deque_push_back(RoyDeque * deque, void * data);

/**
 * @brief Removes specific element from 'deque'.
 * @param position - where the element should be removed.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'deque' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_deque_erase(RoyDeque * deque, size_t position);

/**
 * @brief Removes the first element from 'deque'.
 * @retval true - the removal is successful.
 * @retval false - 'deque' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_deque_pop_front(RoyDeque * deque);

/**
 * @brief Removes the last element from 'deque'.
 * @retval true - the removal is successful.
 * @retval false - 'deque' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_deque_pop_back(RoyDeque * deque);

/**
 * @brief Removes all the elements from 'deque'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_deque_clear(RoyDeque * deque);

/* LIST OPERATIONS */

/**
 * @brief Removes all elements equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'deque'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_deque_remove(RoyDeque * deque, const void * data, RCompare comparer);

/**
 * @brief Removes all elements meet 'condition'.
 * @param condition - a function to check whether the given element meet the condition.
 * @return the number of elements being removed from 'deque'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_deque_remove_if(RoyDeque * deque, RCondition condition);

/// @brief Reverses the order of the elements in 'deque'.
void roy_deque_reverse(RoyDeque * deque);

/**
 * @brief Removes all consecutive duplicate elements from 'deque', only the first element in each group of equal elements is left.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @return the number of elements being removed from 'deque'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_deque_unique(RoyDeque * deque, RCompare comparer);

/**
 * @brief Sorts the elements in ascending order.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @note - This version uses shell sort strategy and may have unsatisfied performance, may be updated in future version.
 */
void roy_deque_sort(RoyDeque * deque, RCompare comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'deque' sequentially.
 * @param operate - a function for element traversing.
 */
void roy_deque_for_each(RoyDeque * deque, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'deque'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_deque_for_which(RoyDeque * deque, RCondition condition, ROperate operate);

#endif // ROYDEQUE_H