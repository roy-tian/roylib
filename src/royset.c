#include "royset.h"

static RoySet * node_new(void * key);
static void     node_delete(RoySet * set, ROperate deleter);

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
roy_set_insert(RoySet   ** set,
               void     *  key,
               RCompare    comparer) {
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
roy_set_erase(RoySet     ** set,
              const void *  key,
              RCompare      comparer,
              ROperate      deleter) {
  if (!*set) {
    return NULL;
  }
  if (comparer(key, (*set)->key) < 0) {
    (*set)->left =  roy_set_erase(&(*set)->left, key, comparer, deleter);
  } else if (comparer(key, (*set)->key) > 0) {
    (*set)->right = roy_set_erase(&(*set)->right, key, comparer, deleter);
  } else /* ((*set)->key == key), match found */ {
    RoySet * temp = (*set);
    if ((*set)->left && (*set)->right) {
      (*set)->key = roy_set_cmin((*set)->right)->key;
      (*set)->right = roy_set_erase(set, key, comparer, deleter);
    } else
    if ((*set)->left && !(*set)->right) {
      *set = (*set)->left;
      node_delete(temp, deleter);
    } else  { // !(*set)->left && (*set)->right || !(*set)->left && !(*set)->right
      *set = (*set)->right;
      node_delete(temp, deleter);
    }
  }
  return *set;
}

void
roy_set_clear(RoySet   * set,
              ROperate   deleter) {
  if (set) {
    roy_set_clear(set->left, deleter);
    roy_set_clear(set->right, deleter);
    node_delete(set, deleter);
  }
}

RoySet *
roy_set_find(RoySet     * set,
             const void * key, 
             RCompare     comparer) {
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
roy_set_for_each(RoySet   * set,
                 ROperate   operate) {
  if (set) {
    roy_set_for_each(set->left, operate);
    operate(set->key);
    roy_set_for_each(set->right, operate);
  }
}

void
roy_set_for_which(RoySet     * set,
                  RCondition   condition,
                  ROperate     operate) {
  if (set) {
    roy_set_for_which(set->left, condition, operate);
    if (condition(set->key)) {
      operate(set->key);
    }
    roy_set_for_which(set->right, condition, operate);
  }
}

/* PRIVATE FUNCTIONS BELOW */

static RoySet *
node_new(void * key) {
  RoySet * ret = (RoySet *)malloc(sizeof(RoySet));
  ret->left    = NULL;
  ret->right   = NULL;
  ret->key     = key;
  return ret;
}

static void
node_delete(RoySet   * set,
            ROperate   deleter) {
  deleter(set->key);
  free(set);
  set = NULL;
}