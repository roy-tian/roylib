#include "royset.h"
#include "roymset.h"

static RoyMSet * node_new(const void * key, size_t key_size);
static void      node_delete(RoyMSet * mset);

RoyMSet *
roy_mset_min(RoyMSet *mset) {
  return (RoyMSet *)roy_set_min((RoySet *)mset);
}

RoyMSet *
roy_mset_max(RoyMSet *mset) {
  return (RoyMSet *)roy_set_max((RoySet *)mset);
}

const RoyMSet *
roy_mset_const_min(const RoyMSet *mset) {
  return (RoyMSet *)roy_set_const_min((RoySet *)mset);
}

const RoyMSet *
roy_mset_const_max(const RoyMSet *mset) {
  return (RoyMSet *)roy_set_const_max((RoySet *)mset);
}

size_t
roy_mset_size(const RoyMSet * mset) {
  return roy_set_size((RoySet *)mset);
}

bool roy_mset_empty(const RoyMSet * mset) {
  return roy_set_empty((RoySet *)mset);
}

RoyMSet *
roy_mset_insert(RoyMSet    ** mset,
                const void *  key,
                size_t     key_size,
                int       (*  compare)(const void *, const void *)) {
  if (!*mset) {
    *mset = node_new(key, key_size);
  } else if (compare(key, (*mset)->key) == 1) {
    (*mset)->right = roy_mset_insert(&(*mset)->right, key, key_size, compare);
  } else {
    (*mset)->left = roy_mset_insert(&(*mset)->left, key, key_size, compare);
  }
  return *mset;
}

RoyMSet *
roy_mset_erase(RoyMSet    ** mset,
               const void *  key,
               size_t     key_size,
               int       (*  compare)(const void *, const void *)) {
  if (!*mset) {
    return NULL;
  }
  if (compare((*mset)->key, key) == -1) {
    (*mset)->left = roy_mset_erase(&(*mset)->left, key, key_size, compare);
  } else
  if (compare((*mset)->key, key) == 1) {
    (*mset)->right = roy_mset_erase(&(*mset)->right, key, key_size, compare);
  } else /* ((*mset)->key == key), match found */ {
    RoyMSet * temp = (*mset);
    if ((*mset)->left && (*mset)->right) {
      memcpy((*mset)->key, roy_mset_const_min((*mset)->right)->key, key_size);
      (*mset)->right = roy_mset_erase(mset, key, key_size, compare);
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

RoyMSet *
roy_mset_clear(RoyMSet * mset) {
  return (RoyMSet *)roy_set_clear((RoySet *)mset);
}

// TODO
size_t
roy_mset_count(const RoyMSet * mset,
               const void    * key,
               int          (* compare)(const void *, const void *)) {
  return 0;
}

// TODO
RoyMSet *
roy_mset_lower_bound(const RoyMSet * mset,
                     const void    * key,
                     int          (* compare)(const void *, const void *)) {
  return NULL;
}

// TODO
RoyMSet *
roy_mset_upper_bound(const RoyMSet * mset,
                     const void    * key,
                     int          (* compare)(const void *, const void *)) {
  return NULL;
}


void
roy_mset_for_each(RoyMSet * mset,
                  void   (* operate)(void *)) {
  roy_set_for_each((RoySet *)mset, operate);
}

void
roy_mset_for_which(RoyMSet * mset,
                   bool   (* condition)(const void *),
                   void   (* operate)        (void *)) {
  roy_set_for_which((RoySet *)mset, condition, operate);
}

/* PRIVATE FUNCTIONS BELOW */

static RoyMSet *
node_new(const void * key,
         size_t    key_size) {
  RoyMSet * ret = (RoyMSet *)malloc(sizeof(RoyMSet));
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