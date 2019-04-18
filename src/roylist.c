#include "../include/roylist.h"
#include <stdlib.h>
#include <string.h>

RoyList *
roy_list_new(void) {
  RoyList * ret = malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  ret->data = NULL;
  ret->next = NULL;
  ret->prev = NULL;
  return ret;
}

RoyList *
roy_list_new_with_data(const void * data,
                       size_t       element_size) {
  RoyList * ret = malloc(sizeof(void *) + sizeof(RoyList *) * 2);
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->next = NULL;
  ret->prev = NULL;
  return ret; 
}

void
roy_list_delete_node(RoyList * list) {
  free(list->data);
  free(list);
}

void
roy_list_delete(RoyList * list) {
  roy_list_clear(list);
  free(list);
}

RoyList *
roy_list_pointer(RoyList * list,
                 int       position) {
  int cur_position = 0;
  RoyList * iter = list;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

RoyList *
roy_list_front(RoyList * list) {
  return list->next;
}

RoyList *
roy_list_back(RoyList * list) {
  RoyList * iter = roy_list_front(list);
  while (iter->next) {
    iter = iter->next;
  }
  return iter; 
}

const RoyList *
roy_list_const_pointer(const RoyList * list,
                       int             position) {
  int cur_position = 0;
  const RoyList * iter = list;
  while (iter->next && cur_position <= position) {
    iter = iter->next;
    cur_position++;
  }
  return iter;
}

const RoyList *
roy_list_const_front(const RoyList * list) {
  return list->next;
}

const RoyList *
roy_list_const_back(const RoyList * list) {
  const RoyList * iter = roy_list_const_front(list);
  while (iter->next) {
    iter = iter->next;
  }
  return iter;  
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
roy_list_length(const RoyList * list) {
  const RoyList * iter = list;
  size_t count = 0;
  while (iter->next) {
    iter = iter->next;
    count++;
  }
  return count;
}

bool
roy_list_empty(const RoyList * list) {
  return roy_list_const_front(list) == NULL;
}


RoyList *
roy_list_insert(RoyList    * list,
                int          position,
                const void * data,
                size_t       element_size) {
  return 
  roy_list_push_front(roy_list_pointer(list, position - 1),
                       data,
                       element_size);
}

RoyList *
roy_list_push_front(RoyList    * list,
                    const void * data,
                    size_t       element_size) {
  RoyList * elem = roy_list_new_with_data(data, element_size);
  elem->next = list->next;
  list->next = elem;
  return list;
}

RoyList *
roy_list_push_back(RoyList    * list,
                   const void * data,
                   size_t       element_size) {
  return  roy_list_push_front(roy_list_back(list), data, element_size);
}

RoyList *
roy_list_erase(RoyList * list,
               int       position) {
  return roy_list_pop_front(roy_list_pointer(list, position - 1));
}

RoyList *
roy_list_pop_front(RoyList * list) {
  if (!roy_list_empty(list)) {
    RoyList * to_erase = roy_list_front(list);
    list->next = to_erase->next;
    roy_list_delete_node(to_erase);
  }
  return list;
}

RoyList *
roy_list_pop_back(RoyList * list) {
  return roy_list_pop_front(roy_list_back(list));
}

RoyList *
roy_list_clear(RoyList * list) {
  while (!roy_list_empty(list)) {
    roy_list_pop_front(list);
  }
  return list;
}