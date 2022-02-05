#include "royarray.h"

struct RoyArray_ {
  void   ** data;
  RDoer     deleter;
  size_t    capacity;
  size_t    size;
};

// position E [0, size], i.e. [begin .. end]
static bool valid_position(const RoyArray * array, size_t position);
// position E [0, size), i.e. [begin .. end-1]
static bool valid_data(const RoyArray * array, size_t position);

RoyArray *
roy_array_new(size_t capacity, RDoer deleter) {
  RoyArray * ret = malloc(sizeof(RoyArray));
  ret->data      = calloc(capacity, R_PTR_SIZE);
  ret->deleter   = deleter;
  ret->capacity  = capacity;
  ret->size      = 0;
  return ret;
}

void
roy_array_delete(RoyArray * array, void * user_data) {
  roy_array_for_each(array, array->deleter, user_data);
  free(array->data);
  free(array);
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
roy_array_insert(RoyArray * restrict array,
                 size_t              position,
                 void     * restrict data) {
  if (!valid_position(array, position) || roy_array_full(array) || !data) {
    return false;
  }
  for (size_t i = roy_array_size(array); i > position; i--) {
    array->data[i] = array->data[i - 1];
  }
  array->data[position] = data;
  array->size++;
  return true;
}

bool
roy_array_insert_fast(RoyArray * restrict array,
                      size_t              position,
                      void     * restrict data) {
  if (!valid_position(array, position) || roy_array_full(array) || !data) {
    return false;
  }
  array->data[roy_array_size(array)] = array->data[position];
  array->data[position] = data;
  array->size++;
  return true;
}

bool
roy_array_push_back(RoyArray * restrict array,
                    void     * restrict data) {
  if (roy_array_full(array) || !data) {
    return false;
  }
  array->data[roy_array_size(array)] = data;
  array->size++;
  return true;
}

bool
roy_array_erase(RoyArray * array,
                size_t     position) {
  if (!valid_data(array, position)) {
    return false;
  }
  array->deleter(roy_array_pointer(array, position), NULL);
  for (size_t i = position; i < roy_array_size(array); i++) {
    array->data[i] = array->data[i + 1];
  }
  array->size--;
  return true;
}

bool
roy_array_erase_fast(RoyArray * array,
                     size_t     position) {
  if (!valid_data(array, position)) {
    return false;
  }
  array->deleter(roy_array_pointer(array, position), NULL);
  array->data[position] = array->data[roy_array_size(array) - 1];
  array->size--;
  return true;
}

bool
roy_array_pop_back(RoyArray * array) {
  if (roy_array_empty(array)) {
    return false;
  }
  array->deleter(roy_array_pointer(array, roy_array_size(array) - 1), NULL);
  array->size--;
  return true;
}

void
roy_array_clear(RoyArray * array) {
  roy_array_for_each(array, array->deleter, NULL);
  array->size = 0;
}

void
roy_array_for_each(RoyArray * array,
                   RDoer      doer,
                   void     * user_data) {
  for (size_t i = 0; i != roy_array_size(array); i++) {
    doer(roy_array_pointer(array, i), user_data);
  }
}

void
roy_array_for_which(RoyArray * array,
                    RChecker   checker,
                    RDoer      doer,
                    void     * user_data) {
  for (size_t i = 0; i != roy_array_size(array); i++) {
    if (checker(roy_array_cpointer(array, i))) {
      doer(roy_array_pointer(array, i), user_data);
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
