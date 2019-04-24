#ifndef ROYVECTOR_H
#define ROYVECTOR_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyVector {
  void   * data;
  size_t   length;
  size_t   element_size;
  size_t   capacity_unit;
  size_t   steps;
};

// RoyArray: a container that encapsulates scalable size vectors.
typedef struct _RoyVector RoyVector;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyVector and returns a pointer to it.
// The vector can store 'capacity' elements with each size 'element_size'.
// (Operations on un-newed RoyArrays will cause undefined behavior.)
RoyVector * roy_vector_new(size_t capacity, size_t element_size);

// Deallocates the memory allocated by 'roy_vector_new'.
// (Always call this function after the work is done by the given 'vector', or memory leak will occur.)
void roy_vector_delete(RoyVector * vector);

/* ELEMENT ACCESS */

// Returns a void pointer to the element at 'position'. (No boundary check)
void * roy_vector_pointer(RoyVector * vector, int position);

// Returns a const void pointer to the element at 'position'. (No boundary check)
const void * roy_vector_const_pointer(const RoyVector * vector, int position);

// Returns a copy of the element at 'position'. (With boundary check)
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_vector_element(void * dest, const RoyVector * vector, int position);

// Returns a typed pointer to the element at 'position'. (No boundary check)
#define roy_vector_at(vector, element_type, position)       \
        (element_type*)roy_vector_pointer(vector, position)

/* CAPACITY */

// Returns the number of elements in 'vector'.
size_t roy_vector_length(const RoyVector * vector);

// Returns the capacity of 'vector'.
size_t roy_vector_capacity(const RoyVector * vector);

// Returns whether there is any elements in 'vector'.
bool roy_vector_empty(const RoyVector * vector);

// Returns whether the number of elements in 'vector' reaches its capacity.
bool roy_vector_full(const RoyVector * vector);

/* MODIFIERS */

// Adds an element named 'data' into 'vector' at 'position'.
// ('data' will be pushed to the back of 'vector' if 'position' exceeds.)
// ('vector' will be extended if its full.)
// (The behavior is undefined if 'data' is uninitialized.)
RoyVector * roy_vector_insert(RoyVector * vector, int position, const void * data);

// Adds an element named 'data' into 'vector' next to the last element.
// ('vector' will be extended if its full.)
// (The behavior is undefined if 'data' is uninitialized.)
RoyVector * roy_vector_push_back(RoyVector * vector, const void * data);

// Removes an element at 'position', and fill the empty positionition with its next recursively.
// (The last element will be removed if 'position' exceeds.)
// ('vector' will be shrunk to fit all elements whenever it could.)
// (Deprecated: slower when 'position' near head and lenth of vector is huge.)
RoyVector * roy_vector_erase(RoyVector * vector, int position);

// Removes the last element.
// ('vector' will be shrunk to fit all elements whenever it could.)
RoyVector * roy_vector_pop_back(RoyVector * vector);

// Removes an element at 'position', and fill the empty position with the last element 
// ('vector' will be shrunk to fit all elements whenever it could.)
// (This function is faster than 'roy_vector_erase'.)
// (The last element will be removed if 'position' exceeds.)
RoyVector * roy_vector_erase_fast(RoyVector * vector, int position);

// Removes all the elements in 'vector'.
// (The capacity of 'vector' will remain unchanged.)
RoyVector * roy_vector_clear(RoyVector * vector);

#endif // ROYVECTOR_H