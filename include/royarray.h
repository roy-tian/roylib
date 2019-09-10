#ifndef ROYARRAY_H
#define ROYARRAY_H

#include "royinit.h"

struct RoyArray_ {
  void   * data;
  size_t   size;
  size_t   capacity;
  size_t   element_size;
};

// RoyArray: a container that encapsulates fixed size arrays.
typedef struct RoyArray_ RoyArray;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyArray and returns a pointer to it.
// The array can store 'capacity' elements with each size 'element_size'.
// (Operations on un-newed RoyArrays will cause undefined behavior.)
RoyArray * roy_array_new(size_t capacity, size_t element_size);

// De-allocates the memory allocated by 'roy_array_new'.
// (Always call this function after the work is done by the given 'array', or memory leak will occur.)
void roy_array_delete(RoyArray * array);

/* ELEMENT ACCESS */

// Returns a void pointer to the element at 'position'.
void * roy_array_pointer(RoyArray * array, size_t position);

// Returns a const void pointer to the element at 'position'.
const void * roy_array_const_pointer(const RoyArray * array, size_t position);

// Returns a copy of the element at 'position'.
void * roy_array_element(void * dest, const RoyArray * array, size_t position);

// Returns a typed pointer to the element at 'position', or NULL if 'position' is invalid.
#define roy_array_at(array, element_type, position) \
        ((element_type*)((position) >= 0 && (position) < ((array)->size) ? roy_array_pointer((array), (position)) : NULL))

/* CAPACITY */

// Returns the number of elements in 'array'.
size_t roy_array_size(const RoyArray * array);

// Returns the capacity of 'array'.
size_t roy_array_capacity(const RoyArray * array);

// Returns whether there is any elements in 'array'.
bool roy_array_empty(const RoyArray * array);

// Returns whether the number of elements in 'array' reaches its capacity.
bool roy_array_full(const RoyArray * array);

/* MODIFIERS */

// Adds an element named 'data' into 'array' at 'position', or does nothing if 'array' is full.
// (does nothing if 'position' is negative or exceeds.)
// (The behavior is undefined if 'data' is uninitialized.)
RoyArray * roy_array_insert(RoyArray * array, size_t position, const void * data);

// Adds an element named 'data' into 'array' at 'position', or does nothing if 'array' is full.
// (does nothing if 'position' is negative or exceeds.)
// (The behavior is undefined if 'data' is uninitialized.)
// (Recommended when element order is irrelevant.)
RoyArray * roy_array_insert_fast(RoyArray * array, size_t position, const void * data);

// Adds an element named 'data' into 'array' next to the last element, or does nothing if 'array' is full.
// (The behavior is undefined if 'data' is uninitialized.)
RoyArray * roy_array_push_back(RoyArray * array, const void * data);

// Removes an element at 'position', and fill the empty position with its next recursively.
// (Deprecated: slower when 'position' near head and length of array is huge.)
RoyArray * roy_array_erase(RoyArray * array, size_t position);

// Removes an element at 'position', and fill the empty position with the last element.
// (Recommended when element order is irrelevant.)
RoyArray * roy_array_erase_fast(RoyArray * array, size_t position);

// Removes the last element of 'array'.
RoyArray * roy_array_pop_back(RoyArray * array);

// Removes all the elements in 'array'.
RoyArray * roy_array_clear(RoyArray * array);

/* TRAVERSE */

// Traverses all elements in 'array' using 'operate' sequentially.
void roy_array_for_each(RoyArray * array, void (* operate)(void *));

// Traverses all elements whichever meets 'condition' in 'array' using 'operate'.
void roy_array_for_which(RoyArray * array, bool (* condition)(const void *), void (* operate)(void *));

#endif // ROYARRAY_H