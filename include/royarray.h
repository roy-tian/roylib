#ifndef ROYARRAY_H
#define ROYARRAY_H

#include "royinit.h"

struct RoyArray_ {
  void     ** data;
  ROperate    deleter;
  size_t      capacity;
  size_t      size;
};

// RoyArray: a container that encapsulates fixed size arrays.
typedef struct RoyArray_ RoyArray;

/* CONSTRUCTION AND DESTRUCTION */

// Creates an RoyArray and allocates sufficient memory for it.
// [PARAMETERS]
//   capacity - how many elements the new array can store.
//    deleter - a function to release elements.
// [RETURN VALUE]
//   The newly build RoyArray.
// [NOTES]
//   The behavior is undefined if any immature RoyArrays are operated.
RoyArray * roy_array_new(size_t capacity, ROperate deleter);

// Releases all the elements and destroies the RoyArray - 'array' itself.
// [NOTES]
//   Always call this function after the work is done by the given 'array',
//   otherwise memory leak will occur.
void roy_array_delete(RoyArray * array);

/* ELEMENT ACCESS */

// Returns a pointer to the element at 'position' in 'array'.
// [NOTES]
//   Returns NULL if 'position' exceeds.
void * roy_array_pointer(RoyArray * array, size_t position);

// Returns a const pointer to the element at 'position' in 'array'.
// [NOTES]
//   Returns NULL if 'position' exceeds.
const void * roy_array_cpointer(const RoyArray * array, size_t position);

// Returns a typed pointer to the element at 'position', or NULL if 'position' exceeds or 'array' is empty.
#define roy_array_at(array, position, element_type) \
        ((element_type*)(roy_array_pointer((array), (position))))

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

// Inserts an element named 'data' into 'array' at 'position', returns whether the insertion is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'position' exceeds, or 'array' is full.)
// (Deprecated when 'array' is huge and 'position' is small, can be very slow.)
bool roy_array_insert(RoyArray * array, size_t position, void * data);

// Moves the element at 'position' to the back of 'array', puts 'data' there, returns whether the operation is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'position' exceeds, or 'array' is full.)
// (Recommended when element order is irrelevant.)
bool roy_array_insert_fast(RoyArray * array, size_t position, void * data);

// Adds an element named 'data' to the back of 'array', returns whether the operation is successful.
// (The behavior is undefined if 'data' is uninitialized, or mis-sized.)
// (Fails if 'array' is full.)
bool roy_array_push_back(RoyArray * array, void * data);

// Removes an element at 'position', and fill with its next recursively, returns whether the operation is successful.
// (Fails if 'position' exceeds, or 'array' is empty.)
// (Deprecated when 'array' is huge and 'position' is small, can be very slow.)
bool roy_array_erase(RoyArray * array, size_t position);

// Removes an element at 'position', and fill the empty position with the last element, returns whether the operation is successful.
// (Fails if 'position' exceeds, or 'array' is empty.)
// (Recommended when element order is irrelevant.)
bool roy_array_erase_fast(RoyArray * array, size_t position);

// Removes the last element of 'array', returns whether the operation is successful.
// (Fails if 'array' is empty.)
bool roy_array_pop_back(RoyArray * array);

// Removes all the elements in 'array'.
void roy_array_clear(RoyArray * array);

/* TRAVERSE */

// Traverses all elements in 'array' using 'operate' sequentially.
void roy_array_for_each(RoyArray * array, ROperate operate);

// Traverses all elements whichever meets 'condition' in 'array' using 'operate'.
void roy_array_for_which(RoyArray * array, RCondition condition, ROperate operate);

#endif // ROYARRAY_H