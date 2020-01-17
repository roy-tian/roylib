#include "royslist.h"
#include "../trivials/shellsort.h"

static RoySList * node_new(void * data);
static void       node_delete(RoySList * slist, ROperate deleter);
static RoySList * back(RoySList * slist);

RoySList *
roy_slist_new(void) {
  return node_new(NULL);
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
  while (iter->next && position < roy_slist_size(slist)) {
    iter = iter->next;
    position--;
  }
  return iter;
}

const RoySList *
roy_slist_citerator(const RoySList * slist,
                    size_t           position) {
  const RoySList * iter = slist;
  while (iter->next && position < roy_slist_size(slist)) {
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
  RoySList * elem = node_new(data);
  elem->next      = slist->next;
  slist->next     = elem;
}

bool
roy_slist_pop_front(RoySList * slist,
                    ROperate   deleter) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    node_delete(to_erase, deleter);
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
                 RCompare     comparer,
                 ROperate     deleter) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (comparer(roy_slist_cbegin(iter)->data, data) == 0) {
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

size_t
roy_slist_unique(RoySList * slist,
                 RCompare   comparer,
                 ROperate   deleter) {
  RoySList * temp = slist;
  size_t count = 0;
  while (temp->next && temp->next->next) {
    if (comparer(roy_slist_cbegin(temp)->data,
                roy_slist_cbegin(temp->next)->data) == 0) {
      roy_slist_pop_front(temp, deleter);
      count++;
    } else {
      temp = temp->next;
    }
  }
  return count;
}

void
roy_slist_sort(RoySList * slist,
               RCompare   comparer) {
  size_t size = roy_slist_size(slist);
  uint64_t i, j, k;
  for (i = gap_index(size); i > 0; i--) {
    uint64_t cur_gap = GAPS[i];
    for (j = cur_gap; j < size; j++) {
      void * tempj = roy_slist_iterator(slist, j)->data;
      for (k = j; k >= cur_gap; k -= cur_gap) {
        void * tempk = roy_slist_citerator(slist, k - cur_gap)->data;
        if (comparer(tempj, tempk) < 0) {
          roy_slist_iterator(slist, k)->data = tempk;
        } else {
          break;
        }
      }
      roy_slist_iterator(slist, k)->data = tempj;
    }
  }
}

RoySList *
roy_slist_find(RoySList   * slist,
               const void * data,
               RCompare     comparer) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    if (comparer(iter->data, data) == 0) {
      return iter;
    }
  }
  return NULL;
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
node_new(void * data) {
  RoySList * ret = malloc(sizeof(RoySList));
  ret->data = data;
  ret->next = NULL;
  return ret;
}

static void
node_delete(RoySList * slist,
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
