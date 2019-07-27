#include "../include/roymap.h"

RoyElement pair_new(const RoyElement key, size_t key_size, const RoyElement value, size_t value_size);

RoyMap
roy_map_new(size_t   key_size,
            size_t   value_size,
            RoyCompare comp) {
  RoyMap ret    = ROY_MAP(malloc(sizeof(struct _RoyMap)));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}

void
roy_map_delete(RoyMap map) {
  map = roy_map_clear(map);
  free(map);
}

RoyElement
roy_map_pmin(RoyMap map) {
  RoySet pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

RoyElement roy_map_pmax(RoyMap map) {
  RoySet pnode = roy_set_max(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

const RoyElement
roy_map_const_pmin(const RoyMap map) {
  const RoySet pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

const RoyElement
roy_map_const_pmax(const RoyMap map) {
  const RoySet pnode = roy_set_max(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

size_t
roy_map_size(const RoyMap map) {
  return roy_set_size(map->root);
}

bool roy_map_empty(const RoyMap map) {
  return roy_set_empty(map->root);
}

RoyMap
roy_map_insert(RoyMap map, const RoyElement key, const RoyElement value) {
  RoyElement pair = pair_new(key, map->key_size, value, map->value_size);
  map->root = roy_set_insert(&map->root,
                             pair,
                             map->key_size + map->value_size,
                             map->comp);
  free(pair);
  return map;
}

RoyMap
roy_map_erase(RoyMap map, const RoyElement key) {
  map->root = roy_set_erase(&map->root, key, map->key_size, map->comp);
  return map;
}

RoyMap
roy_map_clear(RoyMap map) {
  map->root = roy_set_clear(map->root);
  return map;
}

RoyElement
roy_map_find(RoyMap      map,
             const RoyElement key) {
  RoySet pnode = roy_set_find(map->root, key, map->comp);
  return pnode ? pnode->key + map->key_size : NULL;
}

void
roy_map_for_each(RoyMap map, RoyOperate operate) {
  roy_set_for_each(map->root, operate);
}

void
roy_map_for_which(RoyMap map,
                  RoyCondition condition,
                  RoyOperate operate) {
  roy_set_for_which(map->root, condition, operate);
}

// pair must be freed when it's done.
RoyElement
pair_new(const RoyElement key,
         size_t       key_size,
         const RoyElement value,
         size_t       value_size) {
  RoyElement pair = malloc(key_size + value_size);
  memcpy(pair, key, key_size);
  memcpy(pair + key_size, value, value_size);
  return pair;
}
