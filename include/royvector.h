#ifndef ROYVECTOR_H
#define ROYVECTOR_H

#include "royarray.h"

struct RoyVector_ {
  void   * data;
  size_t   size;
  size_t   capacity;
  size_t   element_size;
  size_t   capacity_base;
};

// RoyVector: a container that encapsulates scalable size vectors.
typedef struct RoyVector_ RoyVector;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyVector and returns a pointer to it.
// The vector can store 'capacity' elements with each size 'element_size'.
// (Operations on un-newed RoyVectors will cause undefined behavior.)
RoyVector * roy_vector_new(size_t capacity, size_t element_size);

// De-allocates the memory allocated by 'roy_vector_new'.
// (Always call this function after the work is done by the given 'vector', or memory leak will occur.)
void roy_vector_delete(RoyVector * vector);

/* ELEMENT ACCESS */

// Returns a void pointer to the element at 'position'. (No boundary check)）
void * roy_vector_pointer(RoyVector * vector, size_t position);

// Returns a const void pointer to the element at 'position'. (No boundary check)
const void * roy_vector_const_pointer(const RoyVector * vector, size_t position);

// Returns a copy of the element at 'position', or NULL if 'position' is invalid.
// (The behavior is undefined if 'dest' is uninitialized.)
void * roy_vector_element(void * dest, const RoyVector * vector, size_t position);

// Returns a typed pointer to the element at 'position', or NULL if 'position' is invalid.
#define roy_vector_at(vector, element_type, position) \
        ((element_type *)((position) >= 0 && (position) < ((vector)->size) ? roy_vector_pointer((vector), (position)) : NULL))

/* CAPACITY */

// Returns the number of elements in 'vector'.
size_t roy_vector_size(const RoyVector * vector);

// Returns the capacity of 'vector' at current status.
size_t roy_vector_capacity(const RoyVector * vector);

// Returns whether there is any elements in 'vector'.
bool roy_vector_empty(const RoyVector * vector);

/* MODIFIERS */

// Adds an element named 'data' into 'vector' at 'position'.
// ('vector' will be extended automatically if it's full.)
// ('data' will not be pushed into 'vector' if 'position' exceeds.)
// (The behavior is undefined if 'data' is uninitialized.)
bool roy_vector_insert(RoyVector * vector, size_t position, const void * data);

// Moves the element at 'position' to the tail of the vector, and put 'data' there.
// (Recommended when element order is irrelevant.)
bool roy_vector_insert_fast(RoyVector * vector, size_t position, const void * data);

// Adds an element named 'data' into 'vector' next to the last element.
// ('vector' will be extended automatically if it's full.)
// (The behavior is undefined if 'data' is uninitialized.)
bool roy_vector_push_back(RoyVector * vector, const void * data);

// Removes an element at 'position', and fill the empty position with its next recursively.
// ('vector' will be shrunk to fit all elements automatically whenever it could.)
// (The first element will be removed if 'position' is negative, or the last if 'position' exceeds.)
// (Deprecated: slower when 'position' near head and length of vector is huge.)
bool roy_vector_erase(RoyVector * vector, size_t position);

// Removes an element at 'position', and fill the empty position with the last element.
// ('vector' will be shrunk to fit all elements automatically whenever it could.)
// (The first element will be removed if 'position' is negative, or the last if 'position' exceeds.)
// (Recommended when element order is irrelevant.)
bool roy_vector_erase_fast(RoyVector * vector, size_t position);

// Removes the last element.
// ('vector' will be shrunk to fit all elements whenever it could.)
bool roy_vector_pop_back(RoyVector * vector);

// Removes all the elements in 'vector'.
// (The capacity of 'vector' will be reset.)
void roy_vector_clear(RoyVector * vector);

/* TRAVERSE */

// Traverses all elements in 'vector' using 'operate'.
void roy_vector_for_each(RoyVector * vector, void (* operate)(void *));

// Traverses all elements whichever meets 'condition' in 'vector' using 'operate'.
void roy_vector_for_which(RoyVector * vector, bool (* condition)(const void *), void (* operate)(void *));

#endif // ROYVECTOR_H