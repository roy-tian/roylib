#include "roydeque.h"

RoyDeque *
roy_deque_new(ROperate deleter) {
  RoyDeque * ret = malloc(sizeof(RoyDeque));
  ret->head      = roy_list_new();
  ret->tail      = ret->head->next;
  ret->deleter   = deleter;
  ret->size      = 0;
  return ret;
}

void
roy_deque_delete(RoyDeque * deque) {
  roy_list_delete(deque->head, deque->deleter);
  free(deque);
}

void *
roy_deque_pointer(RoyDeque * deque,
                  size_t     position) {
  RoyList * pnode =
    (position <= deque->size / 2)            ?
    roy_list_iterator(deque->head, position) :
    roy_list_riterator(deque->tail, roy_deque_size(deque) - position - 1);
  return pnode ? pnode->data : NULL;
}

const void *
roy_deque_cpointer(const RoyDeque * deque,
                   size_t           position) {
  const RoyList * pnode =
    (position <= deque->size / 2)            ?
    roy_list_iterator(deque->head, position) :
    roy_list_riterator(deque->tail, roy_deque_size(deque) - position - 1);
  return pnode ? pnode->data : NULL;
}

void *
roy_deque_front(RoyDeque * deque) {
  RoyList * pnode = roy_list_begin(deque->head);
  return pnode ? pnode->data : NULL;
}

const void *
roy_deque_cfront(const RoyDeque * deque) {
  const RoyList * pnode = roy_list_cbegin(deque->head);
  return pnode ? pnode->data : NULL;
}

void *
roy_deque_back(RoyDeque * deque) {
  RoyList * pnode = roy_list_rbegin(deque->tail);
  return pnode ? pnode->data : NULL;
}

const void *
roy_deque_cback(const RoyDeque * deque) {
  const RoyList * pnode = roy_list_crbegin(deque->tail);
  return pnode ? pnode->data : NULL;
}

size_t
roy_deque_size(const RoyDeque * deque) {
  return deque->size;
}

bool
roy_deque_empty(const RoyDeque * deque) {
  return roy_deque_size(deque) == 0;
}

bool
roy_deque_insert(RoyDeque   * restrict deque,
                 size_t                position,
                 void       * restrict data) {
  return (position <= deque->size / 2)                      ?
         roy_list_insert(deque->head, position, data)       :
         roy_list_insert_reverse(deque->tail, deque->size - position - 1, data);
}

void
roy_deque_push_front(RoyDeque   * restrict deque,
                     void       * restrict data) {
  roy_list_push_front(deque->head, data);
  deque->size++;
}

void
roy_deque_push_back(RoyDeque   * restrict deque,
                    void       * restrict data) {
  roy_list_push_back(deque->tail, data);
  deque->size++;
}

bool
roy_deque_erase(RoyDeque * deque,
                size_t     position) {
  return (position <= deque->size / 2)         ?
         roy_list_erase(deque->head, position, deque->deleter) :
         roy_list_erase_reverse(deque->tail,
                                deque->size - position - 1,
                                deque->deleter);
}

bool
roy_deque_pop_front(RoyDeque * deque) {
  if (roy_list_pop_front(deque->head, deque->deleter)) {
    deque->size--;
    return true;
  }
  return false;
}

bool
roy_deque_pop_back(RoyDeque * deque) {
  if (roy_list_pop_back(deque->tail, deque->deleter)) {
    deque->size--;
    return true;
  }
  return false;
}

void
roy_deque_clear(RoyDeque * deque) {
  while (!roy_deque_empty(deque)) {
    roy_deque_pop_front(deque);
  }
}

size_t
roy_deque_remove(RoyDeque   * deque,
                 const void * data,
                 RCompare     comparer) {
  return roy_list_remove(deque->head, data, comparer, deque->deleter);
}

size_t roy_deque_remove_if(RoyDeque   * deque,
                           RCondition   condition) {
  return roy_list_remove_if(deque->head, condition, deque->deleter);
}

void
roy_deque_reverse(RoyDeque * deque) {
  RoyList * phead = deque->head;
  roy_list_reverse(&deque->head);
  deque->tail = phead;
}

size_t
roy_deque_unique(RoyDeque * deque,
                 RCompare   comparer) {
  return roy_list_unique(deque->head, comparer, deque->deleter);
}

void
roy_deque_sort(RoyDeque * deque,
               RCompare   comparer) {
  roy_list_sort(deque->head, comparer);
}

void
roy_deque_for_each(RoyDeque * deque,
                   ROperate   operate) {
  roy_list_for_each(deque->head, operate);
}

void
roy_deque_for_which(RoyDeque   * deque,
                    RCondition   condition,
                    ROperate     operate) {
  roy_list_for_which(deque->head, condition, operate);
}