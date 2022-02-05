#include "royuset.h"
#include "../util/rhash.h"
#include "../math/roymath.h"
#include <math.h>

struct RoySList_ {
  void             * data;
  struct RoySList_ * next;
};

struct RoyUSet_ {
  RoySList  ** buckets;
  uint64_t     seed;
  RHash        hash;
  RComparer    comparer;
  RDoer        deleter;
  size_t       bucket_count;
  size_t       size;
};

static bool valid_bucket_index(const RoyUSet * uset, size_t bucket_index);

RoyUSet *
roy_uset_new(size_t    bucket_count,
             uint64_t  seed,
             RHash     hash,
             RComparer comparer,
             RDoer     deleter) {
  RoyUSet * ret     = malloc(sizeof(RoyUSet));
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash2;
  ret->comparer     = comparer;
  ret->deleter      = deleter;
  ret->bucket_count = roy_uint_prime_next(bucket_count);
  ret->size         = 0;
  ret->buckets      = calloc(roy_uset_bucket_count(ret), R_PTR_SIZE);
  for (size_t i = 0; i != roy_uset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_uset_delete(RoyUSet * uset,
                void    * user_data) {
  if (uset->deleter) {
    for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
      roy_slist_delete(uset->buckets[i], uset->deleter, user_data);
    }
  }
  free(uset->buckets);
  free(uset);
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

size_t
roy_uset_size(const RoyUSet * uset) {
  return uset->size;
}

bool
roy_uset_empty(const RoyUSet * uset) {
  return roy_uset_size(uset) == 0;
}

bool
roy_uset_insert(RoyUSet * restrict uset,
                void    * restrict data,
                size_t             data_size) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data, data_size)];
  if (roy_slist_find(*node, data, uset->comparer)) {
    return false;
  } else {
    roy_slist_push_front(*node, data);
    uset->size++;
    return true;
  }
}

bool
roy_uset_erase(RoyUSet * uset,
               size_t    bucket_index,
               size_t    bucket_position,
               void    * user_data) {
  if (!valid_bucket_index(uset, bucket_index)) {
    return false; 
  }
  RoySList ** node = &uset->buckets[bucket_index];
  size_t size = roy_slist_size(*node);
  roy_slist_erase(*node, bucket_position, uset->deleter, user_data);
  size -= roy_slist_size(*node);
  uset->size -= size;
  return true;
}

size_t
roy_uset_remove(RoyUSet    * uset,
                const void * key,
                size_t       key_size,
                void       * user_data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, key, key_size)];
  size_t remove_count =
    roy_slist_remove(*node, key, uset->comparer, uset->deleter, user_data);
  uset->size -= remove_count;
  return remove_count;
}

const void *
roy_uset_find(const RoyUSet * uset,
              const void    * data,
              size_t          data_size) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data, data_size)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (uset->comparer(data, iter->data) == 0) {
      return iter->data;
    }
  }
  return NULL;
}

void
roy_uset_clear(RoyUSet * uset,
               void    * user_data) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    roy_slist_clear(uset->buckets[i], uset->deleter, user_data);
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
                const void    * data,
                size_t          data_size) {
  return uset->hash(data, data_size, uset->seed) %
         roy_uset_bucket_count(uset);
}

double
roy_uset_load_factor(const RoyUSet * uset) {
  return (double)roy_uset_size(uset) / (double)roy_uset_bucket_count(uset);
}

void
roy_uset_for_each(RoyUSet * uset,
                  RDoer     oeprate,
                  void    * user_data) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_each(uset->buckets[i], oeprate, user_data);
    }
  }
}

void
roy_uset_for_which(RoyUSet  * uset,
                   RChecker   checker,
                   RDoer      doer,
                   void     * user_data) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_which(uset->buckets[i], checker, doer, user_data);
    }
  }
}

/* PRIVATE FUNCTIONS */

static bool
valid_bucket_index(const RoyUSet * uset,
                   size_t          bucket_index) {
  return bucket_index < roy_uset_bucket_count(uset);
}
