#include "royarray.h"

// position E [0, size], aka [begin .. end]
static bool valid_position(const RoyArray * array, size_t position);
// position E [0, size), aka [begin .. end-1]
static bool valid_data(const RoyArray * array, size_t position);

RoyArray *
roy_array_new(size_t capacity, ROperate deleter) {
  RoyArray * ret = (RoyArray *)malloc(sizeof(RoyArray));
  ret->data      = (void **)calloc(capacity, R_PTR_SIZE);
  ret->deleter   = deleter;
  ret->capacity  = capacity;
  ret->size      = 0;
  return ret;
}

void
roy_array_delete(RoyArray * array) {
  roy_array_for_each(array, array->deleter);
  free(array->data);
  free(array);
  array = NULL;
}

void *
roy_array_pointer(RoyArray * array,
                  size_t     position) {
  return valid_position(array, position) ? array->data[position] : NULL;
}

const void *
roy_array_cpointer(const RoyArray * array,
                   size_t           position) {
  return valid_position(array, position) ? array->data[position] : NULL;
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

bool
roy_array_insert(RoyArray * array,
                 size_t     position,
                 void     * data) {
  if (valid_position(array, position) && !roy_array_full(array)) {
    for (size_t i = roy_array_size(array); i > position; i--) {
      array->data[i] = array->data[i - 1];
    }
    array->data[position] = data;
    array->size++;
    return true;
  }
  return false;
}

bool
roy_array_insert_fast(RoyArray * array,
                      size_t     position,
                      void     * data) {
  if (valid_position(array, position) && !roy_array_full(array)) {
    array->data[roy_array_size(array)] = array->data[position];
    array->data[position] = data;
    array->size++;
    return true;
  }
  return false;
}

bool
roy_array_push_back(RoyArray * array,
                    void     * data) {
  if (!roy_array_full(array)) {
    array->data[roy_array_size(array)] = data;
    array->size++;
    return true;
  }
  return false;
}

bool
roy_array_erase(RoyArray * array,
                size_t     position) {
  if (valid_data(array, position)) {
    array->deleter(roy_array_pointer(array, position));
    for (size_t i = position; i < roy_array_size(array); i++) {
      array->data[i] = array->data[i + 1];
    }
    array->size--;
    return true;
  }
  return false;
}

bool
roy_array_erase_fast(RoyArray * array,
                     size_t     position) {
  if (valid_data(array, position)) {
    array->deleter(roy_array_pointer(array, position));
    array->data[position] = array->data[roy_array_size(array) - 1];
    array->size--;
    return true;
  }
  return false;
}

bool
roy_array_pop_back(RoyArray * array) {
  if (!roy_array_empty(array)) {
    array->deleter(roy_array_pointer(array, roy_array_size(array) - 1));
    array->size--;
    return true;
  }
  return false;
}

void
roy_array_clear(RoyArray * array) {
  roy_array_for_each(array, array->deleter);
  array->size = 0;
}

void
roy_array_for_each(RoyArray * array,
                   ROperate   operate) {
  for (size_t i = 0; i != roy_array_size(array); i++) {
    operate(roy_array_pointer(array, i));
  }
}

void
roy_array_for_which(RoyArray   * array,
                    RCondition   condition,
                    ROperate     operate) {
  for (size_t i = 0; i != roy_array_size(array); i++) {
    if (condition(roy_array_cpointer(array, i))) {
      operate(roy_array_pointer(array, i));
    }
  }
}

/* PRIVATE FUNCTIONS DOWN HERE */

static bool
valid_position(const RoyArray * array,
               size_t           position) {
  return position <= roy_array_size(array);
}

static bool
valid_data(const RoyArray * array,
           size_t           position) {
  return position < roy_array_size(array) && !roy_array_empty(array);
}
