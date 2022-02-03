#include "royslist.h"
#include "../tree/roymset.h"

static RoySList * node_new(void * data);
static void       node_delete(RoySList * slist, ROperate deleter, void * user_data);
static RoySList * back(RoySList * slist);
static void       sort_back(void * data, RoySList ** iter);

struct RoySList_ {
  void             * data;
  struct RoySList_ * next;
};

RoySList *
roy_slist_new(void) {
  return node_new(NULL);
}

void
roy_slist_delete(RoySList * slist,
                 ROperate   deleter,
                 void     * user_data) {
  roy_slist_clear(slist, deleter, user_data);
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
roy_slist_push_front(RoySList * restrict slist,
                     void     * restrict data) {
  RoySList * elem = node_new(data);
  elem->next      = slist->next;
  slist->next     = elem;
}

bool
roy_slist_pop_front(RoySList * slist,
                    ROperate   deleter,
                    void     * user_data) {
  if (!roy_slist_empty(slist)) {
    RoySList * to_erase = roy_slist_begin(slist);
    slist->next = to_erase->next;
    node_delete(to_erase, deleter, user_data);
    return true;
  }
  return false;
}

bool
roy_slist_erase(RoySList * slist,
                size_t     position,
                ROperate   deleter,
                void     * user_data) {
  RoySList * iter = slist;
  while (iter->next && position > 0) {
    iter = iter->next;
    position--;
  }
  return roy_slist_pop_front(iter, deleter, user_data);
}

void
roy_slist_clear(RoySList * slist,
                ROperate   deleter,
                void     * user_data) {
  while (!roy_slist_empty(slist)) {
    roy_slist_pop_front(slist, deleter, user_data);
  }
}

size_t
roy_slist_remove(RoySList   * slist,
                 const void * data,
                 RCompare     comparer,
                 ROperate     deleter,
                 void       * user_data) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (comparer(roy_slist_cbegin(iter)->data, data) == 0) {
      roy_slist_pop_front(iter, deleter, user_data);
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
                    ROperate     deleter,
                    void       * user_data) {
  RoySList * iter = slist;
  size_t count = 0;
  while (!roy_slist_empty(iter)) {
    if (condition(roy_slist_cbegin(iter)->data)) {
      roy_slist_pop_front(iter, deleter, user_data);
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
                 ROperate   deleter,
                 void     * user_data) {
  RoySList * temp = slist;
  size_t count = 0;
  while (temp->next && temp->next->next) {
    if (comparer(roy_slist_cbegin(temp)->data,
                roy_slist_cbegin(temp->next)->data) == 0) {
      roy_slist_pop_front(temp, deleter, user_data);
      count++;
    } else {
      temp = temp->next;
    }
  }
  return count;
}

void
roy_slist_sort(RoySList *slist, RCompare comparer) {
  RoyMSet * mset = roy_mset_new();
  RoySList * iter = roy_slist_begin(slist);
  while (iter) {
    roy_mset_insert(&mset, iter->data, (RCompare)comparer);
    iter = iter->next;
  }
  iter = roy_slist_begin(slist);
  roy_mset_for_each(mset, (ROperate)sort_back, &iter);
  roy_mset_delete(mset, NULL, NULL);
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
                   ROperate   operate,
                   void     * user_data) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    operate(iter->data, user_data);
  }
}

void roy_slist_for_which(RoySList   * slist,
                         RCondition   condition,
                         ROperate     operate,
                         void       * user_data) {
  for (RoySList * iter = roy_slist_begin(slist); iter; iter = iter->next) {
    if (condition(iter->data)) {
      operate(iter->data, user_data);
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
            ROperate   deleter,
            void     * user_data) {
  if (deleter) {
    deleter(slist->data, user_data);
  }
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

static void
sort_back(void     *  data,
          RoySList ** iter) {
  (*iter)->data = data;
  (*iter) = (*iter)->next;
}
