#include "../include/royslist.h"

static RoySList * node_new(const void * data, size_t element_size);
static void       node_delete(RoySList * slist);
static RoySList * back(RoySList * slist);

RoySList *
roy_slist_new(void) {
  RoySList * ret = ROY_SLIST(malloc(sizeof(RoySList)));
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
  return slist->next;
}

const RoySList *
roy_slist_cbegin(const RoySList *slist) {
  return slist->next;
}
RoySList *
roy_slist_iterator(RoySList * slist,
                   int        position) {
  int cur_position = 0;
  RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoySList *
roy_slist_const_iterator(const RoySList * slist,
                         int              position) {
  int cur_position = 0;
  const RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

size_t
roy_slist_size(const RoySList * slist) {
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
  return roy_slist_cbegin(slist) == NULL;
}

RoySList *
roy_slist_push_front(RoySList   * slist,
                     const void * data,
                     size_t       element_size) {
  RoySList * elem = node_new(data, element_size);
  elem->next      = slist->next;
  slist->next     = elem;
  return slist;
}

RoySList *
roy_slist_pop_front(RoySList * slist) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    node_delete(to_erase);
  }
  return slist;
}

RoySList *
roy_slist_clear(RoySList * slist) {
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist);
  }
  return slist;
}

RoySList *
roy_slist_remove_if(RoySList * slist,
                    bool    (* condition)(const void *)) {
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

RoySList *
roy_slist_sort(RoySList * slist,
               int     (* compare)(const void *, const void *)) {
  return slist;
}


void
roy_slist_for_each(RoySList * slist,
                   void    (* operate)(void *)) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    operate(iter->data);
  }
}

void roy_slist_for_which(RoySList * slist,
                         bool    (* condition)(const void *),
                         void    (* operate)        (void *)) {
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
  RoySList * ret = ROY_SLIST(malloc(sizeof(void *) + sizeof(RoySList *)));
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