#include "roylist.h"

static RoyList * node_new(const void * data, size_t element_size);
static void node_delete(RoyList * list);

RoyList *
roy_list_new(void) {
  RoyList * head = (RoyList *)malloc(sizeof(RoyList));
  RoyList * tail = (RoyList *)malloc(sizeof(RoyList));
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
roy_list_iterator(RoyList * list_head,
                  size_t    position) {
  int cur_position = 0;
  RoyList * iter = list_head;
  while (iter->next->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoyList *
roy_list_const_iterator(const RoyList * list_head,
                        size_t          position) {
  int cur_position = 0;
  const RoyList * iter = list_head;
  while (iter->next->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

RoyList *
roy_list_reverse_iterator(RoyList * list_tail,
                          size_t    reverse_position) {
  int cur_position = 0;
  RoyList * riter = list_tail;
  while (riter->prev->prev && cur_position <= reverse_position) {
    riter = riter->prev;
    cur_position++;
  }
  return riter;
}

const RoyList *
roy_list_const_reverse_iterator(const RoyList * list_tail,
                                size_t          reverse_position) {
  int cur_position = 0;
  const RoyList * riter = list_tail;
  while (riter->prev->prev && cur_position <= reverse_position) {
    riter = riter->prev;
    cur_position++;
  }
  return riter;
}

RoyList *
roy_list_begin(RoyList * list_head) {
  return list_head->next->next ? list_head->next : NULL;
}

const RoyList *
roy_list_cbegin(const RoyList * list_head) {
  return list_head->next->next ? list_head->next : NULL;
}

RoyList *
roy_list_rbegin(RoyList * list_tail) {
  return list_tail->prev->prev ? list_tail->prev : NULL;
}

const RoyList *
roy_list_crbegin(const RoyList * list_tail) {
  return list_tail->prev->prev ? list_tail->prev : NULL;
}

void *
roy_list_element(void *          dest,
                 const RoyList * list,
                 size_t       element_size,
                 size_t          position) {
  return
  position >= 0 && position < roy_list_size(list)                           ?
  memcpy(dest, roy_list_const_iterator(list, position)->data, element_size) :
  NULL;
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
                size_t       position,
                const void * data,
                size_t    element_size) {
  return 
  roy_list_push_front(roy_list_iterator(list_head, position - 1),
                      data,
                      element_size);
}

RoyList *
roy_list_insert_reverse(RoyList    * list_tail,
                        size_t       reverse_position,
                        const void * data,
                        size_t       element_size) {
  return 
  roy_list_push_back(roy_list_reverse_iterator(list_tail, reverse_position - 1),
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
               size_t    position) {
  return roy_list_pop_front(roy_list_iterator(list_head, position - 1));
}

RoyList *
roy_list_erase_reverse(RoyList * list_tail,
                       size_t    reverse_position) {
  return
  roy_list_pop_back(roy_list_reverse_iterator(list_tail, reverse_position - 1));
}

RoyList *
roy_list_pop_front(RoyList * list_head) {
  if (!roy_list_empty(list_head)) {
    RoyList * to_erase = roy_list_begin(list_head);
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
    RoyList * to_erase = roy_list_rbegin(list_tail);
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

RoyList *
roy_list_remove(RoyList    * list,
                const void * data,
                int       (* compare)(const void *, const void *)) {
  RoyList * temp = list;
  while (!roy_list_empty(temp)) {
    if (compare(temp->data, data) == 0) {
      roy_list_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
  return list;
}

void
roy_list_for_each(RoyList * list,
                  void   (* operate)(void *)) {
  for (RoyList * iter = roy_list_begin(list);
       iter && iter->next;
       iter = iter->next) {
    operate(iter->data);
  }
}

void roy_list_for_which(RoyList * list,
                        bool   (* condition)(const void *),
                        void   (* operate)(void *)) {
  for (RoyList * iter = roy_list_begin(list);
       iter && iter->next;
       iter = iter->next) {
    if (condition(iter->data)) {
      operate(iter->data);
    }
  } 
}


/* PRIVATE FUNCTIONS BELOW */

static RoyList *
node_new(const void * data,
         size_t    element_size) {
  RoyList * ret = (RoyList *)malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->prev = NULL;
  ret->next = NULL;
  return ret; 
}

static void
node_delete(RoyList * list) {
  free(list->data);
  free(list);
}