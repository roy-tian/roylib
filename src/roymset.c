#include "royset.h"
#include "roymset.h"

static RoyMSet * node_new(void * key);

RoyMSet *
roy_mset_new(void) {
  return (RoyMSet *)roy_set_new();
}

void
roy_mset_delete(RoyMSet * mset,
                ROperate deleter) {
  roy_set_delete((RoySet *)mset, deleter);
}


RoyMSet *
roy_mset_min(RoyMSet * mset) {
  return (RoyMSet *)roy_set_min((RoySet *)mset);
}

RoyMSet *
roy_mset_max(RoyMSet * mset) {
  return (RoyMSet *)roy_set_max((RoySet *)mset);
}

const RoyMSet *
roy_mset_cmin(const RoyMSet * mset) {
  return (RoyMSet *)roy_set_cmin((RoySet *) mset);
}

const RoyMSet *
roy_mset_cmax(const RoyMSet * mset) {
  return (RoyMSet *)roy_set_cmax((RoySet *) mset);
}

size_t
roy_mset_size(const RoyMSet * mset) {
  return roy_set_size((RoySet *)mset);
}

bool roy_mset_empty(const RoyMSet * mset) {
  return roy_set_empty((RoySet *)mset);
}

RoyMSet *
roy_mset_insert(RoyMSet  ** mset,
                void     *  key,
                RCompare    comparer) {
  if (!*mset) {
    *mset = node_new(key);
  } else if (comparer(key, (*mset)->key) > 0) {
    (*mset)->right = roy_mset_insert(&(*mset)->right, key, comparer);
  } else {
    (*mset)->left = roy_mset_insert(&(*mset)->left, key, comparer);
  }
  return * mset;
}

RoyMSet *
roy_mset_remove(RoyMSet    ** mset,
                const void *  key,
                RCompare      comparer,
                ROperate      deleter) {
  while (roy_mset_find(*mset, key, comparer)) {
    roy_set_remove((RoySet **)mset, key, comparer, deleter);
  }
  return *mset;
}

void
roy_mset_clear(RoyMSet * mset, ROperate deleter) {
  roy_set_clear((RoySet *)mset, deleter);
}

size_t
roy_mset_count(const RoyMSet * mset,
               const void    * key,
               RCompare        comparer) {
  if (!mset) {
    return 0;
  } else {
    return (comparer(key, mset->key) == 0 ? 1 : 0) +
           roy_mset_count(mset->left, key, comparer) +
           roy_mset_count(mset->right, key, comparer);
  }
}

RoyMSet *
roy_mset_find(const RoyMSet * mset,
              const void    * key,
              RCompare        comparer) {
  return (RoyMSet *)roy_set_find((RoySet *)mset, key, comparer);
}

void
roy_mset_for_each(RoyMSet * mset,
                  ROperate  operate) {
  roy_set_for_each((RoySet *)mset, operate);
}

void
roy_mset_for_which(RoyMSet    * mset,
                   RCondition   condition,
                   ROperate     operate) {
  roy_set_for_which((RoySet *)mset, condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static RoyMSet *
node_new(void * key) {
  RoyMSet * ret = (RoyMSet *)malloc(sizeof(RoyMSet));
  ret->left     = NULL;
  ret->right    = NULL;
  ret->key      = key;
  return ret;
}
