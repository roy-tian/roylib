#include "roypair.h"

RoyPair *
roy_pair_new(void * key,
             void * value) {
  RoyPair * ret = (RoyPair *)malloc(sizeof(RoyPair));
  ret->key      = key;
  ret->value    = value;
  return ret;
}

void *
roy_pair_value(RoyPair * pair) {
  return pair ? pair->value : NULL;
}
