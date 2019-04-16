#include "../include/royarray.h"
#include <stdlib.h>
#include <string.h>

struct RoyArray_ {
  void * data;
  size_t length;
  size_t element_size;
  size_t capacity;
};

RoyArray * roy_array_new(size_t capacity,
                         size_t element_size) {
  RoyArray * ret = malloc(sizeof(void *) + sizeof(size_t) * 3);
  ret->data = calloc(capacity, element_size);
  ret->capacity = capacity;
  ret->element_size = element_size;
  ret->length = 0;
  return ret;
}

void roy_array_delete(RoyArray * array) {
  free(array->data);
  free(array);
}

void * roy_array_pointer(RoyArray * array,
                         int        position) {
  return array->data + array->element_size * position;
}

const void * roy_array_const_pointer(const RoyArray * array,
                                     int              position) {
  return array->data + array->element_size * position;
}

void * roy_array_element(void           * dest,
                         const RoyArray * array,
                         int              position) {
  if (position < roy_array_length(array)) {
    return memcpy(dest,
                  roy_array_const_pointer(array, position),
                  array->element_size);
  }
  return NULL;
}

size_t roy_array_length(const RoyArray * array) {
  return array->length;
}

size_t roy_array_capacity(const RoyArray * array) {
  return array->capacity;
}

bool roy_array_empty(const RoyArray * array) {
  return array->length == 0;
}

bool roy_array_full(const RoyArray * array) {
  return array->length >= array->capacity;
}

RoyArray * roy_array_insert(RoyArray   * array,
                            int          position,
                            const void * data) {
  if (!roy_array_full(array)) {
    if (position > roy_array_length(array)) { // position exceeds.
      position = roy_array_length(array);
    }
    for (size_t i = roy_array_length(array); i > position; i--) {
      memcpy(roy_array_pointer(array, i),
             roy_array_const_pointer(array, (i - 1)),
             array->element_size);             
    }
    memcpy(roy_array_pointer(array, position),
           data,
           array->element_size);
    array->length++;
  } // does nothing if array is full.
  return array;
}

RoyArray * roy_array_push_back(RoyArray   * array,
                               const void * data) {
  return roy_array_insert(array, roy_array_length(array), data);
}

RoyArray * roy_array_erase(RoyArray * array,
                           int        position) {
  if (!roy_array_empty(array)) {
    if (position >= roy_array_length(array)) { // position exceeds.
      position = roy_array_length(array) - 1;
    }
    for (size_t i = position; i < roy_array_length(array); i++) {
      memcpy(roy_array_pointer(array, i),
             roy_array_const_pointer(array, i + 1),
             array->element_size);
    }
    array->length--;
  }
  return array;
}

RoyArray * roy_array_pop_back(RoyArray * array) {
  return roy_array_erase(array, roy_array_length(array) - 1);
}

RoyArray * roy_array_erase_fast(RoyArray * array,
                                int        position) {
  if (!roy_array_empty(array)) {
    if (position >= roy_array_length(array)) { // position exceeds.
      position = roy_array_length(array) - 1;
    }
    memcpy(roy_array_pointer(array, position),
           roy_array_const_pointer(array, array->length - 1),
           array->element_size);
    memset(roy_array_pointer(array, array->length - 1),
           '\0',
           array->element_size);
    array->length--;
  }
  return array;
}

RoyArray * roy_array_clear(RoyArray * array) {
  for (size_t i = 0; i < roy_array_length(array); i++) {
    memset(roy_array_pointer(array, i),
           '\0',
           array->element_size);
  }
  array->length = 0;
  return array;
}