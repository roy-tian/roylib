#ifndef ROYSTACK_H
#define ROYSTACK_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyStack {
  void   * data;
  size_t   size;
  size_t   element_size;
  size_t   capacity;
};

/* CONSTRUCTION AND DESTRUCTION */

// RoyStack: a container adapter that gives the functionality of a LIFO data structure.
typedef struct _RoyStack RoyStack;

// Allocates sufficient memory for an RoyStack and returns a pointer to it.
// The stack can store 'capacity' elements with each size 'element_size' .
// (Operations on un-newed RoyStacks will cause undefined behavior.)
RoyStack * roy_stack_new(size_t capacity, size_t element_size);

// Deallocates the memory allocated by 'roy_stack_new'.
// (Always call this function after the work is done by the given 'stack', or memory leak will occur.)
void roy_stack_delete(RoyStack * stack);

/* ELEMENT ACCESS */

#define roy_stack_top(stack, element_type) \
        (element_type *)(stack->data + stack->element_size * (stack->size - 1))

/* CAPACITY */

// Returns the number of elements in 'stack'.
size_t roy_stack_size(const RoyStack * stack);

// Returns the capacity of 'stack'.
size_t roy_stack_capacity(const RoyStack * stack);

// Returns whether there is any elements in 'stack'.
bool roy_stack_empty(const RoyStack * stack);

// Returns whether the number of elements in 'stack' reaches its capacity.
bool roy_stack_full(const RoyStack * stack);

/* MODIFIERS */

// Adds an element named 'data' into 'stack' next to the last element.
// (The behavior is undefined if 'data' is uninitialized.)
RoyStack * roy_stack_push(RoyStack * stack, const void * data);

// Adds an element same as top into 'stack' next to the last element.
// (The behavior is undefined if 'data' is uninitialized.)
RoyStack * roy_stack_duplicate_top(RoyStack * stack);

// Swaps the top two elements of 'stack'.
RoyStack * roy_stack_swap_top_two(RoyStack * stack);

// Removes the last element.
RoyStack * roy_stack_pop(RoyStack * stack);

// Removes all the elements in 'array'.
RoyStack * roy_stack_clear(RoyStack * stack);

#endif // ROYSTACK_H