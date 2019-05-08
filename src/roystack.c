#include <string.h>
#include <stdlib.h>
#include "../include/roystack.h"

RoyStack *
roy_stack_new(size_t capacity,
              size_t element_size) {
  RoyStack * ret = malloc(sizeof(void *) + sizeof(size_t) * 3);
  ret->data = calloc(capacity, element_size);
  ret->capacity = capacity;
  ret->element_size = element_size;
  ret->length = 0;
  return ret;
}

void
roy_stack_delete(RoyStack * stack) {
  free(stack->data);
  free(stack);
}

size_t
roy_stack_length(const RoyStack * stack) {
  return stack->length;
}

size_t
roy_stack_capacity(const RoyStack * stack) {
  return stack->capacity;
}

bool
roy_stack_empty(const RoyStack * stack) {
  return roy_stack_length(stack) == 0;
}

bool
roy_stack_full(const RoyStack * stack) {
  return roy_stack_length(stack) >= roy_stack_capacity(stack);
}

RoyStack *
roy_stack_push(RoyStack * stack, const void * data) {
  if (! roy_stack_full(stack)) {
    memcpy(stack->data + stack->element_size * stack->length++,
           data,
           stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_duplicate_top(RoyStack * stack) {
  return
  roy_stack_push(stack,
                 stack->data + stack->element_size * (stack->length - 1));
}

void swap(void * data1, void * data2, size_t size) {
  char temp[size];
  memcpy(temp,  data1, size);
  memcpy(data1, data2, size);
  memcpy(data2, temp,  size);
}

RoyStack *
roy_stack_swap_top_two(RoyStack * stack) {
  if (roy_stack_length(stack) >= 2) {
    swap(stack->data + stack->element_size * (stack->length - 2),
         stack->data + stack->element_size * (stack->length - 1),
         stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_pop(RoyStack * stack) {
  if (! roy_stack_empty(stack)) {
    memcpy(stack->data + stack->element_size * --stack->length,
           '\0',
           stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_clear(RoyStack * stack) {
  while (! roy_stack_empty(stack)) {
    roy_stack_pop(stack);
  }
  return stack;
}