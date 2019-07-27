#include "../include/roymmap.h"

static RoyElement pair_new(const RoyElement key, size_t key_size, const RoyElement value, size_t value_size);

RoyMMap
roy_mmap_new(size_t   key_size,
             size_t   value_size,
             RoyCompare   comp) {
  RoyMMap ret   = ROY_MMAP(malloc(sizeof(struct _RoyMMap)));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}

void
roy_mmap_delete(RoyMMap mmap) {
  mmap = roy_mmap_clear(mmap);
  free(mmap);
}

RoyElement
roy_mmap_pmin(RoyMMap mmap) {
  return roy_mset_min(mmap->root)->key + mmap->key_size;
}

RoyElement roy_mmap_pmax(RoyMMap mmap) {
  return roy_mset_max(mmap->root)->key + mmap->key_size;
}

const RoyElement
roy_mmap_const_pmin(const RoyMMap mmap) {
  return roy_mset_min(mmap->root)->key + mmap->key_size;
}

const RoyElement
roy_mmap_const_pmax(const RoyMMap mmap) {
  return roy_mset_max(mmap->root)->key + mmap->key_size;
}

size_t
roy_mmap_size(const RoyMMap mmap) {
  return roy_mset_size(mmap->root);
}

bool roy_mmap_empty(const RoyMMap mmap) {
  return roy_mset_empty(mmap->root);
}

RoyMMap
roy_mmap_insert(RoyMMap mmap, const RoyElement key, const RoyElement value) {
  RoyElement pair = pair_new(key, mmap->key_size, value, mmap->value_size);
  mmap->root = roy_mset_insert(&mmap->root,
                             pair,
                             mmap->key_size + mmap->value_size,
                             mmap->comp);
  free(pair);
  return mmap;
}

RoyMMap
roy_mmap_erase(RoyMMap mmap, const RoyElement key) {
  mmap->root = roy_mset_erase(&mmap->root, key, mmap->key_size, mmap->comp);
  return mmap;
}

RoyMMap roy_mmap_clear(RoyMMap mmap) {
  mmap->root = roy_mset_clear(mmap->root);
  return mmap;
}

void
roy_mmap_for_each(RoyMMap mmap, RoyOperate operate) {
  roy_mset_for_each(mmap->root, operate);
}

void
roy_mmap_for_which(RoyMMap mmap,
                  RoyCondition condition,
                  RoyOperate operate) {
  roy_mset_for_which(mmap->root, condition, operate);
}

// pair must be freed when it's done.
static RoyElement
pair_new(const RoyElement key,
         size_t       key_size,
         const RoyElement value,
         size_t       value_size) {
  RoyElement pair = malloc(key_size + value_size);
  memcpy(pair, key, key_size);
  memcpy(pair + key_size, value, value_size);
  return pair;
}

