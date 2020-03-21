#ifndef ROYVECTOR_H
#define ROYVECTOR_H

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
 * @param capacity - number of elements the new stack can store.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyVector.
 * @note The behavior is undefined if any immature RoyVectors are operated.
 */
RoyVector * roy_vector_new(size_t capacity, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyVector - 'vector' itself.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - Always call this function after the work is done by the given 'vector' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_vector_delete(RoyVector * vector, void * user_data);

/* ELEMENT ACCESS */

/**
 * @brief Accesses the specified element.
 * @return a pointer to the element at 'position' in 'vector'.
 * @return NULL - 'position' exceeds.
 */
void * roy_vector_pointer(RoyVector * vector, size_t position);

/**
 * @brief Accesses the specified element.
 * @return a const pointer to the element at 'position' in 'vector'.
 * @return NULL - 'position' exceeds.
 */
const void * roy_vector_cpointer(const RoyVector * vector, size_t position);

/**
 * @brief Accesses the specified element.
 * @return a typed pointer to the element at 'position'.
 * @return NULL - 'position' exceeds or 'vector' is empty.
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
 * @retval true - there is no element in 'vector'.
 * @retval false - otherwise.
 */
bool roy_vector_empty(const RoyVector * vector);

/* MODIFIERS */

/**
 * @brief Inserts an element into 'vector'.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds or 'data' is uninitialized.
 * @note - The storage will expand automatically whenever needed.
 * @note - The operation will move every element comes after 'position' to its next,
 *         so it can be very slow when 'vector' is huge and 'position' is small, use with caution.
 */
bool roy_vector_insert(RoyVector * restrict vector, size_t position, void * restrict data);

/**
 * @brief Inserts an element into 'vector' in a faster but unstable way.
 * @param position - where the new element should be exactly settled.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'position' exceeds or 'data' is uninitialized.
 * @note - The storage will be expanded automatically whenever needed.
 * @note - The operation moves the element at 'position' to the end of 'vector',
 *         so it may shift the sequence of elements, use this function only if element order is irrelevant.
 */
bool roy_vector_insert_fast(RoyVector * restrict vector, size_t position, void * restrict data);

/**
 * @brief Adds an element to the back of 'vector'.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - data' is uninitialized.
 * @note - The storage will be expanded automatically whenever needed.
 */
bool roy_vector_push_back(RoyVector * restrict vector, void * restrict data);

/**
 * @brief Removes an element from 'vector'.
 * @param position - where the element should be removed.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'vector' is empty.
 * @note - The storage will be shrunk to fit all elements automatically whenever it could.
 * @note - The operation will move every element comes after 'position' to its left,
 *         so it can be very slow when 'array' is huge and 'position' is small, use with caution.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_vector_erase(RoyVector * vector, size_t position);

/**
 * @brief Removes an element from 'vector' in a faster but unstable way.
 * @param position - where the element should be removed.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'vector' is empty.
 * @note - The storage will be shrunk to fit all elements automatically whenever it could.
 * @note - The operation moves the last element and settles to 'position',
 *         so it can shift the sequence of elements, use this function only if element order is irrelevant.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_vector_erase_fast(RoyVector * vector, size_t position);

/**
 * @brief Removes the last element of 'vector'.
 * @retval true - the removal is successful.
 * @retval false - 'position' exceeds or 'vector' is empty.
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
 * @param user_data - data to cooperate with 'operate'.
 * @param operate - a function for element traversing.
 */
void roy_vector_for_each(RoyVector * vector, ROperate operate, void * user_data);

/**
 * @brief Traverses elements whichever meets 'condition' in 'vector'.
 * @param user_data - data to cooperate with 'operate'.
 * @param condition - a function to check whether the given element meet the condition.
 * @param operate - a function for element traversing.
 */
void roy_vector_for_which(RoyVector * vector, RCondition condition, ROperate operate, void * user_data);

#endif // ROYVECTOR_H