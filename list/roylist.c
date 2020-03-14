#include "roylist.h"
#include "../trivial/shellsort.h"

static RoyList * node_new(void * data);
static void      node_delete(RoyList * list, ROperate deleter);

RoyList *
roy_list_new(void) {
  RoyList * head = malloc(sizeof(RoyList));
  RoyList * tail = malloc(sizeof(RoyList));
  head->data = tail->data = NULL;
  head->next = tail;
  head->prev = NULL;
  tail->next = NULL;
  tail->prev = head;
  return head;
}

void
roy_list_delete(RoyList * list, ROperate deleter) {
  roy_list_clear(list, deleter);
  free(list);
}

RoyList *
roy_list_iterator(RoyList * list_head,
                  size_t    position) {
  RoyList * iter = list_head;
  while (iter->next && iter->next->next &&
         position < roy_list_size(list_head)) {
    iter = iter->next;
    position--;
  }
  return iter;
}

const RoyList *
roy_list_citerator(const RoyList * list_head,
                   size_t          position) {
  const RoyList * iter = list_head;
  while (iter->next && iter->next->next &&
         position < roy_list_size(list_head)) {
    iter = iter->next;
    position--;
  }
  return iter;
}

RoyList *
roy_list_riterator(RoyList * list_tail,
                   size_t    rposition) {
  RoyList * riter = list_tail;
  while (riter->prev && riter->prev->prev &&
         rposition < roy_list_rsize(list_tail)) {
    riter = riter->prev;
    rposition--;
  }
  return riter;
}

const RoyList *
roy_list_criterator(const RoyList * list_tail,
                    size_t          rposition) {
  const RoyList * riter = list_tail;
  while (riter->prev && riter->prev->prev &&
         rposition < roy_list_rsize(list_tail)) {
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
roy_list_insert(RoyList * restrict list_head,
                size_t             position,
                void    * restrict data) {
  RoyList * iter = roy_list_iterator(list_head, position);
  if (iter) {
    roy_list_push_front(iter->prev, data);
    return true;
  }
  return false;
}

bool
roy_list_insert_reverse(RoyList * restrict list_tail,
                        size_t             rposition,
                        void    * restrict data) {
  RoyList * iter = roy_list_riterator(list_tail, rposition);
  if (iter) {
    roy_list_push_back(iter->next, data);
    return true;
  }
  return false;
}

void
roy_list_push_front(RoyList * restrict list_head,
                    void    * restrict data) {
  RoyList * elem  = node_new(data);
  RoyList * front = list_head->next;
  list_head->next = elem;
  front->prev     = elem;
  elem->prev      = list_head;
  elem->next      = front;
}

void
roy_list_push_back(RoyList * restrict list_tail,
                   void    * restrict data) {
  RoyList * elem  = node_new(data);
  RoyList * back  = list_tail->prev;
  list_tail->prev = elem;
  back->next      = elem;
  elem->prev      = back;
  elem->next      = list_tail;
}

bool
roy_list_erase(RoyList  * list_head,
               size_t     position,
               ROperate   deleter) {
  return roy_list_pop_front(roy_list_iterator(list_head, position)->prev,
                            deleter);
}

bool
roy_list_erase_reverse(RoyList  * list_tail,
                       size_t     rposition,
                       ROperate   deleter) {
  return roy_list_pop_back(roy_list_riterator(list_tail, rposition)->next,
                           deleter);
}

bool
roy_list_pop_front(RoyList  * list_head,
                   ROperate   deleter) {
  if (!roy_list_empty(list_head)) {
    RoyList * to_erase  = roy_list_begin(list_head);
    RoyList * next_elem = to_erase->next;
    list_head->next     = next_elem;
    next_elem->prev     = list_head;
    node_delete(to_erase, deleter);
    return true;
  }
  return false;
}

bool
roy_list_pop_back(RoyList  * list_tail,
                  ROperate   deleter) {
  if (!roy_list_rempty(list_tail)) {
    RoyList * to_erase  = roy_list_rbegin(list_tail);
    RoyList * prev_elem = to_erase->prev;
    list_tail->prev     = prev_elem;
    prev_elem->next     = list_tail;
    node_delete(to_erase, deleter);
    return true;
  }
  return false;
}

void
roy_list_clear(RoyList  * list,
               ROperate   deleter) {
  while (!roy_list_empty(list)) {
    roy_list_pop_front(list, deleter);
  }
}

size_t
roy_list_remove(RoyList    * list,
                const void * data,
                RCompare     comparer,
                ROperate     deleter) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (comparer(roy_list_cbegin(list)->data, data) == 0) {
      roy_list_pop_front(iter, deleter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

size_t
roy_list_remove_if(RoyList    * list,
                   RCondition   condition,
                   ROperate     deleter) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (condition(roy_list_cbegin(list)->data)) {
      roy_list_pop_front(iter, deleter);
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

size_t
roy_list_unique(RoyList * list,
                RCompare  comparer,
                ROperate  deleter) {
  RoyList * temp = list;
  size_t count = 0;
  while (temp->next && temp->next->next && temp->next->next->next) {
    if (comparer(roy_list_cbegin(temp)->data,
                roy_list_cbegin(temp->next)->data) == 0) {
      roy_list_pop_front(temp, deleter);
      count++;
    } else {
      temp = temp->next;
    }
  }
  return count;
}

void
roy_list_sort(RoyList  * list,
              RCompare   comparer) {
  size_t size = roy_list_size(list);
  uint64_t i, j, k;
  for (i = gap_index(size); i > 0; i--) {
    uint64_t cur_gap = GAPS[i];
    for (j = cur_gap; j < size; j++) {
      void * tempj = roy_list_iterator(list, j)->data;
      for (k = j; k >= cur_gap; k -= cur_gap) {
        void * tempk = roy_list_citerator(list, k - cur_gap)->data;
        if (comparer(tempj, tempk) < 0) {
          roy_list_iterator(list, k)->data = tempk;
        } else {
          break;
        }
      }
      roy_list_iterator(list, k)->data = tempj;
    }
  }
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
node_new(void * data) {
  RoyList * ret = malloc(sizeof(RoyList));
  ret->data = data;
  ret->prev = NULL;
  ret->next = NULL;
  return ret; 
}

static void
node_delete(RoyList * list,
            ROperate  deleter) {
  deleter(list->data);
  free(list);
}
