#ifndef ROYPAIR_H
#define ROYPAIR_H

#include "royinit.h"

struct RoyPair_ {
  void * key;
  void * value;
};

typedef struct RoyPair_ RoyPair;

RoyPair * roy_pair_new(void * key, void * value);
void * roy_pair_key(RoyPair * pair);
void * roy_pair_value(RoyPair * pair);


struct RoyCPair_ {
  const void * key;
  const void * value;
};

typedef struct RoyCPair_ RoyCPair;

RoyCPair * roy_cpair_new(const void * key, const void * value);
const void * roy_cpair_key(RoyCPair * pair);
const void * roy_cpair_value(RoyCPair * pair);

#endif // ROYPAIR_H
