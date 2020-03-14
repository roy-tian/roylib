#ifndef ROYQUEUE_H
#define ROYQUEUE_H

#include "royarray.h"

struct RoyQueue_ {
  void     ** data;
  ROperate    deleter;
  size_t      capacity;
  size_t      size;
  size_t      front_index;
  size_t      back_index;
};

/**
 * @brief RoyQueue: a container adapter that gives the functionality of a FIFO data structure,
 * which implemented as an cycled linear list.
 */
typedef struct RoyQueue_ RoyQueue;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyQueue and allocates sufficient memory for it.
 * @param capacity - number of elements the new queue can store.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyQueue.
 * @note The behavior is undefined if any immature RoyQueues are operated.
 */
RoyQueue * roy_queue_new(size_t capacity, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyQueue - 'queue' itself.
 * @note - Always call this function after the work is done by the given 'queue' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_queue_delete(RoyQueue * queue);

/* ELEMENT ACCESS */

/**
 * @brief Access the first element of 'queue'.
 * @return a typed pointer to the first element.
 * @return NULL - if 'queue' is empty.
 */
#define roy_queue_front(queue, element_type)  \
        ((element_type *)roy_array_pointer((RoyArray *)(queue), (queue)->front_index))

/* CAPACITY */

/// @brief Returns the number of elements in 'queue'.
size_t roy_queue_size(const RoyQueue * queue);

/// @brief Returns the maximum number of elements 'queue' can store.
size_t roy_queue_capacity(const RoyQueue * queue);

/**
 * @brief Checks whether 'queue' is empty.
 * @retval true - there is no element in 'queue'.
 * @retval false - otherwise.
 */
bool roy_queue_empty(const RoyQueue * queue);

/**
 * @brief Checks whether 'queue' is full.
 * @retval true - the number of elements in 'queue' reaches its capacity and no more element can be appended.
 * @retval false - otherwise.
 */
bool roy_queue_full(const RoyQueue * queue);

/* MODIFIERS */

/**
 * @brief Adds an element next to the last element of 'queue'.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'queue' is full or 'data' is uninitialized.
 */
bool roy_queue_push(RoyQueue * restrict queue, void * restrict data);

/**
 * @brief Removes the first element of 'queue'.
 * @retval true - the removal is successful.
 * @retval false - 'queue' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_queue_pop(RoyQueue * queue);

/**
 * @brief Removes all the elements in 'queue'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_queue_clear(RoyQueue * queue);

#endif // ROYQUEUE_H