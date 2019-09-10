#include "royslist.h"

static RoySList * node_new(const void * data, size_t element_size);
static void       node_delete(RoySList * slist);
static RoySList * back(RoySList * slist);

RoySList *
roy_slist_new(void) {
  RoySList * ret = (RoySList *)malloc(sizeof(RoySList));
  assert(ret != NULL);
  ret->data = NULL;
  ret->next = NULL;
  return ret;
}

void
roy_slist_delete(RoySList * slist) {
  roy_slist_clear(slist);
  free(slist);
}

RoySList *
roy_slist_begin(RoySList * slist) {
  assert(slist != NULL);
  return slist->next;
}

const RoySList *
roy_slist_cbegin(const RoySList *slist) {
  assert(slist != NULL);
  return slist->next;
}

RoySList *
roy_slist_iterator(RoySList * slist,
                   size_t     position) {
  assert(slist != NULL);
  assert(position < roy_slist_size(slist));
  size_t cur_position = 0;
  RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoySList *
roy_slist_const_iterator(const RoySList * slist,
                         size_t           position) {
  assert(slist != NULL);
  assert(position < roy_slist_size(slist));
  int cur_position = 0;
  const RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

void *
roy_slist_element(void           * dest,
                  const RoySList * slist,
                  size_t           element_size,
                  size_t           position) {
  assert(dest != NULL);
  assert(slist != NULL);
  assert(position < roy_slist_size(slist));
  return memcpy(dest,
                roy_slist_const_iterator(slist, position)->data,
                element_size);
}

size_t
roy_slist_size(const RoySList * slist) {
  assert(slist != NULL);
  const RoySList * iter = slist;
  size_t count = 0;
  while (iter->next) {
    iter = iter->next;
    count++;
  }
  return count;
}

bool
roy_slist_empty(const RoySList * slist) {
  assert(slist != NULL);
  return roy_slist_cbegin(slist) == NULL;
}

RoySList *
roy_slist_push_front(RoySList   * slist,
                     const void * data,
                     size_t       element_size) {
  assert(slist != NULL);
  assert(data != NULL);
  RoySList * elem = node_new(data, element_size);
  elem->next      = slist->next;
  slist->next     = elem;
  return slist;
}

RoySList *
roy_slist_pop_front(RoySList * slist) {
  assert(slist != NULL);
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    node_delete(to_erase);
  }
  return slist;
}

RoySList *
roy_slist_erase(RoySList * slist,
                size_t     position) {
  assert(slist != NULL);
  assert(position < roy_slist_size(slist));
  return roy_slist_pop_front(roy_slist_iterator(slist, position - 1));
}

RoySList *
roy_slist_clear(RoySList * slist) {
  assert(slist != NULL);
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist);
  }
  return slist;
}

RoySList *
roy_slist_remove(RoySList   * slist,
                 const void * data,
                 int       (* compare)(const void *, const void *)) {
  assert(slist != NULL);
  assert(data != NULL);
  assert(compare != NULL);
  RoySList * temp = slist;
  while (!roy_slist_empty(temp)) {
    if (compare(temp->data, data) == 0) {
      roy_slist_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
  return slist;
}

RoySList *
roy_slist_remove_if(RoySList * slist,
                    bool    (* condition)(const void *)) {
  assert(slist != NULL);
  assert(condition != NULL);
  RoySList * temp = slist;
  while (!roy_slist_empty(temp)) {
    if (condition(temp->data)) {
      roy_slist_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
  return slist;
}

RoySList *
roy_slist_reverse(RoySList * slist) {
  assert(slist != NULL);
  RoySList * pback = back(slist);
  while (roy_slist_cbegin(slist) != pback) {
    RoySList * first = roy_slist_begin(slist);
    slist->next = first->next;
    first->next = pback->next;
    pback->next = first;
  }
  return slist;
}

RoySList *
roy_slist_unique(RoySList * slist,
                 int     (* compare)(const void *, const void *)) {
  assert(slist != NULL);
  assert(compare != NULL);
  RoySList * temp = slist;
  while (!roy_slist_empty(temp) && !roy_slist_empty(temp->next)) {
    if (compare(roy_slist_cbegin(temp)->data,
             roy_slist_cbegin(temp->next)->data) == 0) {
      roy_slist_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
  return slist;
}

// TODO
RoySList *
roy_slist_sort(RoySList * slist,
               int     (* compare)(const void *, const void *)) {
  return slist;
}


void
roy_slist_for_each(RoySList * slist,
                   void    (* operate)(void *)) {
  assert(slist != NULL);
  assert(operate != NULL);
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    operate(iter->data);
  }
}

void roy_slist_for_which(RoySList * slist,
                         bool    (* condition)(const void *),
                         void    (* operate)        (void *)) {
  assert(slist != NULL);
  assert(condition != NULL);
  assert(operate != NULL);
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    if (condition(iter->data)) {
      operate(iter->data);
    }
  } 
}

/* PRIVATE FUNCTIONS BELOW */

static RoySList *
node_new(const void * data,
         size_t       element_size) {
  RoySList * ret = (RoySList *)malloc(sizeof(void *) + sizeof(RoySList *));
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->next = NULL;
  return ret; 
}

static void
node_delete(RoySList * slist) {
  free(slist->data);
  free(slist);
}

static RoySList *
back(RoySList * slist) {
  while (slist->next) {
    slist = slist->next;
  }
  return slist;
}