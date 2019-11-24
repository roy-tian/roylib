#include "roymmap.h"
#include "trivials/roypair.h"

RoyMMap *
roy_mmap_new(RCompare compare,
             ROperate deleter) {
  RoyMMap * ret = (RoyMMap *)malloc(sizeof(RoyMMap));
  ret->root     = NULL;
  ret->compare  = compare;
  ret->deleter  = deleter;
  return ret;
}

void
roy_mmap_delete(RoyMMap * mmap) {
  roy_mmap_clear(mmap);
  free(mmap);
  mmap = NULL;
}

void *
roy_mmap_min(RoyMMap * mmap) {
  RoyMSet * pnode = roy_mset_min(mmap->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

void * roy_mmap_max(RoyMMap * mmap) {
  RoyMSet * pnode = roy_mset_max(mmap->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

const void *
roy_mmap_cmin(const RoyMMap * mmap) {
  const RoyMSet * pnode = roy_mset_min(mmap->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

const void *
roy_mmap_cmax(const RoyMMap * mmap) {
  const RoyMSet * pnode = roy_mset_max(mmap->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
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
  mmap->root = roy_mset_insert(&mmap->root,
                               roy_pair_new(key, value),
                               mmap->compare);
  return mmap;
}

RoyMMap *
roy_mmap_erase(RoyMMap    * mmap,
               const void * key) {
  mmap->root = roy_mset_erase(&mmap->root, key, mmap->compare, mmap->deleter);
  return mmap;
}

void
roy_mmap_clear(RoyMMap * mmap) {
  roy_mset_clear(mmap->root, mmap->deleter);
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
