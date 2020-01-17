#ifndef ROYLIST_H
#define ROYLIST_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "../trivial/royinit.h"

struct RoyList_ {
  void            * data;
  struct RoyList_ * next;
  struct RoyList_ * prev;
};

/// @brief RoyList: a container implemented as a double-linked list which supports fast insertion and removal from anywhere in the container, fast random access is not supported.
typedef struct RoyList_ RoyList;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates a RoyList for navigating.
 * @return an empty RoyList node.
 * @note the real data takes places from the 2nd element.
 */
RoyList * roy_list_new(void);

/**
 * @brief Releases all the elements and destroys the RoyList - 'list' itself.
 * @param deleter - a function for element deleting.
 * @note - Always call this function after the work is done by the given 'list' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_list_delete(RoyList * list, ROperate deleter);

/* ITERATORS */

/**
 * @param list_head - the iterator to the head of 'list'.
 * @param position - where the element takes place.
 * @return an iterator to the 'position'-th element in 'list'.
 * @return NULL - 'position' exceeds.
 */
RoyList * roy_list_iterator(RoyList * list_head, size_t position);

/**
 * @param list_head - the iterator to the head of 'list'.
 * @param position - where the element takes place.
 * @return a const iterator to 'position'-th element in 'list'.
 * @return NULL - 'position' exceeds.
 */
const RoyList * roy_list_citerator(const RoyList * list_head, size_t position);

/**
 * @param list_tail - the iterator to the tail of 'list'.
 * @param rposition - the reversed position where the element takes place.
 * @return a reversed iterator to the 'rposition'-th element in 'list'.
 * @return NULL - 'rposition' exceeds.
 */
RoyList * roy_list_riterator(RoyList * list_tail, size_t rposition);

/**
 * @param list_tail - the iterator to the tail of 'list'.
 * @param rposition - the reversed position where the element takes place.
 * @return a const reversed iterator to the 'rposition'-th element in 'list'.
 * @return NULL - 'rposition' exceeds.
 */
const RoyList * roy_list_criterator(const RoyList * list_tail, size_t rposition);

/**
 * @param list_head - the iterator to the head of 'list'.
 * @return an iterator to the first element in 'list'.
 * @return NULL - 'list' is empty.
 */
RoyList * roy_list_begin(RoyList * list_head);

/**
 * @param list_head - the iterator to the head of 'list'.
 * @return a const iterator to the first element.
 * @return NULL - 'list' is empty.
 */
const RoyList * roy_list_cbegin(const RoyList *list_head);

/**
 * @param list_tail - the iterator to the tail of 'list'.
 * @return a reversed iterator to the last element in 'list'.
 * @return NULL - 'list' is empty.
 */
RoyList * roy_list_rbegin(RoyList * list_tail);

/**
 * @param list_tail - the iterator to the tail of 'list'.
 * @return a const reversed iterator to the last element in 'list'.
 * @return NULL - 'list' is empty.
 */
const RoyList * roy_list_crbegin(const RoyList *list_tail);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified element.
 * @param list_head - the iterator to the head of 'list'.
 * @param position - where the element takes place.
 * @return a typed pointer to the element at 'position'.
 * @return NULL - 'position' exceeds.
 */
#define roy_list_at(list_head, position, element_type) \
        ((element_type *)roy_list_iterator((list_head), (position))->data)

/* CAPACITY */

/**
 * @brief Counts the number of elements in an ascending order.
 * @param list_head - the iterator to the head of 'list'.
 * @return the number of element in 'list'.
 */
size_t roy_list_size(const RoyList * list_head);

/**
 * @brief Counts the number of elements in an descending order.
 * @param list_tail - the iterator to the tail of 'list'.
 * @return the number of element in 'list'.
 */
size_t roy_list_rsize(const RoyList * list_tail);

/**
 * @brief Checks whether 'list' is empty.
 * @param list_head - the iterator to the head of 'list'.
 * @retval true - there is no element in 'list'.
 * @retval false - otherwise.
 */
bool roy_list_empty(const RoyList * list_head);

/**
 * @brief Checks whether 'list' is empty.
 * @param list_tail - the iterator to the tail of 'list'.
 * @retval true - there is no element in 'list'.
 * @retval false - otherwise.
 */
bool roy_list_rempty(const RoyList * list_tail);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'list'.
 * @param list_head - the iterator to the head of 'list'.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_list_insert(RoyList * list_head, size_t position, void * data);

/**
 * @brief Inserts an element into 'list'.
 * @param list_tail - the iterator to the tail of 'list'.
 * @param rposition - the reversed position where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_list_insert_reverse(RoyList * list_tail, size_t rposition, void * data);

/**
 * @brief Adds an element at the beginning of 'list'.
 * @param list_head - the iterator to the head of 'list'.
 * @param data - a pointer to the new element.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_list_push_front(RoyList * list_head, void * data);

/**
 * @brief Adds an element at the end of 'list'.
 * @param list_tail - the iterator to the tail of 'list'.
 * @param data - a pointer to the new element.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_list_push_back(RoyList * list_tail, void * data);

/**
 * @brief Removes specified element from 'list'.
 * @param list_head - the iterator to the head of 'list'.
 * @param position - where the element should be removed.
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'list' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_list_erase(RoyList * list_head, size_t position, ROperate deleter);

/**
 * @brief Removes specified element from 'list'.
 * @param list_tail - the iterator to the tail of 'list'.
 * @param rposition - the reversed position where the element should be removed.
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'list' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_list_erase_reverse(RoyList * list_tail, size_t rposition, ROperate deleter);

/**
 * @brief Removes the first element from 'list'.
 * @param list_head - the iterator to the head of 'list'.
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'list' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_list_pop_front(RoyList * list_head, ROperate deleter);

/**
 * @brief Removes the last element from 'list'.
 * @param list_tail - the iterator to the tail of 'list'.
 * @param deleter - a function for element deleting.
 * @retval true - the removal is successful.
 * @retval false - 'list' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_list_pop_back(RoyList * list_tail, ROperate deleter);

/**
 * @brief Removes all the elements from 'list'.
 * @param deleter - a function for element deleting.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_list_clear(RoyList * list_head, ROperate deleter);

/* LIST OPERATIONS */

/**
 * @brief Removes all elements equivalent to 'data'.
 * @param data - a pointer to the comparable element.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'list'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_list_remove(RoyList * list, const void * data, RCompare comparer, ROperate deleter);

/**
 * @brief Removes all elements meet 'condition'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'list'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_list_remove_if(RoyList * list, RCondition condition, ROperate deleter);

/// @brief Reverses the order of the elements in 'list'.
void roy_list_reverse(RoyList ** list);

/**
 * @brief Removes all consecutive duplicate elements from 'list', only the first element in each group of equal elements is left.
 * @param comparer - a function to compare two elements, returns 0 if current element is equal to the given 'data'.
 * @param deleter - a function for element deleting.
 * @return the number of elements being removed from 'list'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
size_t roy_list_unique(RoyList * list, RCompare comparer, ROperate deleter);

/**
 * @brief Sorts the elements in ascending order.
 * @param comparer - a function to compare two elements, acting like <=> operator in C++.
 * @note - This version uses shell sort strategy and may have unsatisfied performance, may be updated in future version.
 */
void roy_list_sort(RoyList * list, RCompare comparer);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'list' sequentially.
 * @param operate - a function for element traversing.
 */
void roy_list_for_each(RoyList * list, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'list'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_list_for_which(RoyList * list, RCondition condition, ROperate operate);

#endif // ROYLIST_H