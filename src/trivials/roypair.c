#include "roypair.h"

RoyPair *
pair_new(void * key,
         void * value) {
  RoyPair * ret = (RoyPair *)malloc(sizeof(RoyPair));
  ret->key      = key;
  ret->value    = value;
  return ret;
}

void *
pair_value(RoyPair * pair) {
  return pair->value;
}
