#include "../include/roymap.h"

void * pair_new(const void * key, size_t key_size, const void * value, size_t value_size);

RoyMap *
roy_map_new(size_t   key_size,
            size_t   value_size,
            int   (* comp)(const void *, const void *)) {
  RoyMap * ret    = ROY_MAP(malloc(sizeof(RoyMap)));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}

void
roy_map_delete(RoyMap * map) {
  map = roy_map_clear(map);
  free(map);
}

void *
roy_map_pmin(RoyMap * map) {
  RoySet * pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

void * roy_map_pmax(RoyMap * map) {
  RoySet * pnode = roy_set_max(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

const void *
roy_map_const_pmin(const RoyMap * map) {
  const RoySet * pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

const void *
roy_map_const_pmax(const RoyMap * map) {
  const RoySet * pnode = roy_set_max(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

size_t
roy_map_size(const RoyMap * map) {
  return roy_set_size(map->root);
}

bool roy_map_empty(const RoyMap * map) {
  return roy_set_empty(map->root);
}

RoyMap *
roy_map_insert(RoyMap * map, const void * key, const void * value) {
  void * pair = pair_new(key, map->key_size, value, map->value_size);
  map->root = roy_set_insert(&map->root,
                             pair,
                             map->key_size + map->value_size,
                             map->comp);
  free(pair);
  return map;
}

RoyMap *
roy_map_erase(RoyMap * map, const void * key) {
  map->root = roy_set_erase(&map->root, key, map->key_size, map->comp);
  return map;
}

RoyMap *
roy_map_clear(RoyMap * map) {
  map->root = roy_set_clear(map->root);
  return map;
}

void *
roy_map_find(RoyMap     * map,
             const void * key) {
  RoySet * pnode = roy_set_find(map->root, key, map->comp);
  return pnode ? pnode->key + map->key_size : NULL;
}

void
roy_map_for_each(RoyMap * map, void(* operate)(void *)) {
  roy_set_for_each(map->root, operate);
}

void
roy_map_for_which(RoyMap * map,
                  bool  (* condition)(const void *),
                  void  (* operate)(void *)) {
  roy_set_for_which(map->root, condition, operate);
}

// pair must be freed when it's done.
void *
pair_new(const void * key,
         size_t       key_size,
         const void * value,
         size_t       value_size) {
  void * pair = malloc(key_size + value_size);
  memcpy(pair, key, key_size);
  memcpy(pair + key_size, value, value_size);
  return pair;
}
