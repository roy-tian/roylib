#include "royumset.h"
#include "royuset.h"
#include "trivials/hash.h"
#include "trivials/roynumber.h"
#include <math.h>

RoyUMSet *
roy_umset_new(size_t   bucket_count,
              uint64_t seed,
              RHash    hash,
              RCompare comparer,
              ROperate deleter) {
  RoyUMSet * ret    = (RoyUMSet *)malloc(sizeof(RoyUSet));
  ret->buckets      = (RoySList **)calloc(roy_umset_bucket_count(ret),
                                          R_PTR_SIZE);
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash2;
  ret->comparer      = comparer;
  ret->deleter      = deleter;
  ret->bucket_count = roy_uint64_next_prime(bucket_count);
  ret->size         = 0;
  for (size_t i = 0; i != roy_umset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_umset_delete(RoyUMSet * umset) {
  roy_uset_delete((RoyUSet *)umset);
}

const void *
roy_umset_cpointer(const RoyUMSet * umset,
                   int              bucket_index,
                   int              bucket_position) {
  return roy_uset_cpointer((RoyUSet *)umset, bucket_index, bucket_position);
}

size_t
roy_umset_size(const RoyUMSet * umset) {
  return roy_uset_size((RoyUSet *)umset);
}

bool
roy_umset_empty(const RoyUMSet * umset) {
  return roy_uset_empty((RoyUSet *)umset);
}

void
roy_umset_insert(RoyUMSet * umset,
                 void     * data,
                 size_t     data_size) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data, data_size)];
  roy_slist_push_front(*node, data);
  umset->size++;
}

bool
roy_umset_erase(RoyUMSet * umset,
                int        bucket_index,
                int        bucket_position) {
  return roy_uset_erase((RoyUSet *)umset, bucket_index, bucket_position);
}

size_t
roy_umset_remove(RoyUMSet   * umset,
                 const void * data,
                 size_t       data_size) {
  return roy_uset_remove((RoyUSet *)umset, data, data_size);
}

const void *
roy_umset_find(const RoyUMSet * umset,
               const void     * data,
               size_t           data_size) {
  return roy_uset_find((RoyUSet *)umset, data, data_size);
}

void
roy_umset_clear(RoyUMSet * umset) {
  roy_uset_clear((RoyUSet *)umset);
}

size_t
roy_umset_bucket_count(const RoyUMSet * umset) {
  return roy_uset_bucket_count((RoyUSet *)umset);
}

size_t
roy_umset_bucket_size(const RoyUMSet * umset,
                      int              bucket_index) {
  return roy_uset_bucket_size((RoyUSet *)umset, bucket_index);
}

int64_t
roy_umset_bucket(const RoyUMSet * umset,
                 const void     * data,
                 size_t           data_size) {
  return roy_uset_bucket((RoyUSet *)umset, data, data_size);
}

double
roy_umset_load_factor(const RoyUMSet * umset) {
  return roy_uset_load_factor((RoyUSet *)umset);
}

RoyUMSet * roy_umset_rehash(RoyUMSet * umset,
                            size_t     bucket_count,
                            uint64_t   seed) {
  return (RoyUMSet *)roy_uset_rehash((RoyUSet *)umset, bucket_count, seed);
}

void
roy_umset_for_each(RoyUMSet * umset,
                   ROperate   operate) {
  roy_uset_for_each((RoyUSet *)umset, operate);
}

void
roy_umset_for_which(RoyUMSet   * umset,
                    RCondition   condition,
                    ROperate     operate) {
  roy_uset_for_which((RoyUSet *)umset, condition, operate);
}
