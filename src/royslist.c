#include "../include/royslist.h"

static void       delete_node(RoySList * slist, ROperate deleter);
static RoySList * back(RoySList * slist);
static int        gap(size_t slist_size);

RoySList *
roy_slist_new(void * data) {
  RoySList * ret = (RoySList *)malloc(sizeof(RoySList));
  ret->data = data;
  ret->next = NULL;
  return ret;
}

void
roy_slist_delete(RoySList * slist,
                 ROperate   deleter) {
  roy_slist_clear(slist, deleter);
  free(slist);
  slist = NULL;
}

RoySList *
roy_slist_begin(RoySList * slist) {
  return slist->next;
}

const RoySList *
roy_slist_cbegin(const RoySList * slist) {
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
roy_slist_push_front(RoySList * slist,
                     void     * data) {
  RoySList * elem = roy_slist_new(data);
  elem->next      = slist->next;
  slist->next     = elem;
}

bool
roy_slist_pop_front(RoySList * slist,
                    ROperate   deleter) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    delete_node(to_erase, deleter);
    return true;
  }
  return false;
}

bool
roy_slist_erase(RoySList * slist,
                size_t     position,
                ROperate   deleter) {
  RoySList * iter = slist;
  while (iter->next && position > 0) {
    iter = iter->next;
    position--;
  }
  return roy_slist_pop_front(iter, deleter);
}

void
roy_slist_clear(RoySList * slist,
                ROperate   deleter) {
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist, deleter);
  }
}

size_t
roy_slist_remove(RoySList   * slist,
                 const void * data,
                 RCompare     compare,
                 ROperate     deleter) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (compare(roy_slist_cbegin(iter)->data, data) == 0) {
      roy_slist_pop_front(iter, deleter);
      count++;
    } else {
      iter = iter->next;
    }
  }
  return count;
}

size_t
roy_slist_remove_if(RoySList   * slist,
                    RCondition   condition,
                    ROperate     deleter) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (condition(roy_slist_cbegin(iter)->data)) {
      roy_slist_pop_front(iter, deleter);
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
                 RCompare   compare,
                 ROperate   deleter) {
  RoySList * temp = slist;
  while (temp->next && temp->next->next) {
    if (compare(roy_slist_cbegin(temp)->data,
                roy_slist_cbegin(temp->next)->data) == 0) {
      roy_slist_pop_front(temp, deleter);
    } else {
      temp = temp->next;
    }
  }
}


void
roy_slist_sort(RoySList * slist,
               RCompare   compare) {
  size_t size = roy_slist_size(slist);
  for (int inc = gap(size); inc != 0; inc--) {
    for (int i = inc; i != size; i++) {
      RoySList * temp = roy_slist_iterator(slist, i);
    }
  }
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

static void
delete_node(RoySList * slist,
            ROperate   deleter) {
  deleter(slist->data);
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

static int
gap(size_t slist_size) {
  int index = 0;
  while (!(GAPS[index] >= slist_size && GAPS[index + 1] <= slist_size)) {
    index++;
  }
  return index;
}