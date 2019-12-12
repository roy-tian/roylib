#ifndef ROYARRAY_H
#define ROYARRAY_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "trivials/royinit.h"

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
 * @param capacity - how many elements the new array can store.
 * @param deleter - a function to release elements.
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
 * @brief Returns a pointer to the element at 'position' in 'array'.
 * @note Returns NULL if 'position' exceeds.
 */
void * roy_array_pointer(RoyArray * array, size_t position);

/**
 * @brief Returns a const pointer to the element at 'position' in 'array'.
 * @note Returns NULL if 'position' exceeds.
 */
const void * roy_array_cpointer(const RoyArray * array, size_t position);

/**
 * @brief Returns a typed pointer to the element at 'position'.
 * @note Returns NULL if 'position' exceeds or 'array' is empty.
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
 * @return whether there are element(s) in 'array'.
 */
bool roy_array_empty(const RoyArray * array);

/**
 * @brief Checks whether 'array' is full.
 * @return whether the number of elements in 'array' reaches its capacity and no more element can be appended.
 */
bool roy_array_full(const RoyArray * array);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'array'.
 * @param position - the position where the new element should be exactly settled.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'position' exceeds or 'array' is full).
 * @note - The operation will move every element comes after 'position' to its next, so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_array_insert(RoyArray * array, size_t position, void * data);

/**
 * @brief Inserts an element into 'array' in a faster but unstable way.
 * @param position - the position where the new element should be exactly settled.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'position' exceeds or 'array' is full).
 * @note - The operation moves the element at 'position' to the end of 'array', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_array_insert_fast(RoyArray * array, size_t position, void * data);

/**
 * @brief Adds an element to the back of 'array'.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'array' is full).
 * @note The behavior is undefined if 'data' is uninitialized.
 */
bool roy_array_push_back(RoyArray * array, void * data);

/**
 * @brief Removes an element from 'array'.
 * @param position - the position where the element should be removed.
 * @return Whether the removal is successful (fails only when 'position' exceeds or 'array' is empty).
 * @note - The operation will move every element comes after 'position' to its left, so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_array_erase(RoyArray * array, size_t position);

/**
 * @brief Removes an element from 'array' in a faster but unstable way.
 * @param position - the position where the element should be removed.
 * @return Whether the removal is successful (fails only when 'position' exceeds or 'array' is empty).
 * @note - The operation moves the last element and settles to 'position', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_array_erase_fast(RoyArray * array, size_t position);

/**
 * @brief Removes the last element of 'array'.
 * @return Whether the removal is successful (fails only when 'array' is empty).
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
 * @param operate - a functions pointer to the traverser.
 */
void roy_array_for_each(RoyArray * array, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'array'.
 * @param condition - a pointer to the check function, if condition meets, the element gets traversed; or the element is ignored.
 * @param operate - a function pointer to the traverser.
 */
void roy_array_for_which(RoyArray * array, RCondition condition, ROperate operate);

#endif // ROYARRAY_H