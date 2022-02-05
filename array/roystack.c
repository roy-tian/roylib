#include "roystack.h"
#include "royarray.h"

struct RoyStack_ {
  void   ** data;
  RDoer     deleter;
  size_t    capacity;
  size_t    size;
};

RoyStack *
roy_stack_new(size_t capacity, RDoer deleter) {
  return (RoyStack *)roy_array_new(capacity, deleter);
}

void
roy_stack_delete(RoyStack * stack,
                 void     * user_data) {
  roy_array_delete((RoyArray *)stack, user_data);
}

size_t
roy_stack_size(const RoyStack * stack) {
  return roy_array_size((RoyArray *)stack);
}

size_t
roy_stack_capacity(const RoyStack * stack) {
  return roy_array_capacity((RoyArray *)stack);
}

bool
roy_stack_empty(const RoyStack * stack) {
  return roy_array_empty((RoyArray *)stack);
}

bool
roy_stack_full(const RoyStack * stack) {
  return roy_array_full((RoyArray *)stack);
}

bool
roy_stack_push(RoyStack * restrict stack,
               void     * restrict data) {
  return roy_array_push_back((RoyArray *)stack, data);
}

bool
roy_stack_pop(RoyStack * stack) {
  return roy_array_pop_back((RoyArray *)stack);
}

void
roy_stack_clear(RoyStack * stack) {
  roy_array_clear((RoyArray *)stack);
}
