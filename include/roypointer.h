#include "royinit.h"

struct RoyPointer_ {
  RData pointer;
};

// RoyPointer: encapsulates any kinds of pointers in order to transfer the underlying objects.
// useful for transporting functions pointers.
typedef struct RoyPointer_ RoyPointer;

RoyPointer * roy_pointer_set(RoyPointer * pointer, RData real_pointer);
RCData roy_pointer_get(const RoyPointer * pointer);
