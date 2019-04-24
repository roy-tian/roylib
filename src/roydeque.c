#include "../include/roydeque.h"
#include <stdlib.h>
#include <string.h>

RoyDeque *
roy_deque_new(size_t element_size) {
  RoyDeque * ret = malloc(sizeof(RoyList *) * 2 + sizeof(size_t) * 2);
  ret->head = roy_list_new();
  ret->tail = ret->head->next;
  ret->length = 0;
  ret->element_size = element_size;
  return ret;
}

void
roy_deque_delete(RoyDeque * deque) {
  roy_list_delete(deque->head);
  free(deque);
}

void *
roy_deque_pointer(RoyDeque * deque,
                 int         position) {
  if (position <= deque->length / 2) { // smaller half
    return roy_list_pointer(deque->head, position)->data;
  } else { // bigger half
    return
    roy_list_reverse_pointer(deque->tail, deque->length - position - 1)->data;
  }
}

void *
roy_deque_front(RoyDeque * deque) {
  return roy_list_front(deque->head)->data;
}

void *
roy_deque_back(RoyDeque * deque) {
  return roy_list_back(deque->tail)->data;
}

const void *
roy_deque_const_pointer(const RoyDeque * deque,
                        int              position) {
  if (position <= deque->length / 2) { // smaller half
    return roy_list_const_pointer(deque->head, position)->data;
  } else { // bigger half
    return
    roy_list_const_reverse_pointer(deque->tail,
                                   deque->length - position - 1)->data;
  }
}

const void *
roy_deque_const_front(const RoyDeque * deque) {
  return roy_list_const_front(deque->head)->data;
}

const void *
roy_deque_const_back(const RoyDeque * deque) {
  return roy_list_const_back(deque->tail)->data;
}

void *
roy_deque_element(void           * dest,
                  const RoyDeque * deque,
                  int              position) {
  memcpy(dest,
         roy_deque_const_pointer(deque, position),
         deque->element_size);
  return dest;   
}

size_t
roy_deque_length(const RoyDeque * deque) {
  return deque->length;
}

bool
roy_deque_empty(const RoyDeque * deque) {
  return roy_deque_length(deque) == 0;
}

RoyDeque *
roy_deque_insert(RoyDeque   * deque,
                 int          position,
                 const void * data) {
  if (position <= deque->length / 2) { // smaller half
    roy_list_pointer(deque->head, position)->data;
  } else { // bigger half
    return
    roy_list_reverse_pointer(deque->tail, deque->length - position - 1)->data;
  }
}

RoyDeque *
roy_deque_push_front(RoyDeque   * deque,
                     const void * data) {
  roy_list_push_front(deque->head, data, deque->element_size);
  return deque;
}

RoyDeque *
roy_deque_push_back(RoyDeque   * deque,
                    const void * data) {
  roy_list_push_back(deque->tail, data, deque->element_size);
  return deque;
}

RoyDeque *
roy_deque_erase(RoyDeque * deque,
                int        position) {
  return roy_deque_pop_front(roy_deque_pointer(deque, position - 1));
}

RoyDeque *
roy_deque_pop_front(RoyDeque * deque) {
  if (!roy_deque_empty(deque)) {
    RoyDeque * to_erase = roy_deque_front(deque);
    RoyDeque * next_elem = to_erase->next;
    deque->next = next_elem;
    next_elem->prev = deque;
    roy_deque_delete_node(to_erase);
  }
  return deque;
}

RoyDeque *
roy_deque_pop_back(RoyDeque * deque) {
  return roy_deque_pop_front(roy_deque_back(deque));
}

RoyDeque *
roy_deque_clear(RoyDeque * deque) {
  while (!roy_deque_empty(deque)) {
    roy_deque_pop_front(deque);
  }
  return deque;
}