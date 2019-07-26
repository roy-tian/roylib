#include "../include/royset.h"
#include "../include/roymset.h"

static RoyMSet * node_new(const void * key, size_t key_size);
static void      node_delete(RoyMSet * mset);

RoyMSet *
roy_mset_min(RoyMSet *mset) {
  return ROY_MSET(roy_set_min(ROY_SET(mset)));
}

RoyMSet *
roy_mset_max(RoyMSet *mset) {
  return ROY_MSET(roy_set_max(ROY_SET(mset)));
}

const RoyMSet *
roy_mset_const_min(const RoyMSet *mset) {
  return ROY_MSET(roy_set_const_min(ROY_SET(mset)));
}

const RoyMSet *
roy_mset_const_max(const RoyMSet *mset) {
  return ROY_MSET(roy_set_const_max(ROY_SET(mset)));
}

size_t
roy_mset_size(const RoyMSet * mset) {
  return roy_set_size(ROY_SET(mset));
}

bool roy_mset_empty(const RoyMSet * mset) {
  return roy_set_empty(ROY_SET(mset));
}

RoyMSet *
roy_mset_insert(RoyMSet    ** mset,
                const void *  key,
                size_t        key_size,
                int       (*  comp)(const void *, const void *)) {
  if (!*mset) {
    *mset = node_new(key, key_size);
  } else if (comp(key, (*mset)->key) == 1) {
    (*mset)->right = roy_mset_insert(&(*mset)->right, key, key_size, comp);
  } else {
    (*mset)->left = roy_mset_insert(&(*mset)->left, key, key_size, comp);
  }
  return *mset;
}

RoyMSet *
roy_mset_erase(RoyMSet    ** mset,
               const void *  key,
               size_t        key_size,
               int       (*  comp)(const void *, const void *)) {
  if (!*mset) {
    return NULL;
  }
  if (comp((*mset)->key, key) == -1) {
    (*mset)->left = roy_mset_erase(&(*mset)->left, key, key_size, comp);
  } else
  if (comp((*mset)->key, key) == 1) {
    (*mset)->right = roy_mset_erase(&(*mset)->right, key, key_size, comp);
  } else /* ((*mset)->key == key), match found */ {
    RoyMSet * temp = (*mset);
    if ((*mset)->left && (*mset)->right) {
      memcpy((*mset)->key, roy_mset_const_min((*mset)->right)->key, key_size);
      (*mset)->right = roy_mset_erase(mset, key, key_size, comp);
    } else
    if ((*mset)->left && !(*mset)->right) {
      *mset = (*mset)->left;
      node_delete(temp);
    } else  { // !(*mset)->left && (*mset)->right || !(*mset)->left && !(*mset)->right
      *mset = (*mset)->right;
      node_delete(temp);
    }
  }
  return *mset;
}

RoyMSet * roy_mset_clear(RoyMSet * mset) {
  return ROY_MSET(roy_set_clear(ROY_SET(mset)));
}

// TODO
size_t roy_mset_count(const RoyMSet * mset, const void * key, RoyCompare comp) {
  return 0;
}

// TODO
RoyMSet * roy_mset_lower_bound(const RoyMSet * mset, const void * key, RoyCompare comp) {
  return NULL;
}

// TODO
RoyMSet * roy_mset_upper_bound(const RoyMSet * mset, const void * key, RoyCompare comp) {
  return NULL;
}


void roy_mset_for_each(RoyMSet * mset, RoyOperate operate) {
  roy_set_for_each(ROY_SET(mset), operate);
}

void roy_mset_for_which(RoyMSet * mset, RoyCondition condition, RoyOperate operate) {
  roy_set_for_which(ROY_SET(mset), condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static RoyMSet *
node_new(const void * key,
         size_t       key_size) {
  RoyMSet * ret = ROY_MSET(malloc(sizeof(RoyMSet)));
  ret->left     = NULL;
  ret->right    = NULL;
  ret->key      = malloc(key_size);
  memcpy(ret->key, key, key_size);
  return ret;
}

static void
node_delete(RoyMSet * mset) {
  free(mset->key);
  free(mset);
}