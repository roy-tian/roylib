#include "royobject.h"

RoyObject *
roy_object_set(RoyObject * object,
               void      * data) {
  object->data = data;
  return object;
}

const void *
roy_object_cget(const RoyObject * object) {
  return object ? object->data : NULL;
}

void *
roy_object_get(RoyObject * object) {
  return object ? object->data : NULL;
}

RoyObject *
roy_object_copy(RoyObject       * dest,
                const RoyObject * src,
                size_t            src_size) {
  memcpy(dest->data, src->data, src_size);
  return dest;
}

RoyObject *
roy_object_move(RoyObject * dest,
                RoyObject * src,
                size_t      src_size,
                ROperate    deleter) {
  roy_object_copy(dest, src, src_size);
  deleter(src->data);
  return dest;
}
