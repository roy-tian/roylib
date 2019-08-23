#include "../include/royuset.h"
#include "../include/royslist.h"

static size_t next_prime(size_t set_size);

RoyUSet *
roy_uset_new(size_t    capacity,
             size_t    element_size,
             size_t (* hash)(const void *),
             bool   (* equal)(const void *, const void *)) {
  RoyUSet * ret     = ROY_USET(malloc(sizeof(RoyUSet)));
  ret->capacity     = capacity;
  ret->element_size = element_size;
  ret->hash         = hash;
  ret->equal        = equal;
  ret->table        = roy_vector_new(next_prime(capacity), sizeof(RoySList**));
  return ret;
}

void roy_uset_delete(RoyUSet * uset);