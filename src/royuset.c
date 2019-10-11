#include "../include/royuset.h"
#include "../include/roynumber.h"
#include <math.h>

static bool valid_bucket_index(const RoyUSet * uset, size_t bucket_index);

RoyUSet *
roy_uset_new(size_t   bucket_count,
             size_t   element_size,
             uint64_t seed,
             RHash    hash,
             RCompare compare) {
  RoyUSet * ret     = (RoyUSet *)malloc(sizeof(RoyUSet));
  ret->bucket_count = roy_ullong_next_prime(bucket_count);
  ret->element_size = element_size;
  ret->size         = 0;
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash64A;
  ret->compare      = compare;
  ret->buckets      = (RoySList **)calloc(roy_uset_bucket_count(ret),
                                          sizeof(RoySList*));
  for (size_t i = 0; i != roy_uset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_uset_delete(RoyUSet * uset) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    roy_slist_delete(uset->buckets[i]);
  }
  free(uset->buckets);
  free(uset);
  uset = NULL;
}

const void *
roy_uset_cpointer(const RoyUSet * uset,
                  size_t          bucket_index,
                  size_t          bucket_position) {
  if (!valid_bucket_index(uset, bucket_index)) {
    return NULL;
  }
  const RoySList * iter = roy_slist_citerator(uset->buckets[bucket_index],
                                              bucket_position);
  return iter ? iter->data : NULL;
}

void *
roy_uset_element(void    * dest,
                 RoyUSet * uset,
                 size_t    bucket_index,
                 size_t    bucket_position) {
  return valid_bucket_index(uset, bucket_index)         ?
         roy_slist_element(dest,
                           uset->buckets[bucket_index],
                           uset->element_size,
                           bucket_position)             :
         NULL;
}

size_t
roy_uset_size(const RoyUSet * uset) {
  return uset->size;
}

bool
roy_uset_empty(const RoyUSet * uset) {
  return roy_uset_size(uset) == 0;
}

bool
roy_uset_insert(RoyUSet    * uset,
                const void * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (uset->compare(data, iter->data) == 0) {
      return false;
    }
  }
  roy_slist_push_front(*node, data, uset->element_size);
  uset->size++;
  return true;
}

bool
roy_uset_erase(RoyUSet * uset,
               size_t    bucket_index,
               size_t    bucket_position) {
  if (!valid_bucket_index(uset, bucket_index)) {
    return false;
  }
  RoySList ** node = &uset->buckets[bucket_index];
  size_t size = roy_slist_size(*node);
  roy_slist_erase(*node, bucket_position);
  size -= roy_slist_size(*node);
  uset->size -= size;
  return true;
}

size_t
roy_uset_remove(RoyUSet    * uset,
                const void * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  size_t remove_count = roy_slist_remove(*node, data, uset->compare);
  uset->size -= remove_count;
  return remove_count;
}

const void *
roy_uset_find(const RoyUSet * uset,
              const void    * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (uset->compare(data, iter->data) == 0) {
      return iter->data;
    }
  }
  return NULL;
}

void
roy_uset_clear(RoyUSet * uset) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    roy_slist_clear(uset->buckets[i]);
  }
}

size_t
roy_uset_bucket_count(const RoyUSet * uset) {
  return uset->bucket_count;
}

size_t
roy_uset_bucket_size(const RoyUSet * uset,
                     size_t          bucket_index) {
  return roy_slist_size(uset->buckets[bucket_index]);
}

int64_t
roy_uset_bucket(const RoyUSet * uset,
                const void    * data) {
  return uset->hash(data, uset->element_size, uset->seed) %
         roy_uset_bucket_count(uset);
}

double
roy_uset_load_factor(const RoyUSet * uset) {
  return (double)roy_uset_size(uset) / (double)roy_uset_bucket_count(uset);
}

// TODO
RoyUSet * roy_uset_rehash(RoyUSet * uset,
                          size_t    bucket_count,
                          uint64_t  seed) {
  return uset;
}

void
roy_uset_for_each(RoyUSet * uset,
                  ROperate  operate) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_each(uset->buckets[i], operate);
    }
  }
}

void
roy_uset_for_which(RoyUSet    * uset,
                   RCondition   condition,
                   ROperate     operate) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_which(uset->buckets[i], condition, operate);
    }
  }
}

/* PRIVATE FUNCTIONS */

static bool
valid_bucket_index(const RoyUSet * uset,
                   size_t          bucket_index) {
  return bucket_index < roy_uset_bucket_count(uset);
}
