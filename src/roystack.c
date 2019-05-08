#include <string.h>
#include <stdlib.h>
#include "../include/roystack.h"

void swap_elements(void * data1, void * data2, size_t size);

RoyStack *
roy_stack_new(size_t capacity,
              size_t element_size) {
  RoyStack * ret = malloc(sizeof(void *) + sizeof(size_t) * 3);
  ret->data = calloc(capacity, element_size);
  ret->size = 0;
  ret->element_size = element_size;
  ret->capacity = capacity;
  return ret;
}

void
roy_stack_delete(RoyStack * stack) {
  free(stack->data);
  free(stack);
}

size_t
roy_stack_size(const RoyStack * stack) {
  return stack->size;
}

size_t
roy_stack_capacity(const RoyStack * stack) {
  return stack->capacity;
}

bool
roy_stack_empty(const RoyStack * stack) {
  return roy_stack_size(stack) == 0;
}

bool
roy_stack_full(const RoyStack * stack) {
  return roy_stack_size(stack) >= roy_stack_capacity(stack);
}

RoyStack *
roy_stack_push(RoyStack * stack, const void * data) {
  if (! roy_stack_full(stack)) {
    memcpy(stack->data + stack->element_size * stack->size++,
           data,
           stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_duplicate_top(RoyStack * stack) {
  return
  roy_stack_push(stack,
                 stack->data + stack->element_size * (stack->size - 1));
}



RoyStack *
roy_stack_swap_top_two(RoyStack * stack) {
  if (roy_stack_size(stack) >= 2) {
    swap_elements(stack->data + stack->element_size * (stack->size - 2),
         stack->data + stack->element_size * (stack->size - 1),
         stack->element_size);
  }
  return stack;
}

RoyStack *
roy_stack_pop(RoyStack * stack) {
  if (! roy_stack_empty(stack)) {
    stack->size--;
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

/* PRIVATE FUNCTIONS BELOW */

void
swap_elements(void * data1,
              void * data2,
              size_t size) {
  char temp[size];
  memcpy(temp,  data1, size);
  memcpy(data1, data2, size);
  memcpy(data2, temp,  size);
}