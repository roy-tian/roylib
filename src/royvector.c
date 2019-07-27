#include "../include/royvector.h"

static RoyVector expand(RoyVector vector);
static RoyVector shrink(RoyVector vector);
static bool need_expand(const RoyVector vector);
static bool need_shrink(const RoyVector vector);

RoyVector
roy_vector_new(size_t capacity,
               size_t element_size) {
  RoyVector ret    = ROY_VECTOR(malloc(sizeof(struct _RoyVector)));
  ret->data          = calloc(capacity, element_size);
  ret->size          = 0;
  ret->capacity      = capacity;
  ret->element_size  = element_size;
  ret->capacity_base = capacity;
  return ret;
}

void
roy_vector_delete(RoyVector vector) {
  roy_array_delete(ROY_ARRAY(vector));
}

RoyElement
roy_vector_pointer(RoyVector vector,
                   int         position) {
  return roy_array_pointer(ROY_ARRAY(vector), position);
}

const RoyElement
roy_vector_const_pointer(const RoyVector vector,
                         int               position) {
  return roy_array_const_pointer(ROY_ARRAY(vector), position);
}

RoyElement
roy_vector_element(RoyElement dest,
                   const RoyVector vector,
                   int               position) {
  return roy_array_element(dest, ROY_ARRAY(vector), position);
}

size_t
roy_vector_size(const RoyVector vector) {
  return roy_array_size(ROY_ARRAY(vector));
}

size_t
roy_vector_capacity(const RoyVector vector) {
  return roy_array_capacity(ROY_ARRAY(vector));
}

bool
roy_vector_empty(const RoyVector vector) {
  return roy_array_empty(ROY_ARRAY(vector));
}

RoyVector
roy_vector_insert(RoyVector  vector,
                  int          position,
                  const RoyElement data) {
  if (need_expand(vector)) {
    expand(vector);
  }
  roy_array_insert(ROY_ARRAY(vector), position, data);
  return vector;
}

RoyVector
roy_vector_push_back(RoyVector  vector,
                     const RoyElement data) {
  if (need_expand(vector)) {
    expand(vector);
  }
  roy_array_push_back(ROY_ARRAY(vector), data);
  return vector;
}

RoyVector
roy_vector_erase(RoyVector vector,
                 int         position) {
  roy_array_erase(ROY_ARRAY(vector), position);
  if (need_shrink(vector)) {
    shrink(vector);
  }
  return vector;
}

RoyVector
roy_vector_erase_fast(RoyVector vector,
                      int         position) {
  roy_array_erase_fast(ROY_ARRAY(vector), position);
  if (need_shrink(vector)) {
    shrink(vector);
  }
  return vector;
}

RoyVector
roy_vector_pop_back(RoyVector vector) {
  roy_array_pop_back(ROY_ARRAY(vector));
  if (need_shrink(vector)) {
    shrink(vector);
  }
  return vector;
}

RoyVector
roy_vector_clear(RoyVector vector) {
  size_t capacity = vector->capacity_base;
  size_t element_size = vector->element_size;
  roy_vector_delete(vector);
  return vector = roy_vector_new(capacity, element_size);
}

void
roy_vector_for_each(RoyVector vector,
                    RoyOperate operate) {
  roy_array_for_each(ROY_ARRAY(vector), operate);
}

void
roy_vector_for_which(RoyVector vector,
                     RoyCondition condition,
                     RoyOperate operate) {
  roy_array_for_which(ROY_ARRAY(vector), condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static RoyVector
expand(RoyVector vector) {
  vector->capacity += vector->capacity_base;
  vector->data = realloc(vector->data,
                         vector->capacity * vector->element_size);
  return vector;
}

static RoyVector
shrink(RoyVector vector) {
  vector->capacity -= vector->capacity_base;
  vector->data = realloc(vector->data,
                         vector->capacity * vector->element_size);
  return vector;
}

static bool
need_expand(const RoyVector vector) {
  return roy_vector_size(vector) == roy_vector_capacity(vector);
}

static bool
need_shrink(const RoyVector vector) {
  return roy_vector_capacity(vector) - roy_vector_size(vector) >= 
         vector->capacity_base;
}