#include "royinit.h"

struct RoyPair_ {
  void * key;
  void * value;
};

typedef struct RoyPair_ RoyPair;

RoyPair * roy_pair_new(void * key, void * value);
void * roy_pair_value(RoyPair * pair);
