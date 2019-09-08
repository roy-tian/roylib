#include "roystack.h"

static void swap_elements(void * data1, void * data2, size_t size);

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

RoyStack *
roy_stack_push(RoyStack   * stack,
               const void * data) {
  return (RoyStack *)roy_array_push_back((RoyArray *)stack, data);
}

RoyStack *
roy_stack_duplicate_top(RoyStack * stack) {
  return roy_stack_push(stack,
                        roy_array_const_pointer((RoyArray *)stack,
                                                roy_stack_size(stack) - 1));
}

RoyStack *
roy_stack_swap_top_two(RoyStack * stack) {
  size_t size = roy_stack_size(stack);
  if (size >= 2) {
    swap_elements(roy_array_pointer((RoyArray *)stack, size - 2),
                  roy_array_pointer((RoyArray *)stack, size - 1),
                  stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_pop(RoyStack * stack) {
  return (RoyStack *)roy_array_pop_back((RoyArray *)stack);
}

RoyStack *
roy_stack_clear(RoyStack * stack) {
  return (RoyStack *)roy_array_clear((RoyArray *)stack);
}

/* PRIVATE FUNCTIONS BELOW */

static void
swap_elements(void   * data1,
              void   * data2,
              size_t   size) {
  char temp[size];
  memcpy(temp,  data1, size);
  memcpy(data1, data2, size);
  memcpy(data2, temp,  size);
}