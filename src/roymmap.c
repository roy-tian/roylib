#include "../include/roymmap.h"

static void * pair_new(const void * key, size_t key_size, const void * value, size_t value_size);

RoyMMap *
roy_mmap_new(size_t   key_size,
             size_t   value_size,
             int   (* comp)(const void *, const void *)) {
  RoyMMap * ret   = ROY_MMAP(malloc(sizeof(RoyMMap)));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}

void
roy_mmap_delete(RoyMMap * mmap) {
  mmap = roy_mmap_clear(mmap);
  free(mmap);
}

void *
roy_mmap_pmin(RoyMMap * mmap) {
  return roy_mset_min(mmap->root)->key + mmap->key_size;
}

void * roy_mmap_pmax(RoyMMap * mmap) {
  return roy_mset_max(mmap->root)->key + mmap->key_size;
}

const void *
roy_mmap_const_pmin(const RoyMMap * mmap) {
  return roy_mset_min(mmap->root)->key + mmap->key_size;
}

const void *
roy_mmap_const_pmax(const RoyMMap * mmap) {
  return roy_mset_max(mmap->root)->key + mmap->key_size;
}

size_t
roy_mmap_size(const RoyMMap * mmap) {
  return roy_mset_size(mmap->root);
}

bool roy_mmap_empty(const RoyMMap * mmap) {
  return roy_mset_empty(mmap->root);
}

RoyMMap *
roy_mmap_insert(RoyMMap * mmap, const void * key, const void * value) {
  void * pair = pair_new(key, mmap->key_size, value, mmap->value_size);
  mmap->root = roy_mset_insert(&mmap->root,
                             pair,
                             mmap->key_size + mmap->value_size,
                             mmap->comp);
  free(pair);
  return mmap;
}

RoyMMap *
roy_mmap_erase(RoyMMap * mmap, const void * key) {
  mmap->root = roy_mset_erase(&mmap->root, key, mmap->key_size, mmap->comp);
  return mmap;
}

RoyMMap * roy_mmap_clear(RoyMMap * mmap) {
  mmap->root = roy_mset_clear(mmap->root);
  return mmap;
}

void
roy_mmap_for_each(RoyMMap * mmap, void(* operate)(void *)) {
  roy_mset_for_each(mmap->root, operate);
}

void
roy_mmap_for_which(RoyMMap * mmap,
                  bool  (* condition)(const void *),
                  void  (* operate)(void *)) {
  roy_mset_for_which(mmap->root, condition, operate);
}

// pair must be freed when it's done.
static void *
pair_new(const void * key,
         size_t       key_size,
         const void * value,
         size_t       value_size) {
  void * pair = malloc(key_size + value_size);
  memcpy(pair, key, key_size);
  memcpy(pair + key_size, value, value_size);
  return pair;
}

