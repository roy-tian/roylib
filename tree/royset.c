#include "royset.h"

static RoySet * node_new(void * key);
static void     node_delete(RoySet * set, RDoer deleter, void * user_data);

RoySet *
roy_set_new(void) {
  return NULL;
}

void
roy_set_delete(RoySet * set,
               RDoer    deleter,
               void   * user_data) {
  roy_set_clear(set, deleter, user_data);
}

RoySet *
roy_set_min(RoySet * set) {
  if (!set) {
    return NULL;
  } else if (!set->left) {
    return set;
  } else {
    return roy_set_min(set->left);
  }
}

RoySet *
roy_set_max(RoySet * set) {
  if (!set) {
    return NULL;
  } else if (!set->right) {
    return set;
  } else {
    return roy_set_max(set->right);
  }
}

const RoySet *
roy_set_cmin(const RoySet * set) {
  if (!set) {
    return NULL;
  } else if (!set->left) {
    return set;
  } else {
    return roy_set_cmin(set->left);
  }
}

const RoySet *
roy_set_cmax(const RoySet * set) {
  if (!set) {
    return NULL;
  } else if (!set->right) {
    return set;
  } else {
    return roy_set_cmax(set->right);
  }
}

size_t
roy_set_size(const RoySet * set) {
  if (!set) {
    return 0;
  } else {
    return 1 + roy_set_size(set->left) + roy_set_size(set->right);
  }
}

bool
roy_set_empty(const RoySet * set) {
  return set == NULL;
}

RoySet *
roy_set_insert(RoySet    ** restrict set,
               void      *  restrict key,
               RComparer    comparer) {
  if (!*set) {
    *set = node_new(key);
  } else if (comparer(key, (*set)->key) < 0) {
    (*set)->left = roy_set_insert(&(*set)->left, key, comparer);
  } else if (comparer(key, (*set)->key) > 0) {
    (*set)->right = roy_set_insert(&(*set)->right, key, comparer);
  } // if (set->key == key) does nothing
  return *set;
}

RoySet *
roy_set_remove(RoySet     ** set,
               const void *  key,
               RComparer     comparer,
               RDoer         deleter,
               void       *  user_data) {
  if (!*set) {
    return NULL;
  }
  if (comparer(key, (*set)->key) < 0) {
    (*set)->left =
            roy_set_remove(&(*set)->left, key, comparer, deleter, user_data);
  } else if (comparer(key, (*set)->key) > 0) {
    (*set)->right =
            roy_set_remove(&(*set)->right, key, comparer, deleter, user_data);
  } else /* ((*set)->key == key), match found */ {
    RoySet * temp = (*set);
    if ((*set)->left && (*set)->right) {
      (*set)->key = roy_set_cmin((*set)->right)->key;
      (*set)->right = roy_set_remove(set, key, comparer, deleter, user_data);
    } else
    if ((*set)->left && !(*set)->right) {
      *set = (*set)->left;
      node_delete(temp, deleter, user_data);
    } else  { // !(*set)->left && (*set)->right || !(*set)->left && !(*set)->right
      *set = (*set)->right;
      node_delete(temp, deleter, user_data);
    }
  }
  return *set;
}

void
roy_set_clear(RoySet * set,
              RDoer    deleter,
              void   * user_data) {
  if (set) {
    roy_set_clear(set->right, deleter, user_data);
    roy_set_clear(set->left, deleter, user_data);
    node_delete(set, deleter, user_data);
  }
}

RoySet *
roy_set_find(RoySet     * set,
             const void * key, 
             RComparer    comparer) {
  if (!set) {
    return NULL;
  } else if (comparer(key, set->key) < 0) {
    return roy_set_find(set->left, key, comparer);
  } else if (comparer(key, set->key) > 0) {
    return roy_set_find(set->right, key, comparer);
  } else {
    return set;
  }
}

void
roy_set_for_each(RoySet * set,
                 RDoer    doer,
                 void   * user_data) {
  if (set) {
    roy_set_for_each(set->left, doer, user_data);
    doer(set->key, user_data);
    roy_set_for_each(set->right, doer, user_data);
  }
}

void
roy_set_for_which(RoySet   * set,
                  RChecker   checker,
                  RDoer      doer,
                  void     * user_data) {
  if (set) {
    roy_set_for_which(set->left, checker, doer, user_data);
    if (checker(set->key)) {
      doer(set->key, user_data);
    }
    roy_set_for_which(set->right, checker, doer, user_data);
  }
}

/* PRIVATE FUNCTIONS BELOW */

static RoySet *
node_new(void * key) {
  RoySet * ret = malloc(sizeof(RoySet));
  ret->left    = NULL;
  ret->right   = NULL;
  ret->key     = key;
  return ret;
}

static void
node_delete(RoySet * set,
            RDoer    deleter,
            void   * user_data) {
  if (deleter) {
    deleter(set->key, user_data);
  }
  free(set);
  set = NULL;
}