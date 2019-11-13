#include "../include/royslist.h"

static RoySList * node_new(RCData data, size_t element_size);
static void       node_delete(RoySList * slist);
static RoySList * back(RoySList * slist);

RoySList *
roy_slist_new(void) {
  RoySList * ret = (RoySList *)malloc(sizeof(RoySList));
  ret->data = NULL;
  ret->next = NULL;
  return ret;
}

void
roy_slist_delete(RoySList * slist) {
  roy_slist_clear(slist);
  free(slist);
  slist = NULL;
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
                   size_t     position) {
  RoySList * iter = slist;
  while (iter->next) {
    iter = iter->next;
    position--;
  }
  return iter;
}

const RoySList *
roy_slist_citerator(const RoySList * slist,
                    size_t           position) {
  const RoySList * iter = slist;
  while (iter->next) {
    iter = iter->next;
    position--;
  }
  return iter;
}

RData
roy_slist_element(void           * dest,
                  const RoySList * slist,
                  size_t           element_size,
                  size_t           position) {
  return memcpy(dest,
                roy_slist_citerator(slist, position)->data,
                element_size);
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

void
roy_slist_push_front(RoySList   * slist,
                     RCData data,
                     size_t       element_size) {
  RoySList * elem = node_new(data, element_size);
  elem->next      = slist->next;
  slist->next     = elem;
}

bool
roy_slist_pop_front(RoySList * slist) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    node_delete(to_erase);
    return true;
  }
  return false;
}

bool
roy_slist_erase(RoySList * slist,
                size_t     position) {
  RoySList * iter = slist;
  while (iter->next && position > 0) {
    iter = iter->next;
    position--;
  }
  return roy_slist_pop_front(iter);
}

void
roy_slist_clear(RoySList * slist) {
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist);
  }
}

size_t
roy_slist_remove(RoySList   * slist,
                 RCData data,
                 RCompare     compare) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (compare(roy_slist_cbegin(iter)->data, data) == 0) {
      roy_slist_pop_front(iter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

size_t
roy_slist_remove_if(RoySList   * slist,
                    RCondition   condition) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (condition(roy_slist_cbegin(iter)->data)) {
      roy_slist_pop_front(iter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

void
roy_slist_reverse(RoySList * slist) {
  RoySList * pback = back(slist);
  while (roy_slist_cbegin(slist) != pback) {
    RoySList * first = roy_slist_begin(slist);
    slist->next = first->next;
    first->next = pback->next;
    pback->next = first;
  }
}

void
roy_slist_unique(RoySList * slist,
                 RCompare   compare) {
  RoySList * temp = slist;
  while (temp->next && temp->next->next) {
    if (compare(roy_slist_cbegin(temp)->data,
                roy_slist_cbegin(temp->next)->data) == 0) {
      roy_slist_pop_front(temp);
    } else {
      temp = temp->next;
    }
  }
}

// TODO
void
roy_slist_sort(RoySList * slist,
               RCompare   compare) {
}


void
roy_slist_for_each(RoySList * slist,
                   ROperate   operate) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    operate(iter->data);
  }
}

void roy_slist_for_which(RoySList   * slist,
                         RCondition   condition,
                         ROperate     operate) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    if (condition(iter->data)) {
      operate(iter->data);
    }
  } 
}

/* PRIVATE FUNCTIONS BELOW */

static RoySList *
node_new(RCData data,
         size_t       element_size) {
  RoySList * ret = (RoySList *)malloc(sizeof(RoySList));
  ret->data = malloc(element_size);
  memcpy(ret->data, data, element_size);
  ret->next = NULL;
  return ret; 
}

static void
node_delete(RoySList * slist) {
  free(slist->data);
  free(slist);
  slist = NULL;
}

static RoySList *
back(RoySList * slist) {
  while (slist->next) {
    slist = slist->next;
  }
  return slist;
}