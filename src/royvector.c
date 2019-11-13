#include "../include/royvector.h"

static bool need_expand(const RoyVector * vector);
static bool need_shrink(const RoyVector * vector);
static void expand(RoyVector * vector);
static void shrink(RoyVector * vector);

RoyVector *
roy_vector_new(size_t   capacity,
               ROperate deleter) {
  RoyVector * ret    = (RoyVector *)malloc(sizeof(RoyVector));
  ret->data          = (void **)calloc(capacity, PTR_SIZE);
  ret->deleter       = deleter;
  ret->capacity      = capacity;
  ret->size          = 0;
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
  return roy_array_pointer((RoyArray *) vector, position);
}

const void *
roy_vector_cpointer(const RoyVector * vector,
                    size_t            position) {
  return roy_array_cpointer((RoyArray *) vector, position);
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
roy_vector_insert(RoyVector * vector,
                  size_t      position,
                  void      * data) {
  expand(vector);
  return roy_array_insert((RoyArray *)vector, position, data);
}

bool
roy_vector_insert_fast(RoyVector * vector,
                       size_t      position,
                       void      * data) {
  expand(vector);
  return roy_array_insert_fast((RoyArray *)vector, position, data);
}

bool
roy_vector_push_back(RoyVector * vector,
                     void      * data) {
  expand(vector);
  return roy_array_push_back((RoyArray *)vector, data);
}

bool
roy_vector_erase(RoyVector * vector,
                 size_t      position) {
  if (roy_array_erase((RoyArray *)vector, position)) {
    shrink(vector);
    return true;
  }
  return false;
}

bool
roy_vector_erase_fast(RoyVector * vector,
                      size_t      position) {
  if (roy_array_erase_fast((RoyArray *)vector, position)) {
    shrink(vector);
    return true;
  }
  return false;
}

bool
roy_vector_pop_back(RoyVector * vector) {
  if (roy_array_pop_back((RoyArray *)vector)) {
    shrink(vector);
    return true;
  }
  return false;
}

void
roy_vector_clear(RoyVector * vector) {
  roy_vector_for_each(vector, vector->deleter);
  vector->capacity = vector->capacity_base;
  vector->size = 0;
  vector->data = (void **)realloc(vector->data,
                                  roy_vector_capacity(vector) * PTR_SIZE);
}

void
roy_vector_for_each(RoyVector * vector,
                    ROperate    operate) {
  roy_array_for_each((RoyArray *)vector, operate);
}

void
roy_vector_for_which(RoyVector  * vector,
                     RCondition   condition,
                     ROperate     operate) {
  roy_array_for_which((RoyArray *)vector, condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static bool
need_expand(const RoyVector * vector) {
  return roy_vector_size(vector) >= roy_vector_capacity(vector);
}

static bool
need_shrink(const RoyVector * vector) {
  return roy_vector_capacity(vector) - roy_vector_size(vector) >=
         vector->capacity_base;
}

static void
expand(RoyVector * vector) {
  if (need_expand(vector)) {
    vector->capacity += vector->capacity_base;
    vector->data =
      (void **)realloc(vector->data, roy_vector_capacity(vector) * PTR_SIZE);
  }
}

static void
shrink(RoyVector * vector) {
  if (need_shrink(vector)) {
    vector->capacity -= vector->capacity_base;
    vector->data =
      (void **)realloc(vector->data, roy_vector_capacity(vector) * PTR_SIZE);
  }
}
