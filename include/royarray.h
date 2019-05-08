#ifndef ROYARRAY_H
#define ROYARRAY_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyArray {
  void   * data;
  size_t   size;
  size_t   element_size;
  size_t   capacity;
};

// RoyArray: a container that encapsulates fixed size arrays.
typedef struct _RoyArray RoyArray;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyArray and returns a pointer to it.
// The array can store 'capacity' elements with each size 'element_size' .
// (Operations on un-newed RoyArrays will cause undefined behavior.)。
RoyArray * roy_array_new(size_t capacity, size_t element_size);

// Deallocates the memory allocated by 'roy_array_new'.
// (Always call this function after the work is done by the given 'array', or memory leak will occur.)。
void roy_array_delete(RoyArray * array);

/* ELEMENT ACCESS */

// Returns a void pointer to the element at 'position'. (No boundary check)
void * roy_array_pointer(RoyArray * array, int position);

// Returns a const void pointer to the element at 'position'. (No boundary check)
const void * roy_array_const_pointer(const RoyArray * array, int position);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_array_element(void * dest, const RoyArray * array, int position);

// Returns a typed pointer to the element at 'position'. (With boundary check)
#define roy_array_at(array, element_type, position)           \
        (position >= 0 && position < array->size)           ? \
        ((element_type*)roy_array_pointer(array, position)) : \
        NULL

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

// Adds an element named 'data' into 'array' at 'position'.
// ('data' will be pushed to the front of 'array' if 'position' is negative, or to the back if 'position' exceeds.)
// (The behavior is undefined if 'data' is uninitialized.)
RoyArray * roy_array_insert(RoyArray * array, int position, const void * data);

// Adds an element named 'data' into 'array' next to the last element.
// (The behavior is undefined if 'data' is uninitialized.)
RoyArray * roy_array_push_back(RoyArray * array, const void * data);

// Removes an element at 'position', and fill the empty position with its next recursively.
// (The first element will be removed if 'position' is negative, or the last if 'position' exceeds.)
// (Deprecated: slower when 'position' near head and lenth of array is huge.)
RoyArray * roy_array_erase(RoyArray * array, int position);

// Removes an element at 'position', and fill the empty position with the last element.
// (The first element will be removed if 'position' is negative, or the last if 'position' exceeds.)
// (Recommended when element order is irrelevant.)
RoyArray * roy_array_erase_fast(RoyArray * array, int position);

// Removes the last element of 'array'.
RoyArray * roy_array_pop_back(RoyArray * array);

// Removes all the elements in 'array'.
RoyArray * roy_array_clear(RoyArray * array);

/* TRAVERSE */

#define ROY_ITERATE_FUNC(operate) (void(*)(void *))(operate)
#define ROY_CONDITION_FUNC(condition) (bool(*)(const void *))(condition)

// Traverses all elements in 'array' using 'operate'.
void roy_array_for_each(RoyArray * array, void(* iterate)(void *));

// Traverses all elements whichever meets 'condition' in 'array' using 'operate'.
void roy_array_for_which(RoyArray * array, bool(* condition)(const void *), void(* operate)(void *));

#endif // ROYARRAY_H