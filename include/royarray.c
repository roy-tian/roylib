#include "royarray.h"

RoyArray *
roy_array_new(size_t capacity,
              size_t element_size) {
  RoyArray * ret    = (RoyArray *)malloc(sizeof(RoyArray));
  assert(ret != NULL);
  ret->data         = calloc(capacity, element_size);
  assert(ret->data != NULL);
  ret->size         = 0;
  ret->capacity     = capacity;
  ret->element_size = element_size;
  return ret;
}

void
roy_array_delete(RoyArray * array) {
  free(array->data);
  free(array);
}

void *
roy_array_pointer(RoyArray * array,
                  size_t     position) {
  assert(array != NULL);
  assert(position < roy_array_size(array));
  return array->data + array->element_size * position;
}

const void *
roy_array_const_pointer(const RoyArray * array,
                        size_t           position) {
  assert(array != NULL);
  assert(position < roy_array_size(array));
  return array->data + array->element_size * position;
}

void *
roy_array_element(void           * dest,
                  const RoyArray * array,
                  size_t           position) {
  assert(dest != NULL);
  assert(array != NULL);
  assert(position < roy_array_size(array));
  return memcpy(dest,
                roy_array_const_pointer(array, position),
                array->element_size);
}

size_t
roy_array_size(const RoyArray * array) {
  assert(array != NULL);
  return array->size;
}

size_t
roy_array_capacity(const RoyArray * array) {
  assert(array != NULL);
  return array->capacity;
}

bool
roy_array_empty(const RoyArray * array) {
  assert(array != NULL);
  return roy_array_size(array) == 0;
}

bool
roy_array_full(const RoyArray * array) {
  assert(array != NULL);
  return roy_array_size(array) >= roy_array_capacity(array);
}

RoyArray *
roy_array_insert(RoyArray   * array,
                 size_t       position,
                 const void * data) {
  assert(array != NULL);
  assert(position <= roy_array_size(array));
  assert(data != NULL);
  if (!roy_array_full(array)) {
    for (size_t i = roy_array_size(array); i > position; i--) {
      memcpy(roy_array_pointer(array, i),
             roy_array_const_pointer(array, (i - 1)),
             array->element_size);
    }
    memcpy(roy_array_pointer(array, position),
           data,
           array->element_size);
    array->size++;
  }
  return array;
}

RoyArray *
roy_array_insert_fast(RoyArray   * array,
                      size_t       position,
                      const void * data) {
  assert(array != NULL);
  assert(position <= roy_array_size(array));
  assert(data != NULL);
  if (!roy_array_full(array)) {
    memcpy(roy_array_pointer(array, roy_array_size(array)),
           roy_array_const_pointer(array, position),
           array->element_size);
    memcpy(roy_array_pointer(array, position),
           data,
           array->element_size);
    array->size++;
  }
  return array;
}

RoyArray *
roy_array_push_back(RoyArray   * array,
                    const void * data) {
  assert(array != NULL);
  assert(data != NULL);
  if (!roy_array_full(array)) {
    memcpy(roy_array_pointer(array, roy_array_size(array)),
           data,
           array->element_size);
    array->size++;
  }
  return array;
}

RoyArray *
roy_array_erase(RoyArray * array,
                size_t     position) {
  assert(array != NULL);
  assert(position < roy_array_size(array));
  if (!roy_array_empty(array)) {
    for (size_t i = position; i < roy_array_size(array); i++) {
      memcpy(roy_array_pointer(array, i),
             roy_array_const_pointer(array, i + 1),
             array->element_size);
    }
    array->size--;
  }
  return array;
}

RoyArray *
roy_array_erase_fast(RoyArray * array,
                     size_t     position) {
  assert(array != NULL);
  assert(position < roy_array_size(array));
  if (!roy_array_empty(array)) {
    memcpy(roy_array_pointer(array, position),
           roy_array_const_pointer(array, roy_array_size(array) - 1),
           array->element_size);
    array->size--;
  }
  return array;
}

RoyArray *
roy_array_pop_back(RoyArray * array) {
  assert(array != NULL);
  if (!roy_array_empty(array)) {
    array->size--;
  }
  return array;
}

RoyArray *
roy_array_clear(RoyArray * array) {
  assert(array != NULL);
  array->size = 0;
  return array;
}

void
roy_array_for_each(RoyArray * array,
                   void    (* operate) (void *)) {
  assert(array != NULL);
  assert(operate != NULL);
  for (size_t i = 0; i != roy_array_size(array); i++) {
    operate(roy_array_pointer(array, i));
  }
}

void
roy_array_for_which(RoyArray * array,
                    bool    (* condition) (const void *),
                    void    (* operate)         (void *)) {
  assert(array != NULL);
  assert(condition != NULL);
  assert(operate != NULL);
  for (size_t i = 0; i != roy_array_size(array); i++) {
    if (condition(roy_array_const_pointer(array, i))) {
      operate(roy_array_pointer(array, i));
    }
  }
}

