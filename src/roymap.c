#include "roymap.h"
#include "trivials/roypair.h"

RoyMap *
roy_map_new(RCompare comparer,
            ROperate deleter) {
  RoyMap * ret = (RoyMap *)malloc(sizeof(RoyMap));
  ret->root    = NULL;
  ret->comparer = comparer;
  ret->deleter = deleter;
  return ret;
}

void
roy_map_delete(RoyMap * map) {
  roy_map_clear(map);
  free(map);
  map = NULL;
}

void *
roy_map_min(RoyMap * map) {
  RoySet * pnode = roy_set_min(map->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

void * roy_map_max(RoyMap * map) {
  RoySet * pnode = roy_set_max(map->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

const void *
roy_map_cmin(const RoyMap * map) {
  const RoySet * pnode = roy_set_min(map->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

const void *
roy_map_cmax(const RoyMap * map) {
  const RoySet * pnode = roy_set_max(map->root);
  return pnode ? roy_pair_value(pnode->key) : NULL;
}

size_t
roy_map_size(const RoyMap * map) {
  return roy_set_size(map->root);
}

bool roy_map_empty(const RoyMap * map) {
  return roy_set_empty(map->root);
}

RoyMap *
roy_map_insert(RoyMap * map,
               void   * key,
               void   * value) {
  map->root = roy_set_insert(&map->root,
                             roy_pair_new(key, value),
                             map->comparer);
  return map;
}

RoyMap *
roy_map_erase(RoyMap     * map,
              const void * key) {
  map->root = roy_set_erase(&map->root, key, map->comparer, map->deleter);
  return map;
}

void
roy_map_clear(RoyMap * map) {
  roy_set_clear(map->root, map->deleter);
}

void *
roy_map_find(RoyMap     * map,
             const void * key) {
  RoySet * pnode = roy_set_find(map->root, key, map->comparer);
  return pnode ? roy_pair_value(pnode->key) : NULL;
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
