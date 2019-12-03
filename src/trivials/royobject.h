#ifndef ROYOBJECT_H
#define ROYOBJECT_H

#include "royinit.h"

struct RoyObject_ {
  void * data;
};

// RoyObject: encapsulates any kinds of pointers in order to transfer the underlying objects.
typedef struct RoyObject_ RoyObject;

RoyObject * roy_object_set(RoyObject * object, void * data);

const void * roy_object_cget(const RoyObject * object);

void * roy_object_get(RoyObject * object);

RoyObject * roy_object_copy(RoyObject * dest, const RoyObject * src, size_t src_size);

RoyObject * roy_object_move(RoyObject * dest, RoyObject * src, size_t src_size, ROperate deleter);

#endif // ROYOBJECT_H