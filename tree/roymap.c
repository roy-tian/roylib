#include "roymap.h"
#include "../util/roypair.h"

RoyMap *
roy_map_new(RCompare comparer,
            ROperate deleter) {
  RoyMap * ret  = malloc(sizeof(RoyMap));
  ret->root     = roy_set_new();
  ret->comparer = comparer;
  ret->deleter  = deleter;
  return ret;
}

void
roy_map_delete(RoyMap * map,
               void   * user_data) {
  roy_map_clear(map, user_data);
  free(map);
}

void *
roy_map_min(RoyMap * map) {
  return roy_pair_value(roy_set_min(map->root)->key);
}

void * roy_map_max(RoyMap * map) {
  return roy_pair_value(roy_set_max(map->root)->key);
}

const void *
roy_map_cmin(const RoyMap * map) {
  return roy_cpair_value(roy_set_cmin(map->root)->key);
}

const void *
roy_map_cmax(const RoyMap * map) {
  return roy_cpair_value(roy_set_cmax(map->root)->key);
}

size_t
roy_map_size(const RoyMap * map) {
  return roy_set_size(map->root);
}

bool roy_map_empty(const RoyMap * map) {
  return roy_set_empty(map->root);
}

RoyMap *
roy_map_insert(RoyMap * restrict map,
               void   * restrict key,
               void   * restrict value) {
  map->root = 
    roy_set_insert(&map->root, roy_pair_new(key, value), map->comparer);
  return map;
}

RoyMap *
roy_map_remove(RoyMap     * map,
               const void * key) {
  map->root = roy_set_remove(&map->root, key, map->comparer, map->deleter, NULL);
  return map;
}

void
roy_map_clear(RoyMap * map,
              void   * user_data) {
  roy_set_clear(map->root, map->deleter, user_data);
}

void *
roy_map_find(RoyMap     * map,
             const void * key) {
  RoyCPair * pair = roy_cpair_new(key, NULL);
  RoySet * set = roy_set_find(map->root, pair, map->comparer);
  free(pair);
  return set ? roy_pair_value(set->key) : NULL;
}

void
roy_map_for_each(RoyMap   * map,
                 ROperate   operate,
                 void     * user_data) {
  roy_set_for_each(map->root, operate, user_data);
}

void
roy_map_for_which(RoyMap     * map,
                  RCondition   condition,
                  ROperate     operate,
                  void       * user_data) {
  roy_set_for_which(map->root, condition, operate, user_data);
}
