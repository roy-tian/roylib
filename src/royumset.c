#include "../include/royumset.h"
#include "../include/royuset.h"
#include "../include/royhash.h"
#include "../include/roynumber.h"
#include <math.h>

RoyUMSet *
roy_umset_new(size_t   bucket_count,
              size_t   element_size,
              uint64_t seed,
              RHash    hash,
              RCompare compare) {
  RoyUMSet * ret    = (RoyUMSet *)malloc(sizeof(RoyUMSet));
  ret->bucket_count = roy_uint64_next_prime(bucket_count);
  ret->element_size = element_size;
  ret->size         = 0;
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash2;
  ret->compare      = compare;
  ret->buckets      = (RoySList **)calloc(roy_umset_bucket_count(ret),
                                          sizeof(RoySList*));
  for (size_t i = 0; i != roy_umset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_umset_delete(RoyUMSet * umset) {
  roy_uset_delete((RoyUSet *)umset);
}

RCData
roy_umset_cpointer(const RoyUMSet * umset,
                   int              bucket_index,
                   int              bucket_position) {
  return roy_uset_cpointer((RoyUSet *)umset, bucket_index, bucket_position);
}

RData
roy_umset_element(void     * dest,
                  RoyUMSet * umset,
                  int        bucket_index,
                  int        bucket_position) {
  return
  roy_uset_element(dest, (RoyUSet *)umset, bucket_index, bucket_position);
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
roy_umset_insert(RoyUMSet  * umset,
                 RCData data) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data)];
  roy_slist_push_front(*node, data, umset->element_size);
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
                 RCData data) {
  return roy_uset_remove((RoyUSet *)umset, data);
}

RCData
roy_umset_find(const RoyUMSet * umset,
               const void     * data) {
  return roy_uset_find((RoyUSet *)umset, data);
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
                 const void     * data) {
  return roy_uset_bucket((RoyUSet *)umset, data);
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
