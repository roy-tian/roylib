#include "../include/roypointer.h"

RoyPointer
roy_pointer_set(RoyPointer pointer,
                RoyElement real_pointer) {
  pointer->pointer = real_pointer;
  return pointer;
}

const RoyElement
roy_pointer_get(const RoyPointer pointer) {
  return pointer ? pointer->pointer : NULL;
}