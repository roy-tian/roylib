#ifndef ROYVECTOR_H
#define ROYVECTOR_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "royarray.h"

struct RoyVector_ {
  void     ** data;
  ROperate    deleter;
  size_t      capacity;
  size_t      size;
  size_t      capacity_base;
};

/// @brief RoyVector: a container that encapsulates scalable size vectors.
typedef struct RoyVector_ RoyVector;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyVector and allocates sufficient memory for it.
 * @param capacity - how many elements the new stack can store.
 * @param deleter - a function to release elements.
 * @return The newly build RoyVector.
 * @note The behavior is undefined if any immature RoyVectors are operated.
 */
RoyVector * roy_vector_new(size_t capacity, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyVector - 'vector' itself.
 * @note - Always call this function after the work is done by the given 'vector' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_vector_delete(RoyVector * vector);

/* ELEMENT ACCESS */

/**
 * @brief Accesses the specific element.
 * @return a pointer to the element at 'position' in 'vector'.
 * @return NULL - 'position' exceeds.
 */
void * roy_vector_pointer(RoyVector * vector, size_t position);

/**
 * @brief Accesses the specific element.
 * @return a const pointer to the element at 'position' in 'vector'.
 * @return NULL - 'position' exceeds.
 */
const void * roy_vector_cpointer(const RoyVector * vector, size_t position);

/**
 * @brief Returns a typed pointer to the element at 'position'.
 * @note Returns NULL if 'position' exceeds or 'vector' is empty.
 */
#define roy_vector_at(vector, position, element_type) \
        ((element_type *)roy_vector_pointer((vector), (position)))

/* CAPACITY */

/// @brief Returns the number of elements in 'vector'.
size_t roy_vector_size(const RoyVector * vector);

/// @brief Returns the maximum number of elements 'vector' can store.
size_t roy_vector_capacity(const RoyVector * vector);

/**
 * @brief Checks whether 'vector' is empty.
 * @return whether there is no element in 'vector'.
 */
bool roy_vector_empty(const RoyVector * vector);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'vector'.
 * @param position - the position where the new element should be exactly settled.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'position' exceeds).
 * @note - The storage will expand automatically whenever needed.
 * @note - The operation will move every element comes after 'position' to its next, so it can be very slow when 'vector' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_vector_insert(RoyVector * vector, size_t position, void * data);

/**
 * @brief Inserts an element into 'vector' in a faster but unstable way.
 * @param position - the position where the new element should be exactly settled.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'position' exceeds).
 * @note - The storage will be expanded automatically whenever needed.
 * @note - The operation moves the element at 'position' to the end of 'vector', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
bool roy_vector_insert_fast(RoyVector * vector, size_t position, void * data);

/**
 * @brief Adds an element to the back of 'vector'.
 * @param data - the pointer to the new element.
 * @note - The storage will be expanded automatically whenever needed.
 * @note - The behavior is undefined if 'data' is uninitialized.
 */
void roy_vector_push_back(RoyVector * vector, void * data);

// Removes an element at 'position', and fill the empty position with its next recursively, return whether the operation is successful.
// (Fails if 'position' exceeds, or 'vector' is empty.)
// ('vector' will be shrunk to fit all elements automatically whenever it could.)
// (Deprecated when 'vector' is huge and 'position' is small, can be very slow.)
/**
 * @brief Removes an element from 'vector'.
 * @param position - the position where the element should be removed.
 * @return Whether the removal is successful (fails only when 'position' exceeds or 'vector' is empty).
 * @note - The storage will be shrunk to fit all elements automatically whenever it could.
 * @note - The operation will move every element comes after 'position' to its left, so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_vector_erase(RoyVector * vector, size_t position);

/**
 * @brief Removes an element from 'vector' in a faster but unstable way.
 * @param position - the position where the element should be removed.
 * @return Whether the removal is successful (fails only when 'position' exceeds or 'vector' is empty).
 * @note - The storage will be shrunk to fit all elements automatically whenever it could.
 * @note - The operation moves the last element and settles to 'position', so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_vector_erase_fast(RoyVector * vector, size_t position);

/**
 * @brief Removes the last element of 'vector'.
 * @return Whether the removal is successful (fails only when 'vector' is empty).
 * @note - The storage will be shrunk to fit all elements automatically whenever it could.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_vector_pop_back(RoyVector * vector);

/**
 * @brief Removes all the elements in 'vector'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_vector_clear(RoyVector * vector);

/* TRAVERSE */

/**
 * @brief Traverses all elements in 'vector' sequentially.
 * @param operate - the traverse function.
 */
void roy_vector_for_each(RoyVector * vector, ROperate operate);

/**
 * @brief Traverses elements whichever meets 'condition' in 'vector'.
 * @param condition - the check function, the element gets traversed if condition meets, otherwise the element is ignored.
 * @param operate - the traverse function.
 */
void roy_vector_for_which(RoyVector * vector, RCondition condition, ROperate operate);

#endif // ROYVECTOR_H