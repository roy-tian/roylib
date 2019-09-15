#include "roydeque.h"

RoyDeque *
roy_deque_new(size_t element_size) {
  RoyDeque * ret    = (RoyDeque *)malloc(sizeof(RoyDeque));
  assert(ret != NULL);
  ret->head         = roy_list_new();
  ret->tail         = ret->head->next;
  ret->size         = 0;
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
                  size_t     position) {
  assert(deque != NULL);
  assert(position < roy_deque_size(deque));
  RoyList * pnode;
  if (position <= deque->size / 2) { // smaller half
    pnode = roy_list_iterator(deque->head, position);
  } else { // bigger half
    pnode = roy_list_reverse_iterator(deque->tail,
                                      roy_deque_size(deque) - position - 1);
  }
  return pnode->data;
}

const void *
roy_deque_const_pointer(const RoyDeque * deque,
                        size_t           position) {
  assert(deque != NULL);
  assert(position < roy_deque_size(deque));
  const RoyList * pnode;
  if (position <= deque->size / 2) { // smaller half
    pnode = roy_list_const_iterator(deque->head, position);
  } else { // bigger half
    pnode = roy_list_const_reverse_iterator(deque->tail,
                                            deque->size - position - 1);
  }
  return pnode ? pnode->data : NULL;
}

void *
roy_deque_front(RoyDeque * deque) {
  assert(deque != NULL);
  RoyList * pnode = roy_list_begin(deque->head);
  return pnode ? pnode->data : NULL;
}

const void *
roy_deque_const_front(const RoyDeque * deque) {
  assert(deque != NULL);
  const RoyList * pnode = roy_list_cbegin(deque->head);
  return pnode ? pnode->data : NULL;
}

void *
roy_deque_back(RoyDeque * deque) {
  assert(deque != NULL);
  RoyList * pnode = roy_list_rbegin(deque->tail);
  return pnode ? pnode->data : NULL;
}

const void *
roy_deque_const_back(const RoyDeque * deque) {
  assert(deque != NULL);
  const RoyList * pnode = roy_list_crbegin(deque->tail);
  return pnode ? pnode->data : NULL;
}

void *
roy_deque_element(void           * dest,
                  const RoyDeque * deque,
                  size_t           position) {
  assert(dest != NULL);
  assert(deque != NULL);
  assert(position < roy_deque_size(deque));
  memcpy(dest,
         roy_deque_const_pointer(deque, position),
         deque->element_size);
  return dest;   
}

size_t
roy_deque_size(const RoyDeque * deque) {
  assert(deque != NULL);
  return deque->size;
}

bool
roy_deque_empty(const RoyDeque * deque) {
  assert(deque != NULL);
  return roy_deque_size(deque) == 0;
}

RoyDeque *
roy_deque_insert(RoyDeque   * deque,
                 size_t       position,
                 const void * data) {
  assert(deque != NULL);
  assert(position < roy_deque_size(deque));
  assert(data != NULL);
  if (position <= deque->size / 2) { // smaller half
    roy_list_insert(deque->head, position, data, deque->element_size);
  } else { // bigger half
    roy_list_insert_reverse(deque->tail,
                            deque->size - position - 1,
                            data,
                            deque->element_size);
  }
  return deque;
}

RoyDeque *
roy_deque_push_front(RoyDeque   * deque,
                     const void * data) {
  assert(deque != NULL);
  assert(data != NULL);
  roy_list_push_front(deque->head, data, deque->element_size);
  deque->size++;
  return deque;
}

RoyDeque *
roy_deque_push_back(RoyDeque   * deque,
                    const void * data) {
  assert(deque != NULL);
  assert(data != NULL);
  roy_list_push_back(deque->tail, data, deque->element_size);
  deque->size++;
  return deque;
}

RoyDeque *
roy_deque_erase(RoyDeque * deque,
                size_t     position) {
  assert(deque != NULL);
  assert(position < roy_deque_size(deque));
  if (position <= deque->size / 2) { // smaller half
    roy_list_erase(deque->head, position);
  } else { // bigger half
    roy_list_erase_reverse(deque->tail,
                           deque->size - position - 1);
  }
  return deque;
}

RoyDeque *
roy_deque_pop_front(RoyDeque * deque) {
  assert(deque != NULL);
  if (!roy_list_empty(deque->head)) {
    roy_list_pop_front(deque->head);
    deque->size--;
  }
  return deque;
}

RoyDeque *
roy_deque_pop_back(RoyDeque * deque) {
  assert(deque != NULL);
  if (deque->tail->prev) { // not empty
    roy_list_pop_back(deque->tail);
    deque->size--;
  }
  return deque;
}

RoyDeque *
roy_deque_clear(RoyDeque * deque) {
  assert(deque != NULL);
  while (!roy_deque_empty(deque)) {
    roy_deque_pop_front(deque);
  }
  return deque;
}

void
roy_deque_for_each(RoyDeque * deque,
                   void    (* operate)(void *)) {
  assert(deque != NULL);
  assert(operate != NULL);
  roy_list_for_each(deque->head, operate);
}

void
roy_deque_for_which(RoyDeque * deque,
                    bool    (* condition)(const void *),
                    void    (* operate)(void *)) {
  assert(deque != NULL);
  assert(condition != NULL);
  assert(operate != NULL);
  roy_list_for_which(deque->head, condition, operate);
}