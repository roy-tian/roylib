#include "roylist.h"
#include "../tree/roymset.h"

static RoyList * node_new(void * data);
static void      node_delete(RoyList * list, ROperate deleter, void * user_data);
static void      sort_back(void * data, RoyList ** iter);

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
roy_list_delete(RoyList  * list,
                ROperate   deleter,
                void     * user_data) {
  roy_list_clear(list, deleter, user_data);
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
               ROperate   deleter,
               void     * user_data) {
  return roy_list_pop_front(roy_list_iterator(list_head, position)->prev,
                            deleter,
                            user_data);
}

bool
roy_list_erase_reverse(RoyList  * list_tail,
                       size_t     rposition,
                       ROperate   deleter,
                       void     * user_data) {
  return roy_list_pop_back(roy_list_riterator(list_tail, rposition)->next,
                           deleter,
                           user_data);
}

bool
roy_list_pop_front(RoyList  * list_head,
                   ROperate   deleter,
                   void     * user_data) {
  if (!roy_list_empty(list_head)) {
    RoyList * to_erase  = roy_list_begin(list_head);
    RoyList * next_elem = to_erase->next;
    list_head->next     = next_elem;
    next_elem->prev     = list_head;
    node_delete(to_erase, deleter, user_data);
    return true;
  }
  return false;
}

bool
roy_list_pop_back(RoyList  * list_tail,
                  ROperate   deleter,
                  void     * user_data) {
  if (!roy_list_rempty(list_tail)) {
    RoyList * to_erase  = roy_list_rbegin(list_tail);
    RoyList * prev_elem = to_erase->prev;
    list_tail->prev     = prev_elem;
    prev_elem->next     = list_tail;
    node_delete(to_erase, deleter, user_data);
    return true;
  }
  return false;
}

void
roy_list_clear(RoyList  * list_head,
               ROperate   deleter,
               void     * user_data) {
  while (!roy_list_empty(list_head)) {
    roy_list_pop_front(list_head, deleter, user_data);
  }
}

size_t
roy_list_remove(RoyList    * list,
                const void * data,
                RCompare     comparer,
                ROperate     deleter,
                void       * user_data) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (comparer(roy_list_cbegin(list)->data, data) == 0) {
      roy_list_pop_front(iter, deleter, user_data);
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
                   ROperate     deleter,
                   void       * user_data) {
  RoyList * iter = list;
  size_t count = 0;
  while (!roy_list_empty(iter)) {
    if (condition(roy_list_cbegin(list)->data)) {
      roy_list_pop_front(iter, deleter, user_data);
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
roy_list_unique(RoyList  * list,
                RCompare   comparer,
                ROperate   deleter,
                void     * user_data) {
  RoyList * temp = list;
  size_t count = 0;
  while (temp->next && temp->next->next && temp->next->next->next) {
    if (comparer(roy_list_cbegin(temp)->data,
                roy_list_cbegin(temp->next)->data) == 0) {
      roy_list_pop_front(temp, deleter, user_data);
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
  RoyMSet * mset = roy_mset_new();
  RoyList * iter = roy_list_begin(list);
  while (iter && iter->next) {
    roy_mset_insert(&mset, iter->data, (RCompare)comparer);
    iter = iter->next;
  }
  iter = roy_list_begin(list);
  roy_mset_for_each(mset, (ROperate)sort_back, &iter);
  roy_mset_delete(mset, NULL, NULL);
}

void
roy_list_for_each(RoyList  * list,
                  ROperate   operate,
                  void     * user_data) {
  for (RoyList * iter = roy_list_begin(list);
       iter && iter->next;
       iter = iter->next) {
    operate(iter->data, user_data);
  }
}

void roy_list_for_which(RoyList    * list,
                        RCondition   condition,
                        ROperate     operate,
                        void       * user_data) {
  for (RoyList * iter = roy_list_begin(list);
       iter && iter->next;
       iter = iter->next) {
    if (condition(iter->data)) {
      operate(iter->data, user_data);
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
            ROperate  deleter,
            void    * user_data) {
  if (deleter) {
    deleter(list->data, user_data);
  }
  free(list);
}


static void
sort_back(void    *  data,
          RoyList ** iter) {
  (*iter)->data = data;
  (*iter) = (*iter)->next;
}
