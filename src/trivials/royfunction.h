#ifndef ROYOBJECT_H
#define ROYOBJECT_H

#include "royinit.h"

struct RoyFunction_ {
  void * func_ptr;
};

/// @brief RoyFunction: encapsulates any kinds of pointers in order to transfer the underlying objects.
typedef struct RoyFunction_ RoyFunction;

RoyFunction * roy_function_new(void * func_ptr);

void roy_function_delete(RoyFunction * function);

void * roy_function_get(RoyFunction * function);

#endif // ROYOBJECT_H