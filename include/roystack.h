#ifndef ROYSTACK_H
#define ROYSTACK_H

#include "royarray.h"

struct RoyStack_ {
  void   ** data;
  size_t    capacity;
  size_t    size;
};

/* CONSTRUCTION AND DESTRUCTION */

// RoyStack: a container adapter that gives the functionality of a LIFO data structure.
typedef struct RoyStack_ RoyStack;


// Allocates sufficient memory for an RoyStack and returns a pointer to it.
// The stack can store 'capacity' elements with each size 'element_size' .
// (Operations on un-newed RoyStacks will cause undefined behavior.)
RoyStack * roy_stack_new(size_t capacity);

// De-allocates the memory allocated by 'roy_stack_new'.
// (Always call this function after the work is done by the given 'stack', or memory leak will occur.)
void roy_stack_delete(RoyStack * stack, ROperate deleter);

/* ELEMENT ACCESS */

// Returns a typed pointer to the first element of 'stack', or NULL if 'stack' is empty.
#define roy_stack_top(stack, element_type)  \
        ((element_type*)roy_array_pointer((RoyArray *)(stack), roy_stack_size(stack) - 1))

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

// Adds an element named 'data' into 'stack' next to the last element, returns whether the insertion is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'position' exceeds, or 'stack' is full.)
bool roy_stack_push(RoyStack * stack, void * data);

// Adds an element same as top into 'stack' next to the last element, returns whether the insertion is successful.
// (Fails if 'stack' is full.)
bool roy_stack_duplicate_top(RoyStack * stack);

// Removes the first element, returns whether the insertion is successful.
// (Fails if 'stack' is empty)
bool roy_stack_pop(RoyStack * stack);

// Removes all the elements in 'stack'.
void roy_stack_clear(RoyStack * stack);

#endif // ROYSTACK_H