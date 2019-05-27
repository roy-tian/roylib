#ifndef ROYMAP_H
#define ROYMAP_H

#include "royinit.h"

struct _RoyMapNode { };

struct _RoyMap {
  struct _RoyMapNode * root;
  size_t               key_size;
  size_t               value_size;
  int               (* comp) (const void *, const void *);
};

typedef struct _RoyMap RoyMap;

RoyMap * roy_map_new(size_t key_size, size_t value_size, int (* comp)(const void *, const void *));

void roy_map_delete(RoyMap * map);

RoyMap * roy_map_insert_sort(RoyMap * map, const void * key, const void * value);

#endif // ROYMAP_H
