#include "../include/roymap.h"

struct _RoyMapNode {
  void               * key;
  void               * value;
  struct _RoyMapNode * left;
  struct _RoyMapNode * right;
};

typedef struct _RoyMapNode Node;

static Node * node_new(size_t key_size, size_t value_size);
static Node * node_set_key(Node * node, const void * key, size_t key_size);
static Node * node_set_value(Node * node, const void * value, size_t value_size);

RoyMap *
roy_map_new(size_t    key_size,
            size_t    value_size,
            int    (* comp) (const void *, const void *)) {
  RoyMap * ret;
  ret->root       = malloc(sizeof(Node));
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}


void
roy_map_delete(RoyMap * map) {

}

RoyMap *
roy_map_insert_sort(RoyMap     * map,
                    const void * key,
                    const void * value) {
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

/* PRIVATE FUNCTIONS BELOW */

static Node *
node_new(size_t key_size,
         size_t value_size) {
  Node * ret = malloc(sizeof(Node));
  ret->key   = malloc(key_size);
  ret->value = malloc(value_size);
  ret->left  = NULL;
  ret->right = NULL;
  return ret;
}

static Node *
node_set_key(Node       * node,
             const void * key,
             size_t       key_size) {

}
static Node * node_set_value(Node * node, const void * value, size_t value_size);