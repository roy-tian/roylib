#ifndef ROYMATCH_H
#define ROYMATCH_H

#include "royinit.h"

typedef struct RoyMatch_ {
  int begin;
  int end;
  int type;
} RoyMatch;

RoyMatch * roy_match_new(int begin, int end, int type);

RoyMatch * roy_match_new_default(void);

RoyMatch * roy_match_copy(const RoyMatch * another);

void roy_match_delete(RoyMatch * match);

RoyMatch roy_match_make(int begin, int end, int type);

RoyMatch roy_match_make_default(void);

void roy_match_set(RoyMatch * restrict match, int begin, int end, int type);

void roy_match_set_default(RoyMatch * restrict match);

bool roy_match_default(const RoyMatch * match);

#endif //ROYMATCH_H
