#include "../include/royslist.h"
#include <stdlib.h>
#include <string.h>

struct _RoySList {
  void * data;
  struct _RoySList * next;
};

RoySList *
roy_slist_new(void) {
  RoySList * ret = malloc(sizeof(void *) + sizeof(RoySList *));
  ret->data = NULL;
  ret->next = NULL;
  return ret;
}

RoySList *
roy_slist_new_with_data(const void * data,
                        size_t       element_size) {
  RoySList * ret = malloc(sizeof(void *) + sizeof(RoySList *));
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->next = NULL;
  return ret; 
}

void
roy_slist_delete_node(RoySList * slist) {
  free(slist->data);
  free(slist);
}

void
roy_slist_delete(RoySList * slist) {
  roy_slist_clear(slist);
  free(slist);
}

RoySList *
roy_slist_pointer(RoySList * slist,
                  int        position) {
  int cur_position = 0;
  RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

RoySList *
roy_slist_front(RoySList * slist) {
  return slist->next;
}

RoySList *
roy_slist_back(RoySList * slist) {
  RoySList * iter = roy_slist_front(slist);
  while (iter->next) {
    iter = iter->next;
  }
  return iter; 
}

const RoySList *
roy_slist_const_pointer(const RoySList * slist,
                        int              position) {
  int cur_position = 0;
  const RoySList * iter = slist;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoySList *
roy_slist_const_front(const RoySList * slist) {
  return slist->next;
}

const RoySList *
roy_slist_const_back(const RoySList * slist) {
  const RoySList * iter = roy_slist_const_front(slist);
  while (iter->next) {
    iter = iter->next;
  }
  return iter;  
}

void *
roy_slist_element(void *           dest,
                  size_t           element_size,
                  const RoySList * slist,
                  int              position) {
  memcpy(dest,
         roy_slist_const_pointer(slist, position)->data,
         element_size);
  return dest;   
}

size_t roy_slist_length(const RoySList * slist) {
  const RoySList * iter = slist;
  size_t count = 0;
  while (iter->next) {
    iter = iter->next;
    count++;
  }
  return count;
}

bool roy_slist_empty(const RoySList * slist) {
  return roy_slist_const_front(slist) == NULL;
}


RoySList *
roy_slist_insert(RoySList   * slist,
                 int          position,
                 const void * data,
                 size_t       element_size) {
  return 
  roy_slist_push_front(roy_slist_pointer(slist, position - 1),
                       data,
                       element_size);
}

RoySList *
roy_slist_push_front(RoySList   * slist,
                     const void * data,
                     size_t       element_size) {
  RoySList * elem = roy_slist_new_with_data(data, element_size);
  elem->next = slist->next;
  slist->next = elem;
  return slist;
}

RoySList *
roy_slist_push_back(RoySList   * slist,
                    const void * data,
                    size_t       element_size) {
  return  roy_slist_push_front(roy_slist_back(slist), data, element_size);
}

RoySList *
roy_slist_erase(RoySList * slist,
                int        position) {
  return roy_slist_pop_front(roy_slist_pointer(slist, position - 1));
}

RoySList *
roy_slist_pop_front(RoySList * slist) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_front(slist);
    slist->next = to_erase->next;
    roy_slist_delete_node(to_erase);
  }
  return slist;
}

RoySList *
roy_slist_pop_back(RoySList * slist) {
  return roy_slist_pop_front(roy_slist_back(slist));
}

RoySList *
roy_slist_clear(RoySList * slist) {
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist);
  }
  return slist;
}