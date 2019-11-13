#include "../include/roymap.h"

RData pair_new(RCData key, size_t key_size, RCData value, size_t value_size);

RoyMap *
roy_map_new(size_t   key_size,
            size_t   value_size,
            RCompare compare) {
  RoyMap * ret    = (RoyMap *)malloc(sizeof(RoyMap));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->compare    = compare;
  return ret;
}

void
roy_map_delete(RoyMap * map) {
  roy_map_clear(map);
  free(map);
  map = NULL;
}

RData
roy_map_min(RoyMap * map) {
  RoySet * pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

RData roy_map_max(RoyMap * map) {
  RoySet * pnode = roy_set_max(map->root);
  return pnode ? pnode->key + map->key_size : NULL;
}

RCData
roy_map_cmin(const RoyMap * map) {
  const RoySet * pnode = roy_set_min(map->root);
  return pnode ? pnode->key + map->key_size: NULL;
}

RCData
roy_map_cmax(const RoyMap * map) {
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
roy_map_insert(RoyMap     * map,
               RCData key,
               RCData value) {
  RData pair = pair_new(key, map->key_size, value, map->value_size);
  map->root = roy_set_insert(&map->root,
                             pair,
                             map->key_size + map->value_size,
                             map->compare);
  free(pair);
  return map;
}

RoyMap *
roy_map_erase(RoyMap     * map,
              RCData key) {
  map->root = roy_set_erase(&map->root, key, map->key_size, map->compare);
  return map;
}

void
roy_map_clear(RoyMap * map) {
  roy_set_clear(map->root);
}

RData
roy_map_find(RoyMap     * map,
             RCData key) {
  RoySet * pnode = roy_set_find(map->root, key, map->compare);
  return pnode ? pnode->key + map->key_size : NULL;
}

void
roy_map_for_each(RoyMap   * map,
                 ROperate   operate) {
  roy_set_for_each(map->root, operate);
}

void
roy_map_for_which(RoyMap     * map,
                  RCondition   condition,
                  ROperate     operate) {
  roy_set_for_which(map->root, condition, operate);
}

// pair must be freed when it's done.
RData
pair_new(RCData key,
         size_t       key_size,
         RCData value,
         size_t       value_size) {
  RData pair = malloc(key_size + value_size);
  memcpy(pair, key, key_size);
  memcpy(pair + key_size, value, value_size);
  return pair;
}
