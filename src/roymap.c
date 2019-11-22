#include "../include/roymap.h"

typedef struct Pair_ {
  void * key;
  void * value;
} Pair;

static Pair * pair_new(void * key, void * value);
static void * pair_value(Pair * pair);

RoyMap *
roy_map_new(RCompare compare,
            ROperate deleter) {
  RoyMap * ret = (RoyMap *)malloc(sizeof(RoyMap));
  ret->root    = NULL;
  ret->compare = compare;
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
  return pnode ? (*(Pair *)pnode->key).value : NULL;
}

void * roy_map_max(RoyMap * map) {
  RoySet * pnode = roy_set_max(map->root);
  return pnode ? (*(Pair *)pnode->key).value : NULL;
}

const void *
roy_map_cmin(const RoyMap * map) {
  const RoySet * pnode = roy_set_min(map->root);
  return pnode ? (*(Pair *)pnode->key).value : NULL;
}

const void *
roy_map_cmax(const RoyMap * map) {
  const RoySet * pnode = roy_set_max(map->root);
  return pnode ? (*(Pair *)pnode->key).value : NULL;
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
  Pair * pair = pair_new(key, value);
  map->root = roy_set_insert(&map->root, pair, map->compare);
  return map;
}

RoyMap *
roy_map_erase(RoyMap     * map,
              const void * key) {
  map->root = roy_set_erase(&map->root, key, map->compare, map->deleter);
  return map;
}

void
roy_map_clear(RoyMap * map) {
  roy_set_clear(map->root, map->deleter);
}

void *
roy_map_find(RoyMap     * map,
             const void * key) {
  RoySet * pnode = roy_set_find(map->root, key, map->compare);
  return pnode ? (*(Pair *)pnode->key).value : NULL;
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

/* PRIVATE FUNCTIONS DOWN HERE */

static Pair *
pair_new(void * key,
         void * value) {
  Pair * ret = (Pair *)malloc(sizeof(Pair));
  ret->key   = key;
  ret->value = value;
  return ret;
}

static void *
pair_value(Pair * pair) {
  return pair->value;
}