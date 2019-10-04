#include "../include/roylist.h"

static RoyList * node_new(const void * data, size_t element_size);
static void      node_delete(RoyList * list);

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
  list = NULL;
}

RoyList *
roy_list_iterator(RoyList * list_head,
                  size_t    position) {
  RoyList * iter = roy_list_begin(list_head);
  while (iter->next && position > 0) {
    iter = iter->next;
    position--;
  }
  return iter;
}

const RoyList *
roy_list_citerator(const RoyList * list_head,
                   size_t          position) {
  const RoyList * iter = roy_list_cbegin(list_head);
  while (iter->next && position > 0) {
    iter = iter->next;
    position--;
  }
  return iter;
}

RoyList *
roy_list_riterator(RoyList * list_tail,
                   size_t    rposition) {
  RoyList * riter = roy_list_rbegin(list_tail);
  while (riter->prev && rposition > 0) {
    riter = riter->prev;
    rposition--;
  }
  return riter;
}

const RoyList *
roy_list_criterator(const RoyList * list_tail,
                    size_t          rposition) {
  const RoyList * riter = roy_list_crbegin(list_tail);
  while (riter->prev && rposition > 0) {
    riter = riter->prev;
    rposition--;
  }
  return riter;
}

RoyList *
roy_list_begin(RoyList * list_head) {
  return list_head->next;
}

const RoyList *
roy_list_cbegin(const RoyList * list_head) {
  return list_head->next;
}

RoyList *
roy_list_rbegin(RoyList * list_tail) {
  return list_tail->prev;
}

const RoyList *
roy_list_crbegin(const RoyList * list_tail) {
  return list_tail->prev;
}

void *
roy_list_element(void *          dest,
                 const RoyList * list,
                 size_t          element_size,
                 size_t          position) {
  return memcpy(dest, roy_list_citerator(list, position)->data, element_size);
}

size_t
roy_list_size(const RoyList * list_head) {
  const RoyList * iter = list_head;
  size_t count = 0;
  while (iter->next && iter->next->next) {
    iter = iter->next;
    count++;
  }
  return count;
}

size_t
roy_list_rsize(const RoyList * list_tail) {
  const RoyList * iter = list_tail;
  size_t count = 0;
  while (iter->prev && iter->prev->prev) {
    iter = iter->prev;
    count++;
  }
  return count;
}

bool
roy_list_empty(const RoyList * list_head) {
  return list_head->next->next == NULL;
}

bool
roy_list_rempty(const RoyList * list_tail) {
  return list_tail->prev->prev == NULL;
}

bool
roy_list_insert(RoyList    * list_head,
                size_t       position,
                const void * data,
                size_t       element_size) {
  RoyList * iter = roy_list_iterator(list_head, position);
  if (iter) {
    roy_list_push_front(iter->prev, data, element_size);
    return true;
  }
  return false;
}

bool
roy_list_insert_reverse(RoyList    * list_tail,
                        size_t       rposition,
                        const void * data,
                        size_t       element_size) {
  RoyList * iter = roy_list_riterator(list_tail, rposition);
  if (iter) {
    roy_list_push_back(iter->next, data, element_size);
    return true;
  }
  return false;
}

void
roy_list_push_front(RoyList    * list_head,
                    const void * data,
                    size_t       element_size) {
  RoyList * elem  = node_new(data, element_size);
  RoyList * front = list_head->next;
  list_head->next = elem;
  front->prev     = elem;
  elem->prev      = list_head;
  elem->next      = front;
}

void
roy_list_push_back(RoyList    * list_tail,
                   const void * data,
                   size_t       element_size) {
  RoyList * elem  = node_new(data, element_size);
  RoyList * back  = list_tail->prev;
  list_tail->prev = elem;
  back->next      = elem;
  elem->prev      = back;
  elem->next      = list_tail;
}

bool
roy_list_erase(RoyList * list_head,
               size_t    position) {
  return roy_list_pop_front(roy_list_iterator(list_head, position)->prev);
}

bool
roy_list_erase_reverse(RoyList * list_tail,
                       size_t    rposition) {
  return roy_list_pop_back(roy_list_riterator(list_tail, rposition)->next);
}

bool
roy_list_pop_front(RoyList * list_head) {
  if (!roy_list_empty(list_head)) {
    RoyList * to_erase  = roy_list_begin(list_head);
    RoyList * next_elem = to_erase->next;
    list_head->next     = next_elem;
    next_elem->prev     = list_head;
    node_delete(to_erase);
    return true;
  }
  return false;
}

bool
roy_list_pop_back(RoyList * list_tail) {
  if (!roy_list_rempty(list_tail)) {
    RoyList * to_erase  = roy_list_rbegin(list_tail);
    RoyList * prev_elem = to_erase->prev;
    list_tail->prev     = prev_elem;
    prev_elem->next     = list_tail;
    node_delete(to_erase);
    return true;
  }
  return false;
}

void
roy_list_clear(RoyList * list) {
  while (!roy_list_empty(list)) {
    roy_list_pop_front(list);
  }
}

size_t
roy_list_remove(RoyList    * list,
                const void * data,
                RCompare     compare) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (compare(roy_list_cbegin(list)->data, data) == 0) {
      roy_list_pop_front(iter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

size_t
roy_list_remove_if(RoyList    * list,
                   RCondition   condition) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (condition(roy_list_cbegin(list)->data)) {
      roy_list_pop_front(iter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

void
roy_list_reverse(RoyList ** list) {
  RoyList * iter = *list;
  while (iter) {
    RoyList * temp = iter->next;
    iter->next = iter->prev;
    iter->prev = temp;
    iter = temp;
  }
  while ((*list)->prev) {
    *list = (*list)->prev;
  }
}

void
roy_list_unique(RoyList * list,
                RCompare  compare) {
    RoyList * temp = list;
    while (temp->next && temp->next->next && temp->next->next->next) {
    if (compare(roy_list_cbegin(temp)->data,
                roy_list_cbegin(temp->next)->data) == 0) {
      roy_list_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
}

// TODO
void
roy_list_sort(RoyList * list,
              RCompare compare) {
}

void
roy_list_for_each(RoyList  * list,
                  ROperate   operate) {
  for (RoyList * iter = roy_list_begin(list);
       iter && iter->next;
       iter = iter->next) {
    operate(iter->data);
  }
}

void roy_list_for_which(RoyList    * list,
                        RCondition   condition,
                        ROperate     operate) {
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
         size_t       element_size) {
  RoyList * ret = (RoyList *)malloc(sizeof(RoyList));
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
  list = NULL;
}
