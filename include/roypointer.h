#include "royinit.h"

struct RoyPointer_ {
  void * pointer;
};

// RoyPointer: encapsulates any kinds of pointers in order to transfer the underlaying objects.
// useful for transporting functions pointers.
typedef struct RoyPointer_ RoyPointer;

RoyPointer * roy_pointer_set(RoyPointer * pointer, void * real_pointer);
const void * roy_pointer_get(const RoyPointer * pointer);
