#include "royinit.h"

struct _RoyPointer {
  RoyElement pointer;
};

// RoyPointer: encapsulates any kinds of pointers in order to transfer the underlaying objects.
typedef struct _RoyPointer * RoyPointer;

RoyPointer roy_pointer_set(RoyPointer pointer, RoyElement real_pointer);
const RoyElement roy_pointer_get(const RoyPointer pointer);
