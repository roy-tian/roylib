#include "../include/royset.h"

static RoySet * node_modify(RoySet * set, const void * key, size_t key_size);

RoySet *
roy_set_new(void) {
  RoySet * ret = malloc(sizeof(RoySet));
  ret->left  = NULL;
  ret->right = NULL;
  ret->key   = NULL;
  return ret;
}

void roy_set_delete(RoySet * set);

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
  if (set) {
    while (set->right) {
      set = set->right;
    }
    return set;
  } else {
    return NULL;
  }
}

const RoySet *
roy_set_const_min(const RoySet * set) {
  if (set) {
    while (set->left) {
      set = set->left;
    }
    return set;
  } else {
    return NULL;
  }
}

const RoySet *
roy_set_const_max(const RoySet * set) {
  if (!set) {
    return NULL;
  } else if (!set->right) {
    return set;
  } else {
    return roy_set_const_max(set);
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
  return set->key == NULL;
}

RoySet *
roy_set_insert(RoySet     * set,
               const void * key,
               size_t       key_size,
               int       (* comp)(const void *, const void *)) {
  
}

RoySet * roy_set_erase(RoySet * set, const void * key, size_t key_size);

RoySet * roy_set_clear(RoySet * set);

void roy_set_for_each(RoySet * set, void(* iterate)(void *));

void roy_set_for_which(RoySet * set, bool(* condition)(const void *), void(* iterate)(void *));

/* PRIVATE FUNCTIONS BELOW */

static RoySet *
node_modify(RoySet     * set,
            const void * key,
            size_t       key_size) {
  set->key = malloc(key_size);
  memcpy(set->key, key, key_size);
  return set;
}