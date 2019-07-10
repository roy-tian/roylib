#include "../include/roypointer.h"

RoyPointer *
roy_pointer_set(RoyPointer * pointer,
                void       * real_pointer) {
  pointer->pointer = real_pointer;
  return pointer;
}

const void *
roy_pointer_get(const RoyPointer * pointer) {
  return pointer ? pointer->pointer : NULL;
}