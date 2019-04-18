#include "../include/royvector.h"
#include <stdlib.h>
#include <string.h>

RoyVector *
expand(RoyVector * vector) {
  void * temp = calloc(roy_vector_capacity(vector) + vector->capacity_unit, 
                       vector->element_size);
  memcpy(temp, vector->data,
         roy_vector_length(vector) * vector->element_size);
  free(vector->data);
  vector->data = temp;
  vector->steps++;
  return vector;
}

RoyVector *
shrink(RoyVector * vector) {
  void * temp = calloc(roy_vector_capacity(vector) - vector->capacity_unit, 
                       vector->element_size);
  memcpy(temp, vector->data,
         roy_vector_length(vector) * vector->element_size);
  free(vector->data);
  vector->data = temp;
  vector->steps--;
  return vector;
}

RoyVector *
roy_vector_new(size_t capacity_unit,
               size_t element_size) {
  RoyVector * ret = malloc(sizeof(void *) + sizeof(size_t) * 3);
  ret->data = calloc(capacity_unit, element_size);
  ret->capacity_unit = capacity_unit;
  ret->element_size = element_size;
  ret->length = 0;
  return ret;
}

void
roy_vector_delete(RoyVector * vector) {
  free(vector->data);
  free(vector);
}

void *
roy_vector_pointer(RoyVector * vector,
                   int        position) {
  return vector->data + vector->element_size * position;
}

const void *
roy_vector_const_pointer(const RoyVector * vector,
                         int              position) {
  return vector->data + vector->element_size * position;
}

void *
roy_vector_element(void           * dest,
                   const RoyVector * vector,
                   int              position) {
  if (position < roy_vector_length(vector)) {
    return memcpy(dest,
                  roy_vector_const_pointer(vector, position),
                  vector->element_size);
  }
  return NULL;
}

size_t
roy_vector_length(const RoyVector * vector) {
  return vector->length;
}

size_t
roy_vector_capacity(const RoyVector * vector) {
  return vector->capacity_unit * vector->steps;
}

bool
roy_vector_empty(const RoyVector * vector) {
  return vector->length == 0;
}

bool
roy_vector_full(const RoyVector * vector) {
  return vector->length == roy_vector_capacity(vector);
}

RoyVector *
roy_vector_insert(RoyVector  * vector,
                  int          position,
                  const void * data) {
  if (roy_vector_full(vector)) {
    expand(vector);
  }
  if (position > roy_vector_length(vector)) { // position exceeds.
    position = roy_vector_length(vector);
  }
  for (size_t i = roy_vector_length(vector); i > position; i--) {
    memcpy(roy_vector_pointer(vector, i),
           roy_vector_const_pointer(vector, (i - 1)),
           vector->element_size);             
  }
  memcpy(roy_vector_pointer(vector, position),
         data,
         vector->element_size);
  vector->length++;
  return vector;
}

RoyVector *
roy_vector_push_back(RoyVector  * vector,
                     const void * data) {
  return roy_vector_insert(vector, roy_vector_length(vector), data);
}

RoyVector *
roy_vector_erase(RoyVector * vector,
                 int         position) {
  if (!roy_vector_empty(vector)) {
    if (position >= roy_vector_length(vector)) { // position exceeds.
      position = roy_vector_length(vector) - 1;
    }
    for (size_t i = position; i < roy_vector_length(vector); i++) {
      memcpy(roy_vector_pointer(vector, i),
             roy_vector_const_pointer(vector, i + 1),
             vector->element_size);
    }
    vector->length--;
  }
  if (roy_vector_capacity(vector) - roy_vector_length(vector) == 
      vector->capacity_unit) {
    shrink(vector);
  }
  return vector;
}

RoyVector *
roy_vector_pop_back(RoyVector * vector) {
  return roy_vector_erase(vector, roy_vector_length(vector) - 1);
}

RoyVector *
roy_vector_erase_fast(RoyVector * vector,
                      int         position) {
  if (!roy_vector_empty(vector)) {
    if (position >= roy_vector_length(vector)) { // position exceeds.
      position = roy_vector_length(vector) - 1;
    }
    memcpy(roy_vector_pointer(vector, position),
           roy_vector_const_pointer(vector, vector->length - 1),
           vector->element_size);
    memset(roy_vector_pointer(vector, vector->length - 1),
           '\0',
           vector->element_size);
    vector->length--;
  }
  if (roy_vector_capacity(vector) - roy_vector_length(vector) == 
      vector->capacity_unit) {
    shrink(vector);
  }
  return vector;
}

RoyVector *
roy_vector_clear(RoyVector * vector) {
  size_t capacity_unit = vector->capacity_unit;
  size_t element_size = vector->element_size;
  roy_vector_delete(vector);
  return vector = roy_vector_new(capacity_unit, element_size);
}