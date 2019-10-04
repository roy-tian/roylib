#include "../include/roystack.h"

RoyStack *
roy_stack_new(size_t capacity,
              size_t element_size) {
  return (RoyStack *)roy_array_new(capacity, element_size);
}

void
roy_stack_delete(RoyStack * stack) {
  roy_array_delete((RoyArray *)stack);
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
roy_stack_push(RoyStack   * stack,
               const void * data) {
  return roy_array_push_back((RoyArray *)stack, data);
}

bool
roy_stack_duplicate_top(RoyStack * stack) {
  return
  roy_stack_push(stack, roy_array_cpointer((RoyArray *) stack,
                                           roy_stack_size(stack) - 1));
}

bool
roy_stack_pop(RoyStack * stack) {
  return roy_array_pop_back((RoyArray *)stack);
}

void
roy_stack_clear(RoyStack * stack) {
  roy_array_clear((RoyArray *)stack);
}
