#include "royumap.h"

struct RoyUSet_ {
  RoySList  ** buckets;
  uint64_t     seed;
  RHash        hash;
  RComparer    comparer;
  RDoer        deleter;
  size_t       bucket_count;
  size_t       size;
};

struct RoyUMap_ {
  RoyUSet * uset;
};

RoyUMap *
roy_umap_new(size_t    bucket_count,
             uint64_t  seed,
             RHash     hash,
             RComparer comparer,
             RDoer     deleter) {
  RoyUMap * ret = malloc(sizeof(RoyUMap));
  ret->uset = roy_uset_new(bucket_count, seed, hash, comparer, deleter);
  return ret;
}

void
roy_umap_delete(RoyUMap * umap,
                void    * user_data) {
  roy_uset_delete(umap->uset, user_data);
  free(umap);
}

const RoyCPair *
roy_umap_cpointer(const RoyUMap * umap,
                  size_t          bucket_index,
                  size_t          bucket_position) {
  return roy_uset_cpointer(umap->uset, bucket_index, bucket_position);
}

size_t
roy_umap_size(const RoyUMap * umap) {
  return roy_uset_size(umap->uset);
}

bool
roy_umap_empty(const RoyUMap * umap) {
  return roy_uset_empty(umap->uset);
}

bool
roy_umap_insert(RoyUMap * restrict umap,
                void    * restrict key,
                size_t             key_size,
                void    * restrict value) {
  RoySList ** node =
    &umap->uset->buckets[roy_umap_bucket(umap, key, key_size)];
  if (roy_slist_find(*node, key, umap->uset->comparer)) {
    return false;
  } else {
    roy_slist_push_front(*node, roy_pair_new(key, value));
    umap->uset->size++;
    return true;
  }
}

bool
roy_umap_erase(RoyUMap * umap,
               size_t    bucket_index,
               size_t    bucket_position,
               void    * user_data) {
  return roy_uset_erase(umap->uset, bucket_index, bucket_position, user_data);
}

size_t
roy_umap_remove(RoyUMap    * umap,
                const void * key,
                size_t       key_size,
                void       * user_data) {
  return roy_uset_remove(umap->uset, key, key_size, user_data);
}

void
roy_umap_clear(RoyUMap * umap,
               void    * user_data) {
  return roy_uset_clear(umap->uset, user_data);
}

const void *
roy_umap_find(const RoyUMap * umap,
              const void    * key,
              size_t          key_size) {
  return (*(RoyCPair *)roy_uset_find(umap->uset, key, key_size)).value;
}

size_t
roy_umap_bucket_count(const RoyUMap * umap) {
  return roy_uset_bucket_count(umap->uset);
}

size_t
roy_umap_bucket_size(const RoyUMap * umap,
                     size_t          bucket_index) {
  return roy_uset_bucket_size(umap->uset, bucket_index);
}

int64_t
roy_umap_bucket(const RoyUMap * umap,
                const void    * key,
                size_t          key_size) {
  return roy_uset_bucket(umap->uset, key, key_size);
}

double
roy_umap_load_factor(const RoyUMap * umap) {
  return roy_uset_load_factor(umap->uset);
}

void
roy_umap_for_each(RoyUMap  * umap,
                  RDoer   oeprate,
                  void     * user_data) {
  roy_uset_for_each(umap->uset, oeprate, user_data);
}

void
roy_umap_for_which(RoyUMap  * umap,
                   RChecker   checker,
                   RDoer      doer,
                   void     * user_data) {
  roy_uset_for_which(umap->uset, checker, doer, user_data);
}
