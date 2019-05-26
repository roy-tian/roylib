#ifndef ROYMAP_H
#define ROYMAP_H

#include "royinit.h"

struct _RoyMap {
  void           * key;
  void           * value;
  struct _RoyMap * left;
  struct _RoyMap * right;
};

typedef struct _RoyMap RoyMap;

RoyMap * roy_map_new(void);

void roy_map_delete(RoyMap * map);

RoyMap * roy_map_insert_sort(RoyMap * map, const void * key, size_t key_size, const void * value, size_t value_size, int (* comp)(const void *, const void *));

#endif // ROYMAP_H
