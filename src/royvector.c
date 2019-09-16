#include "../include/royvector.h"

static void expand(RoyVector * vector);
static void shrink(RoyVector * vector);

RoyVector *
roy_vector_new(size_t capacity,
               size_t element_size) {
  RoyVector * ret    = (RoyVector *)malloc(sizeof(RoyVector));
  ret->data          = calloc(capacity, element_size);
  ret->size          = 0;
  ret->capacity      = capacity;
  ret->element_size  = element_size;
  ret->capacity_base = capacity;
  return ret;
}

void
roy_vector_delete(RoyVector * vector) {
  roy_array_delete((RoyArray *)vector);
}

void *
roy_vector_pointer(RoyVector * vector,
                   size_t      position) {
  return roy_array_pointer((RoyArray *)vector, position);
}

const void *
roy_vector_const_pointer(const RoyVector * vector,
                         size_t            position) {
  return roy_array_const_pointer((RoyArray *)vector, position);
}

void *
roy_vector_element(void            * dest,
                   const RoyVector * vector,
                   size_t            position) {
  return roy_array_element(dest, (RoyArray *)vector, position);
}

size_t
roy_vector_size(const RoyVector * vector) {
  return roy_array_size((RoyArray *)vector);
}

size_t
roy_vector_capacity(const RoyVector * vector) {
  return roy_array_capacity((RoyArray *)vector);
}

bool
roy_vector_empty(const RoyVector * vector) {
  return roy_array_empty((RoyArray *)vector);
}

bool
roy_vector_insert(RoyVector  * vector,
                  size_t       position,
                  const void * data) {
  expand(vector);
  return roy_array_insert((RoyArray *)vector, position, data);
}

bool
roy_vector_insert_fast(RoyVector  * vector,
                       size_t       position,
                       const void * data) {
  expand(vector);
  return roy_array_insert_fast((RoyArray *)vector, position, data);
}

bool
roy_vector_push_back(RoyVector  * vector,
                     const void * data) {
  expand(vector);
  return roy_array_push_back((RoyArray *)vector, data);
}

bool
roy_vector_erase(RoyVector * vector,
                 size_t      position) {
  bool success = roy_array_erase((RoyArray *)vector, position);
  shrink(vector);
  return success;
}

bool
roy_vector_erase_fast(RoyVector * vector,
                      size_t      position) {
  bool success = roy_array_erase_fast((RoyArray *)vector, position);
  shrink(vector);
  return success;
}

bool
roy_vector_pop_back(RoyVector * vector) {
  bool success = roy_array_pop_back((RoyArray *)vector);
  shrink(vector);
  return success;
}

void
roy_vector_clear(RoyVector * vector) {
  size_t capacity = vector->capacity_base;
  size_t element_size = vector->element_size;
  roy_vector_delete(vector);
  vector = roy_vector_new(capacity, element_size);
}

void
roy_vector_for_each(RoyVector * vector,
                    void     (* operate) (void *)) {
  roy_array_for_each((RoyArray *)vector, operate);
}

void
roy_vector_for_which(RoyVector * vector,
                     bool     (* condition) (const void *),
                     void     (* operate)         (void *)) {
  roy_array_for_which((RoyArray *)vector, condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static void
expand(RoyVector * vector) {
  if (roy_vector_size(vector) == roy_vector_capacity(vector)) {
    vector->capacity += vector->capacity_base;
    vector->data = realloc(vector->data,
                           vector->capacity * vector->element_size);
  }
}

static void
shrink(RoyVector * vector) {
  if (roy_vector_capacity(vector) - roy_vector_size(vector) >=
      vector->capacity_base) {
    vector->capacity -= vector->capacity_base;
    vector->data = realloc(vector->data,
                           vector->capacity * vector->element_size);
  }
}
