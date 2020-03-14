#ifndef ROYARRAY_H
#define ROYARRAY_H

#include "../trivial/royinit.h"

struct RoyArray_ {
  void     ** data;
  ROperate    deleter;
  size_t      capacity;
  size_t      size;
};

/// @brief RoyArray: a container that encapsulates fixed size arrays.
typedef struct RoyArray_ RoyArray;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyArray and allocates sufficient memory for it.
 * @param capacity - number of elements the new array can store.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyArray.
 * @note The behavior is undefined if any immature RoyArrays are operated.
 */
RoyArray * roy_array_new(size_t capacity, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyArray - 'array' itself.
 * @note - Always call this function after the work is done by the given 'array' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_array_delete(RoyArray * array);

/* ELEMENT ACCESS */

/**
 * @brief Accesses specified element.
 * @param position - where the element takes place.
 * @return a pointer to the specified element in 'array'.
 * @return NULL - 'position' exceeds.
 */
void * roy_array_pointer(RoyArray * array, size_t position);

/**
 * @brief Accesses specified element.
 * @param position - where the element takes place.
 * @return a const pointer to the element at 'position' in 'array'.
 * @return NULL - 'position' exceeds.
 */
const void * roy_array_cpointer(const RoyArray * array, size_t position);

/**
 * @brief Accesses specified element.
 * @return a typed pointer to the element at 'position'.
 * @return NULL - if 'position' exceeds or 'array' is empty.
 */
#define roy_array_at(array, position, element_type) \
        ((element_type*)roy_array_pointer((array), (position)))

/* CAPACITY */

/// @brief Returns the number of elements in 'array'.
size_t roy_array_size(const RoyArray * array);

/// @brief Returns the maximum number of elements 'array' can store.
size_t roy_array_capacity(const RoyArray * array);

/**
 * @brief Checks whether 'array' is empty.
 * @retval true - there is no element in 'array'.
 * @retval false - otherwise.
 */
bool roy_array_empty(const RoyArray * array);

/**
 * @brief Checks whether 'array' is full.
 * @retval true - the number of elements in 'array' reaches its capacity and no more element can be appended.
 * @retval false - otherwise.
 */
bool roy_array_full(const RoyArray * array);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'array'.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds, 'array' is full or 'data' is uninitialized.
 * @note - The operation will move every element comes after 'position' to its next, so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 */
bool roy_array_insert(RoyArray * restrict array, size_t position, void * restrict data);

/**
 * @brief Inserts an element into 'array' in a faster but unstable way.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds, 'array' is full or 'data' is uninitialized.
 * @note - The operation moves the element at 'position' to the end of 'array', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 */
bool roy_array_insert_fast(RoyArray * restrict array, size_t position, void * restrict data);

/**
 * @brief Adds an element to the back of 'array'.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds, 'array' is full or 'data' is uninitialized.
 */
bool roy_array_push_back(RoyArray * restrict array, void * restrict data);

/**
 * @brief Removes an element from 'array'.
 * @param position - where the element should be removed.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'array' is empty.
 * @note - The operation will move every element comes after 'position' to its left recursively, so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_array_erase(RoyArray * array, size_t position);

/**
 * @brief Removes an element from 'array' in a faster but unstable way.
 * @param position - where the element should be removed.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'array' is empty.
 * @note - The operation moves the last element and settles to 'position', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_array_erase_fast(RoyArray * array, size_t position);

/**
 * @brief Removes the last element of 'array'.
 * @retval true - the removal is successful.
 * @retval false - 'array' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_array_pop_back(RoyArray * array);

/**
 * @brief Removes all the elements in 'array'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_array_clear(RoyArray * array);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'array' sequentially.
 * @param operate - a function for element traversing.
 */
void roy_array_for_each(RoyArray * array, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'array'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_array_for_which(RoyArray * array, RCondition condition, ROperate operate);

#endif // ROYARRAY_H