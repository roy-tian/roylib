#include "royummap.h"

RoyUMMap *
roy_ummap_new(size_t   bucket_count, 
              uint64_t seed, 
              RHash    hash, 
              RCompare comparer, 
              ROperate deleter) {
  RoyUMMap * ret = malloc(sizeof(RoyUMMap));
  ret->umset = roy_umset_new(bucket_count, seed, hash, comparer, deleter);
  return ret;
}

void
roy_ummap_delete(RoyUMMap * ummap,
                 void     * user_data) {
  roy_umset_delete(ummap->umset, user_data);
  free(ummap);
}

const RoyCPair *
roy_ummap_cpointer(const RoyUMMap * ummap,
                   size_t           bucket_index,
                   size_t           bucket_position) {
  return roy_umset_cpointer(ummap->umset, bucket_index, bucket_position);
}

size_t
roy_ummap_size(const RoyUMMap * ummap) {
  return roy_umset_size(ummap->umset);
}

bool
roy_ummap_empty(const RoyUMMap * ummap) {
  return roy_umset_empty(ummap->umset);
}

void
roy_ummap_insert(RoyUMMap * restrict ummap,
                 void     * restrict key,
                 size_t              key_size,
                 void     * restrict value) {
  RoySList ** node =
    &ummap->umset->buckets[roy_ummap_bucket(ummap, key, key_size)];
  roy_slist_push_front(*node, roy_pair_new(key, value));
  ummap->umset->size++;
}

bool
roy_ummap_erase(RoyUMMap * ummap,
                size_t     bucket_index,
                size_t     bucket_position,
                void     * user_data) {
  return
    roy_umset_erase(ummap->umset, bucket_index, bucket_position, user_data);
}

size_t
roy_ummap_remove(RoyUMMap   * ummap,
                 const void * key,
                 size_t       key_size,
                 void       * user_data) {
  return roy_umset_remove(ummap->umset, key, key_size, user_data);
}

void
roy_ummap_clear(RoyUMMap * ummap,
                void     * user_data) {
  return roy_umset_clear(ummap->umset, user_data);
}

const void *
roy_ummap_find(const RoyUMMap * ummap,
               const void     * key,
               size_t           key_size) {
  return (*(RoyCPair *)roy_umset_find(ummap->umset, key, key_size)).value;
}

size_t
roy_ummap_bucket_count(const RoyUMMap * ummap) {
  return roy_umset_bucket_count(ummap->umset);
}

size_t
roy_ummap_bucket_size(const RoyUMMap * ummap,
                      size_t           bucket_index) {
  return roy_umset_bucket_size(ummap->umset, bucket_index);
}

int64_t
roy_ummap_bucket(const RoyUMMap * ummap,
                 const void     * key,
                 size_t           key_size) {
  return roy_umset_bucket(ummap->umset, key, key_size);
}

double
roy_ummap_load_factor(const RoyUMMap * ummap) {
  return roy_umset_load_factor(ummap->umset);
}

void
roy_ummap_for_each(RoyUMMap * ummap,
                   ROperate   oeprate,
                   void     * user_data) {
  roy_umset_for_each(ummap->umset, oeprate, user_data);
}

void
roy_ummap_for_which(RoyUMMap   * ummap,
                    RCondition   condition,
                    ROperate     operate,
                    void       * user_data) {
  roy_umset_for_which(ummap->umset, condition, operate, user_data);
}
