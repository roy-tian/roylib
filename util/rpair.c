#include "rpair.h"

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

RoyCPair *
roy_cpair_new(const void * key,
              const void * value) {
  RoyCPair * ret = malloc(sizeof(RoyCPair));
  ret->key       = key;
  ret->value     = value;
  return ret;
}

const void *
roy_cpair_key(RoyCPair * pair) {
  return pair ? pair->key : NULL;
}

const void *
roy_cpair_value(RoyCPair * pair) {
  return pair ? pair->value : NULL;
}
