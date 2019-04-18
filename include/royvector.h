#ifndef ROYVECTOR_H
#define ROYVECTOR_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyVector {
  void * data;
  size_t length;
  size_t element_size;
  size_t capacity_unit;
  size_t steps;
};

// RoyArray: a container that encapsulates scalable size arrays.
typedef struct _RoyVector RoyVector;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyVector and returns a pointer to it.
// The array can store 'capacity' elements with each size 'element_size' .
// (Operations on un-newed RoyArrays will cause undefined behavior.)
RoyVector * roy_vector_new(size_t capacity, size_t element_size);

// Deallocates the memory allocated by 'roy_vector_new'.
// (Always call this function after the work is done by the given 'array', or memory leak will occur.)
void roy_vector_delete(RoyVector * array);

/* ELEMENT ACCESS */

// Returns a void pointer to the element at 'position'. (No boundary check)
void * roy_vector_pointer(RoyVector * array, int position);

// Returns a const void pointer to the element at 'position'. (No boundary check)
const void * roy_vector_const_pointer(const RoyVector * array, int position);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_vector_element(void * dest, const RoyVector * array, int position);

// Returns a typed pointer to the element at 'position'. (No boundary check)
#define roy_vector_at(array, element_type, position)       \
        (element_type*)roy_vector_pointer(array, position)

/* CAPACITY */

// Returns the number of elements in 'array'.
size_t roy_vector_length(const RoyVector * array);

// Returns the capacity of 'array'.
size_t roy_vector_capacity(const RoyVector * array);

// Returns whether there is any elements in 'array'.
bool roy_vector_empty(const RoyVector * array);

// Returns whether the number of elements in 'array' reaches its capacity.
bool roy_vector_full(const RoyVector * array);

/* MODIFIERS */

// Adds an element named 'data' into 'array' at 'position'.
// ('data' will be pushed to the back of 'array' if 'position' exceeds.)
// (The behavior is undefined if 'data' is uninitialized.)
RoyVector * roy_vector_insert(RoyVector * array, int position, const void * data);

// Adds an element named 'data' into 'array' next to the last element.
// (The behavior is undefined if 'data' is uninitialized.)
RoyVector * roy_vector_push_back(RoyVector * array, const void * data);

// Removes an element at 'position', and fill the empty positionition with its next recursively.
// (The last element will be removed if 'position' exceeds.)
// (Deprecated: slower when 'position' near head and lenth of array is huge.)
RoyVector * roy_vector_erase(RoyVector  * array, int position);

// Removes the last element.
RoyVector * roy_vector_pop_back(RoyVector * array);

// Removes an element at 'position', and fill the empty position with the last element 
// (This function is faster than 'roy_vector_erase'.)
// (The last element will be removed if 'position' exceeds.)
RoyVector * roy_vector_erase_fast(RoyVector * array, int position);

// Removes all the elements in 'array'.
RoyVector * roy_vector_clear(RoyVector * array);

#endif // ROYVECTOR_H