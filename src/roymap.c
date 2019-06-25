#include "../include/roymap.h"


RoyMap *
roy_map_new(size_t   key_size,
            size_t   value_size,
            int   (* comp)(const void *, const void *)) {
  RoyMap * ret    = malloc(sizeof(RoyMap));
  ret->root       = NULL;
  ret->key_size   = key_size;
  ret->value_size = value_size;
  ret->comp       = comp;
  return ret;
}

// Deallocates all the memory allocated.
// (Always call this function after the work is done by the given 'map', or memory leak will occur.)
void roy_map_delete(RoyMap * map);
