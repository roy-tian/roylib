#ifndef ROYSTACK_H
#define ROYSTACK_H

/**
 * @author Roy Tian
 * @version 0.1.0 alpha
 * @date Dec 12, 2019
 * @copyright MIT.
 */

#include "royarray.h"

struct RoyStack_ {
  void     ** data;
  ROperate    deleter;
  size_t      capacity;
  size_t      size;
};

/// @brief RoyStack: a container adapter that gives the functionality of a LIFO data structure.
typedef struct RoyStack_ RoyStack;

/* CONSTRUCTION AND DESTRUCTION */

/**
 * @brief Creates an RoyStack and allocates sufficient memory for it.
 * @param capacity - how many elements the new stack can store.
 * @param deleter - a function to release elements.
 * @return The newly build RoyStack.
 * @note The behavior is undefined if any immature RoyStacks are operated.
 */
RoyStack * roy_stack_new(size_t capacity, ROperate deleter);

/**
 * @brief Releases all the elements and destroys the RoyStack - 'stack' itself.
 * @note - Always call this function after the work is done by the given 'stack' to get rid of memory leaking.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_stack_delete(RoyStack * stack);

/* ELEMENT ACCESS */

/**
 * @brief Returns a typed pointer to the first element of 'stack'.
 * @note Returns NULL if 'stack' is empty.
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
 * @return whether there are element(s) in 'stack'.
 */
bool roy_stack_empty(const RoyStack * stack);

/**
 * @brief Checks whether 'stack' is full.
 * @return Whether the number of elements in 'stack' reaches its capacity and no more element can be appended.
 */
bool roy_stack_full(const RoyStack * stack);

/* MODIFIERS */

/**
 * @brief Adds an element right before the first element of 'stack'.
 * @param data - the pointer to the new element.
 * @return Whether the insertion is successful (fails only when 'stack' is full).
 * @note The behavior is undefined if 'data' is uninitialized.
 */
bool roy_stack_push(RoyStack * stack, void * data);

/**
 * @brief Removes the first element of 'stack'.
 * @return Whether the removal is successful (fails only when 'stack' is empty).
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
bool roy_stack_pop(RoyStack * stack);

/**
 * @brief Removes all the elements in 'stack'.
 * @note - The behavior is undefined if 'deleter' deletes elements in a wrong manner.
 */
void roy_stack_clear(RoyStack * stack);

#endif // ROYSTACK_H