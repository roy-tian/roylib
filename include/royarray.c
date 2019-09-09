#include "royarray.h"

static bool position_valid(const RoyArray * array, size_t position, bool right_included);

RoyArray *
roy_array_new(size_t capacity,
              size_t element_size) {
  RoyArray * ret    = (RoyArray *)malloc(sizeof(RoyArray));
  ret->data         = calloc(capacity, element_size);
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
  return array->data + array->element_size * position;
}

const void *
roy_array_const_pointer(const RoyArray * array,
                        size_t           position) {
  return array->data + array->element_size * position;
}

void *
roy_array_element(void           * dest,
                  const RoyArray * array,
                  size_t           position) {
  return
  position >= 0 && position < roy_array_size(array)                           ?
  memcpy(dest, roy_array_const_pointer(array, position), array->element_size) :
  NULL;
}

size_t
roy_array_size(const RoyArray * array) {
  return array->size;
}

size_t
roy_array_capacity(const RoyArray * array) {
  return array->capacity;
}

bool
roy_array_empty(const RoyArray * array) {
  return roy_array_size(array) == 0;
}

bool
roy_array_full(const RoyArray * array) {
  return roy_array_size(array) >= roy_array_capacity(array);
}

RoyArray *
roy_array_insert(RoyArray   * array,
                 size_t       position,
                 const void * data) {
  if (position_valid(array, position, true) && !roy_array_full(array)) {
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
roy_array_push_back(RoyArray   * array,
                    const void * data) {
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
  if (position_valid(array, position, false) && !roy_array_empty(array)) {
    for (size_t i = position; i != roy_array_size(array) - 1; i++) {
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
  if (position_valid(array, position, false) && !roy_array_empty(array)) {
    memcpy(roy_array_pointer(array, position),
           roy_array_const_pointer(array, array->size - 1),
           array->element_size);
    array->size--;
  }
  return array;
}

RoyArray *
roy_array_pop_back(RoyArray * array) {
  if (!roy_array_empty(array)) {
    array->size--;
  }
  return array;
}

RoyArray *
roy_array_clear(RoyArray * array) {
  array->size = 0;
  return array;
}

void
roy_array_for_each(RoyArray * array,
                   void    (* operate) (void *)) {
  size_t array_size = roy_array_size(array);
  for (size_t i = 0; i != array_size; i++) {
    operate(roy_array_pointer(array, i));
  }
}

void
roy_array_for_which(RoyArray * array,
                    bool    (* condition) (const void *),
                    void    (* operate)         (void *)) {
  size_t array_size = roy_array_size(array);
  for (size_t i = 0; i != array_size; i++) {
    if (condition(roy_array_const_pointer(array, i))) {
      operate(roy_array_pointer(array, i));
    }
  }
}

/* PRIVATE FUNCTIONS BELOW */

static bool
position_valid(const RoyArray * array,
               size_t           position,
               bool             right_included) {
  if (position < 0) {
    return false;
  }
  if (right_included && position > roy_array_size(array)) {
    return false;
  }
  if (!right_included && position >= roy_array_size(array)) {
    return false;
  }
  return true;
}