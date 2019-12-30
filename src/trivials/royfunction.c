#include "royfunction.h"

RoyFunction *
roy_function_new(void * func_ptr) {
  RoyFunction * ret = (RoyFunction *)malloc(sizeof(RoyFunction));
  ret->func_ptr = func_ptr;
  return ret;
}

void
roy_function_delete(RoyFunction * function) {
  free(function);
}

void *
roy_function_get(RoyFunction * function) {
  return function ? function->func_ptr : NULL;
}
