#ifndef ROYSTACK_H
#define ROYSTACK_H

#include "../util/rpre.h"

/// @brief RoyStack: a container adapter that gives the functionality of a LIFO data structure.
typedef struct RoyStack_ RoyStack;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyStack and allocates sufficient memory for it.
 * @param capacity - number of elements the new stack can store.
 * @param deleter - a function for element deleting.
 * @return The newly build RoyStack.
 * @note The behavior is undefined if any immature RoyStacks are operated.
 */
RoyStack * roy_stack_new(size_t capacity, RDoer deleter);

/**
 * @brief Releases all the elements and destroys the RoyStack - 'stack' itself.
 * @param user_data - data to cooperate with 'deleter'.
 * @note - Always call this function after the work is done by the given 'stack' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_stack_delete(RoyStack * stack, void * user_data);

/* ELEMENT ACCESS */

/**
 * @brief Accesses the last element.
 * @return a typed pointer to the last element.
 * @return NULL - 'stack' is empty.
 */
#define roy_stack_top(stack, element_type)  \
        ((element_type*)roy_array_pointer((RoyArray *)(stack), roy_stack_size(stack) - 1))

/* CAPACITY */

/// @brief Returns the number of elements in 'stack'.
size_t roy_stack_size(const RoyStack * stack);

/// @brief Returns the maximum number of elements 'stack' can store.
size_t roy_stack_capacity(const RoyStack * stack);

/**
 * @brief Checks whether 'stack' is empty.
 * @retval true - there is no element in 'stack'.
 * @retval false - otherwise.
 */
bool roy_stack_empty(const RoyStack * stack);

/**
 * @brief Checks whether 'stack' is full.
 * @retval true - the number of elements in 'stack' reaches its capacity and no more element can be appended.
 * @retval false - otherwise.
 */
bool roy_stack_full(const RoyStack * stack);

/* MODIFIERS */

/**
 * @brief Adds an element right before the first element of 'stack'.
 * @param data - a pointer to the new element.
 * @retval true - the insertion is successful.
 * @retval false - 'stack' is full or 'data' is uninitialized.
 */
bool roy_stack_push(RoyStack * restrict stack, void * restrict data);

/**
 * @brief Removes the first element of 'stack'.
 * @retval true - the removal is successful.
 * @retval false - 'stack' is empty.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_stack_pop(RoyStack * stack);

/**
 * @brief Removes all the elements in 'stack'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_stack_clear(RoyStack * stack);

#endif // ROYSTACK_H