#include "../include/roylist.h"
#include <stdlib.h>
#include <string.h>

RoyList * node_new(const void * data, size_t element_size);
void node_delete(RoyList * list);

RoyList *
roy_list_new(void) {
  RoyList * head = malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  RoyList * tail = malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  head->data = tail->data = NULL;
  head->next = tail;
  head->prev = NULL;
  tail->next = NULL;
  tail->prev = head;
  return head;
}

void
roy_list_delete(RoyList * list) {
  roy_list_clear(list);
  free(list);
}

RoyList *
roy_list_pointer(RoyList * list_head,
                 int       position) {
  int cur_position = 0;
  RoyList * iter = list_head;
  while (iter->next->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoyList *
roy_list_const_pointer(const RoyList * list_head,
                       int             position) {
  int cur_position = 0;
  const RoyList * iter = list_head;
  while (iter->next->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

RoyList *
roy_list_reverse_pointer(RoyList * list_tail,
                         int       reverse_position) {
  int cur_position = 0;
  RoyList * riter = list_tail;
  while (riter->prev->prev && cur_position <= reverse_position) {
    riter = riter->prev;
    cur_position++;
  }
  return riter;
}

const RoyList *
roy_list_const_reverse_pointer(const RoyList * list_tail,
                               int             reverse_position) {
  int cur_position = 0;
  const RoyList * riter = list_tail;
  while (riter->prev->prev && cur_position <= reverse_position) {
    riter = riter->prev;
    cur_position++;
  }
  return riter;
}

RoyList *
roy_list_front(RoyList * list_head) {
  return list_head->next->next ? list_head->next : NULL;
}

const RoyList *
roy_list_const_front(const RoyList * list_head) {
  return list_head->next->next ? list_head->next : NULL;
}

RoyList *
roy_list_back(RoyList * list_tail) {
  return list_tail->prev->prev ? list_tail->prev : NULL;
}

const RoyList *
roy_list_const_back(const RoyList * list_tail) {
  return list_tail->prev->prev ? list_tail->prev : NULL;
}

void *
roy_list_element(void *          dest,
                 size_t          element_size,
                 const RoyList * list,
                 int             position) {
  memcpy(dest,
         roy_list_const_pointer(list, position)->data,
         element_size);
  return dest;   
}

size_t
roy_list_size(const RoyList * list_head) {
  const RoyList * iter = list_head;
  size_t count = 0;
  while (iter->next->next) {
    iter = iter->next;
    count++;
  }
  return count;
}

bool
roy_list_empty(const RoyList * list_head) {
  return list_head->next->next == NULL;
}

RoyList *
roy_list_insert(RoyList    * list_head,
                int          position,
                const void * data,
                size_t       element_size) {
  return 
  roy_list_push_front(roy_list_pointer(list_head, position - 1),
                      data,
                      element_size);
}

RoyList *
roy_list_insert_reverse(RoyList    * list_tail,
                        int          reverse_position,
                        const void * data,
                        size_t       element_size) {
  return 
  roy_list_push_back(roy_list_reverse_pointer(list_tail, reverse_position - 1),
                     data,
                     element_size);
}

RoyList *
roy_list_push_front(RoyList    * list_head,
                    const void * data,
                    size_t       element_size) {
  RoyList * elem = node_new(data, element_size);
  RoyList * front = list_head->next;
  list_head->next = elem;
  front->prev = elem;
  elem->prev = list_head;
  elem->next = front;
  return list_head;
}

RoyList *
roy_list_push_back(RoyList    * list_tail,
                   const void * data,
                   size_t       element_size) {
  RoyList * elem = node_new(data, element_size);
  RoyList * back = list_tail->prev;
  list_tail->prev = elem;
  back->next = elem;
  elem->prev = back;
  elem->next = list_tail;
  return list_tail;
}

RoyList *
roy_list_erase(RoyList * list_head,
               int       position) {
  return roy_list_pop_front(roy_list_pointer(list_head, position - 1));
}

RoyList *
roy_list_erase_reverse(RoyList * list_tail,
                       int       reverse_position) {
  return
  roy_list_pop_back(roy_list_reverse_pointer(list_tail, reverse_position - 1));
}

RoyList *
roy_list_pop_front(RoyList * list_head) {
  if (!roy_list_empty(list_head)) {
    RoyList * to_erase = roy_list_front(list_head);
    RoyList * next_elem = to_erase->next;
    list_head->next = next_elem;
    next_elem->prev = list_head;
    node_delete(to_erase);
  }
  return list_head;
}

RoyList *
roy_list_pop_back(RoyList * list_tail) {
  if (list_tail->prev->prev) { // not empty
    RoyList * to_erase = roy_list_back(list_tail);
    RoyList * prev_elem = to_erase->prev;
    list_tail->prev = prev_elem;
    prev_elem->next = list_tail;
    node_delete(to_erase);
  }
  return list_tail;
}

RoyList *
roy_list_clear(RoyList * list) {
  while (!roy_list_empty(list)) {
    roy_list_pop_front(list);
  }
  return list;
}

/* PRIVATE FUNCTIONS BELOW */

RoyList *
node_new(const void * data,
         size_t       element_size) {
  RoyList * ret = malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->prev = NULL;
  ret->next = NULL;
  return ret; 
}

void
node_delete(RoyList * list) {
  free(list->data);
  free(list);
}