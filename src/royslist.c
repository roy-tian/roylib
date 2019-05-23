#include "../include/royslist.h"
#include <stdlib.h>
#include <string.h>

static RoySList * node_new(const void * data, size_t element_size);
static void node_delete(RoySList * slist);

RoySList *
roy_slist_new(void) {
  RoySList * ret = malloc(sizeof(void *) + sizeof(RoySList *));
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
roy_slist_front(RoySList * slist) {
  return slist->next;
}

const RoySList *
roy_slist_const_front(const RoySList * slist) {
  return slist->next;
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
  return roy_slist_const_front(slist) == NULL;
}

RoySList *
roy_slist_push_front(RoySList   * slist,
                     const void * data,
                     size_t       element_size) {
  RoySList * elem = node_new(data, element_size);
  elem->next = slist->next;
  slist->next = elem;
  return slist;
}

RoySList *
roy_slist_pop_front(RoySList * slist) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_front(slist);
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
  RoySList * temp = roy_slist_front(slist);
  while (!roy_slist_empty(temp)) {
    if (condition(temp->data)) {
      roy_slist_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
  return slist;
}

RoySList * roy_slist_reverse(RoySList * slist);

RoySList * roy_slist_unique(RoySList * slist, int (*compare)(const void *, const void *));

RoySList * roy_slist_sort(RoySList * slist, int (*compare)(const void *, const void *));

void
roy_slist_for_each(RoySList * slist,
                   void    (* iterate)(void *)) {
  for (RoySList * iter = roy_slist_front(slist);
       iter->next != NULL;
       iter = iter->next) {
    iterate(iter->data);
  }
}

void roy_slist_for_which(RoySList * slist,
                         bool    (* condition)(const void *),
                         void    (* iterate)(void *)) {
  for (RoySList * iter = roy_slist_front(slist);
       iter->next != NULL;
       iter = iter->next) {
    if (condition(iter->data)) {
      iterate(iter->data);
    }
  } 
}

/* PRIVATE FUNCTIONS BELOW */

static RoySList *
node_new(const void * data,
         size_t       element_size) {
  RoySList * ret = malloc(sizeof(void *) + sizeof(RoySList *));
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