#include "../include/roymap.h"

RoyMap *
roy_map_new(void) {
  RoyMap * ret = malloc(sizeof(RoyMap));
  ret->key   = NULL;
  ret->value = NULL;
  ret->left  = NULL;
  ret->right = NULL;
  return ret;
}

void
roy_map_delete(RoyMap * map) {

}

RoyMap *
roy_map_insert_sort(RoyMap     * map,
                    const void * key,
                    size_t       key_size,
                    const void * value,
                    size_t       value_size,
                    int       (* comp)(const void *, const void *)) {
  if (map->key == NULL) {
    map->key = malloc(key_size);
    memcpy(map->key, key, key_size);
    map->value = malloc(value_size);
    memcpy(map->value, value, value_size);
  } else switch (comp(map->key, key)) {
  case 0:
    map->value = malloc(value_size);
    memcpy(map->value, value, value_size);
    break;
  case 1:
    map->left =
      roy_map_insert_sort(map->left, key, key_size, value, value_size, comp);
    break;
  case -1:
    map->right =
      roy_map_insert_sort(map->right, key, key_size, value, value_size, comp);
    break;
  default:
    break;
  }
  return map;
}