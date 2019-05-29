#include "../include/royset.h"

static RoySet * node_new(const void * key, size_t key_size);
static void     node_delete(RoySet * set);

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
  if (!set) {
    set = node_new(key, key_size);
  } else if (comp(set->key, key) == -1) {
    set->left = roy_set_insert(set, key, key_size, comp);
  } else if (comp(set->key, key) == 1) {
    set->right = roy_set_insert(set, key, key_size, comp);
  } // if (set->key == key) does nothing
  return set;
}

RoySet *
roy_set_erase(RoySet     * set,
              const void * key,
              size_t       key_size,
              int       (* comp)(const void *, const void *)) {
  if (!set) {
    return NULL;
  }
  if (comp(set->key, key) == -1) {
    set->left = roy_set_erase(set->left, key, key_size, comp);
  } else if (comp(set->key, key) == 1) {
    set->right = roy_set_erase(set->right, key, key_size, comp);
  } else /* (set->key == key) match found */ {
    RoySet * temp = set;
    if (set->left && set->right) {
      memcpy(set->key, roy_set_const_min(set->right)->key, key_size);
      set->right = roy_set_erase(set, key, key_size, comp);
    } else if (set->left && !set->right) {
      set = set->left;
      node_delete(temp);
    } else /* (!set->left && set->right || !set->left && !set->right) */ {
      set = set->right;
      node_delete(temp);
    }
  }
  return set;
}

RoySet * roy_set_clear(RoySet * set) {
  if (set) {
    roy_set_clear(set->left);
    roy_set_clear(set->right);
    node_delete(set);
  }
  return NULL;
}

void roy_set_for_each(RoySet * set, void(* iterate)(void *));

void roy_set_for_which(RoySet * set, bool(* condition)(const void *), void(* iterate)(void *)) {
  if (set) {
    roy_set_for_which(set->left, condition, iterate);
    if (condition(set->key)) {
      iterate(set->key);
    }
    roy_set_for_which(set->right, condition, iterate);
  }
}

/* PRIVATE FUNCTIONS BELOW */

static RoySet *
node_new(const void * key,
         size_t       key_size) {
  RoySet * ret = malloc(sizeof(RoySet));
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