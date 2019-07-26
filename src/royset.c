#include "../include/royset.h"

static RoySet * node_new(const void * key, size_t key_size);
static void     node_delete(RoySet * set);

RoySet *
roy_set_min(RoySet *set) {
  if (!set) {
    return NULL;
  } else if (!set->left) {
    return set;
  } else {
    return roy_set_min(set->left);
  }
}

RoySet *
roy_set_max(RoySet *set) {
  if (!set) {
    return NULL;
  } else if (!set->right) {
    return set;
  } else {
    return roy_set_max(set->right);
  }
}

const RoySet *
roy_set_const_min(const RoySet *set) {
  if (!set) {
    return NULL;
  } else if (!set->left) {
    return set;
  } else {
    return roy_set_const_min(set->left);
  }
}

const RoySet *
roy_set_const_max(const RoySet *set) {
  if (!set) {
    return NULL;
  } else if (!set->right) {
    return set;
  } else {
    return roy_set_const_max(set->right);
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

bool roy_set_empty(const RoySet * set) {
  return set == NULL;
}

RoySet *
roy_set_insert(RoySet     ** set,
               const void *  key,
               size_t        key_size,
               int       (*  comp)(const void *, const void *)) {
  if (!*set) {
    *set = node_new(key, key_size);
  } else if (comp(key, (*set)->key) < 0) {
    (*set)->left = roy_set_insert(&(*set)->left, key, key_size, comp);
  } else if (comp(key, (*set)->key) > 0) {
    (*set)->right = roy_set_insert(&(*set)->right, key, key_size, comp);
  } // if (set->key == key) does nothing
  return *set;
}

RoySet *
roy_set_erase(RoySet     ** set,
              const void *  key,
              size_t        key_size,
              int       (*  comp)(const void *, const void *)) {
  if (!*set) {
    return NULL;
  }
  if (comp(key, (*set)->key) < 0) {
    (*set)->left =  roy_set_erase(&(*set)->left, key, key_size, comp);
  } else
  if (comp(key, (*set)->key) > 0) {
    (*set)->right = roy_set_erase(&(*set)->right, key, key_size, comp);
  } else /* ((*set)->key == key), match found */ {
    RoySet * temp = (*set);
    if ((*set)->left && (*set)->right) {
      memcpy((*set)->key, roy_set_const_min((*set)->right)->key, key_size);
      (*set)->right = roy_set_erase(set, key, key_size, comp);
    } else
    if ((*set)->left && !(*set)->right) {
      *set = (*set)->left;
      node_delete(temp);
    } else  { // !(*set)->left && (*set)->right || !(*set)->left && !(*set)->right
      *set = (*set)->right;
      node_delete(temp);
    }
  }
  return *set;
}

RoySet * roy_set_clear(RoySet * set) {
  if (set) {
    roy_set_clear(set->left);
    roy_set_clear(set->right);
    node_delete(set);
  }
  return NULL;
}

RoySet * roy_set_find(RoySet * set, const void * key, RoyCompare comp) {
  if (!set) {
    return NULL;
  } else if (comp(key, set->key) < 0) {
    return roy_set_find(set->left, key, comp);
  } else if (comp(key, set->key) > 0) {
    return roy_set_find(set->right, key, comp);
  } else {
    return set;
  }
}

void roy_set_for_each(RoySet * set, RoyOperate operate) {
   if (set) {
    roy_set_for_each(set->left, operate);
    operate(set->key);
    roy_set_for_each(set->right, operate);
  }
}

void roy_set_for_which(RoySet * set, RoyCondition condition, RoyOperate operate) {
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
node_new(const void * key,
         size_t       key_size) {
  RoySet * ret = ROY_SET(malloc(sizeof(RoySet)));
  ret->left    = NULL;
  ret->right   = NULL;
  ret->key     = malloc(key_size);
  memcpy(ret->key, key, key_size);
  return ret;
}

static void
node_delete(RoySet * set) {
  free(set->key);
  free(set);
}