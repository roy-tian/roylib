#include "roymmap.h"
#include "trivials/roypair.h"

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
roy_mmap_delete(RoyMMap * mmap) {
  roy_mmap_clear(mmap);
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
  return roy_pair_value(roy_mset_cmin(mmap->root)->key);
}

const void *
roy_mmap_cmax(const RoyMMap * mmap) {
  return roy_pair_value(roy_mset_cmax(mmap->root)->key);
}

size_t
roy_mmap_size(const RoyMMap * mmap) {
  return roy_mset_size(mmap->root);
}

bool roy_mmap_empty(const RoyMMap * mmap) {
  return roy_mset_empty(mmap->root);
}

RoyMMap *
roy_mmap_insert(RoyMMap * mmap,
                void    * key,
                void    * value) {
  mmap->root =
    roy_mset_insert(&mmap->root, roy_pair_new(key, value), mmap->comparer);
  return mmap;
}

RoyMMap *
roy_mmap_remove(RoyMMap    * mmap,
                const void * key) {
  mmap->root = roy_mset_remove(&mmap->root, key, mmap->comparer, mmap->deleter);
  return mmap;
}

void
roy_mmap_clear(RoyMMap * mmap) {
  roy_mset_clear(mmap->root, mmap->deleter);
}

size_t
roy_mmap_count(const RoyMMap * mmap,
               void          * key) {
  RoyPair * pair = roy_pair_new(key, NULL);
  size_t ret = roy_mset_count(mmap->root, pair, (RCompare)mmap->comparer);
  free(pair);
  return ret;
}

void *
roy_mmap_find(RoyMMap * mmap,
              void    * key) {
  RoyPair * pair = roy_pair_new(key, NULL);
  RoyMSet * mset = roy_mset_find(mmap->root, pair, (RCompare)mmap->comparer);
  free(pair);
  return mset ? roy_pair_value(mset->key) : NULL;
}

void
roy_mmap_for_each(RoyMMap  * mmap,
                  ROperate   operate) {
  roy_mset_for_each(mmap->root, operate);
}

void
roy_mmap_for_which(RoyMMap    * mmap,
                   RCondition   condition,
                   ROperate     operate) {
  roy_mset_for_which(mmap->root, condition, operate);
}
