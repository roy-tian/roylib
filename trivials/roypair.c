#include "roypair.h"

RoyPair *
roy_pair_new(void * key,
             void * value) {
  RoyPair * ret = malloc(sizeof(RoyPair));
  ret->key      = key;
  ret->value    = value;
  return ret;
}

void *
roy_pair_key(RoyPair * pair) {
  return pair ? pair->key : NULL;
}

void *
roy_pair_value(RoyPair * pair) {
  return pair ? pair->value : NULL;
}
