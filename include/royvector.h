#ifndef ROYVECTOR_H
#define ROYVECTOR_H

#include "royarray.h"

struct RoyVector_ {
  void   ** data;
  size_t    capacity;
  size_t    size;
  size_t    capacity_base;
};

// RoyVector: a container that encapsulates scalable size vectors.
typedef struct RoyVector_ RoyVector;

/* CONSTRUCTION AND DESTRUCTION */

// Allocates sufficient memory for an RoyVector and returns a pointer to it.
// The vector can store 'capacity' elements with each size 'element_size'.
// (Operations on un-newed RoyVectors can cause undefined behavior.)
RoyVector * roy_vector_new(size_t capacity);

// De-allocates the memory allocated by 'roy_vector_new'.
// (Always call this function after the work is done by the given 'vector', or memory leak will occur.)
void roy_vector_delete(RoyVector * vector, ROperate deleter);

/* ELEMENT ACCESS */

// Returns a pointer to the element at 'position', or NULL if position exceeds.
void * roy_vector_pointer(RoyVector * vector, size_t position);

// Returns a const pointer to the element at 'position', or NULL if position exceeds.
const void * roy_vector_cpointer(const RoyVector * vector, size_t position);

// Returns a typed pointer to the element at 'position', or NULL if 'position' exceeds or 'vector' is empty.
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

// Inserts an element named 'data' into 'vector' at 'position', returns whether the insertion is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'position' exceeds.)
// (Deprecated when 'vector' is huge and 'position' is small, can be very slow.)
bool roy_vector_insert(RoyVector * vector, size_t position, void * data);

// Moves the element at 'position' to the back of 'vector', puts 'data' there, returns whether the operation is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'position' exceeds.)
// (Recommended when element order is irrelevant.)
bool roy_vector_insert_fast(RoyVector * vector, size_t position, void * data);

// Adds an element named 'data' to the back of 'array', returns whether the operation is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// ('vector' will be extended automatically whenever it's full.)
bool roy_vector_push_back(RoyVector * vector, void * data);

// Removes an element at 'position', and fill the empty position with its next recursively, return whether the operation is successful.
// (Fails if 'position' exceeds, or 'vector' is empty.)
// ('vector' will be shrunk to fit all elements automatically whenever it could.)
// (Deprecated when 'vector' is huge and 'position' is small, can be very slow.)
bool roy_vector_erase(RoyVector * vector, size_t position);

// Removes an element at 'position', and fill the empty position with the last element, returns whether the operation is successful.
// (Fails if 'position' exceeds, or 'vector' is empty.)
// ('vector' will be shrunk to fit all elements automatically whenever it could.)
// (Recommended when element order is irrelevant.)
bool roy_vector_erase_fast(RoyVector * vector, size_t position);

// Removes the last element, returns whether the operation is successful.
// (Fails if 'vector' is empty.)
// ('vector' will be shrunk to fit all elements whenever it could.)
bool roy_vector_pop_back(RoyVector * vector);

// Removes all the elements in 'vector'.
// (The capacity of 'vector' will be reset.)
void roy_vector_clear(RoyVector * vector);

/* TRAVERSE */

// Traverses all elements in 'vector' using 'operate'.
void roy_vector_for_each(RoyVector * vector, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'vector' using 'operate'.
void roy_vector_for_which(RoyVector * vector, RCondition condition, ROperate operate);

#endif // ROYVECTOR_H