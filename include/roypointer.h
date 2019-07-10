#include "royinit.h"

struct _RoyPointer {
  void * pointer;
};

// RoyPointer: encapsulates any kinds of pointers in order to transfer the underlaying objects.
typedef struct _RoyPointer RoyPointer;

RoyPointer * roy_pointer_set(RoyPointer * pointer, void * real_pointer);
const void * roy_pointer_get(const RoyPointer * pointer);
