#include "roymmap.h"
#include "../util/roypair.h"

RoyMMap *
roy_mmap_new(RCompare comparer,
             ROperate deleter) {
  RoyMMap * ret = malloc(sizeof(RoyMMap));
  ret->root     = NULL;
  ret->comparer = comparer;
  ret->deleter  = deleter;
  return ret;
}

void
roy_mmap_delete(RoyMMap * mmap,
                void    * user_data) {
  roy_mmap_clear(mmap, user_data);
  free(mmap);
}

void *
roy_mmap_min(RoyMMap * mmap) {
  return roy_pair_value(roy_mset_min(mmap->root)->key);
}

void * roy_mmap_max(RoyMMap * mmap) {
  return roy_pair_value(roy_mset_max(mmap->root)->key);
}

const void *
roy_mmap_cmin(const RoyMMap * mmap) {
  return roy_cpair_value(roy_mset_cmin(mmap->root)->key);
}

const void *
roy_mmap_cmax(const RoyMMap * mmap) {
  return roy_cpair_value(roy_mset_cmax(mmap->root)->key);
}

size_t
roy_mmap_size(const RoyMMap * mmap) {
  return roy_mset_size(mmap->root);
}

bool roy_mmap_empty(const RoyMMap * mmap) {
  return roy_mset_empty(mmap->root);
}

RoyMMap *
roy_mmap_insert(RoyMMap * restrict mmap,
                void    * restrict key,
                void    * restrict value) {
  mmap->root =
    roy_mset_insert(&mmap->root, roy_pair_new(key, value), mmap->comparer);
  return mmap;
}

RoyMMap *
roy_mmap_remove(RoyMMap    * mmap,
                const void * key) {
  mmap->root =
    roy_mset_remove(&mmap->root, key, mmap->comparer, mmap->deleter, NULL);
  return mmap;
}

void
roy_mmap_clear(RoyMMap * mmap,
               void    * user_data) {
  roy_mset_clear(mmap->root, mmap->deleter, user_data);
}

size_t
roy_mmap_count(const RoyMMap * mmap,
               const void    * key) {
  RoyCPair * pair = roy_cpair_new(key, NULL);
  size_t ret = roy_mset_count(mmap->root, pair, (RCompare)mmap->comparer);
  free(pair);
  return ret;
}

void *
roy_mmap_find(RoyMMap    * mmap,
              const void * key) {
  RoyCPair pair = { key, NULL };
  RoyMSet * mset = roy_mset_find(mmap->root, &pair, (RCompare)mmap->comparer);
  return mset ? roy_pair_value(mset->key) : NULL;
}

void
roy_mmap_for_each(RoyMMap  * mmap,
                  ROperate   operate,
                  void     * user_data) {
  roy_mset_for_each(mmap->root, operate, user_data);
}

void
roy_mmap_for_which(RoyMMap    * mmap,
                   RCondition   condition,
                   ROperate     operate,
                   void       * user_data) {
  roy_mset_for_which(mmap->root, condition, operate, user_data);
}
