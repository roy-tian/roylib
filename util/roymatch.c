#define PCRE2_CODE_UNIT_WIDTH 8

#include "roymatch.h"
#include <pcre2.h>

RoyMatch *
roy_match_new(int begin, int end, int type) {
  RoyMatch * ret = malloc(sizeof(RoyMatch));
  ret->begin = begin;
  ret->end   = end;
  ret->type  = type;
  return ret;
}

RoyMatch *
roy_match_new_default(void) {
  return roy_match_new(PCRE2_ERROR_NOMATCH, PCRE2_ERROR_NOMATCH, 0);
}

RoyMatch *
roy_match_copy(const RoyMatch * another) {
  return roy_match_new(another->begin, another->end, another->type);
}

void
roy_match_delete(RoyMatch * match) {
  free(match);
}

RoyMatch
roy_match_make(int begin, int end, int type) {
  RoyMatch ret = { begin, end, type };
  return ret;
}

RoyMatch
roy_match_make_default(void) {
  return roy_match_make(PCRE2_ERROR_NOMATCH, PCRE2_ERROR_NOMATCH, 0);
}


void
roy_match_set(RoyMatch * restrict match, int begin, int end, int type) {
  match->begin = begin;
  match->end   = end;
  match->type  = type;
}

void
roy_match_set_default(RoyMatch * restrict match) {
  roy_match_set(match, PCRE2_ERROR_NOMATCH, PCRE2_ERROR_NOMATCH, 0);
}

bool
roy_match_default(const RoyMatch * match) {
  return match->begin == PCRE2_ERROR_NOMATCH &&
         match->end   == PCRE2_ERROR_NOMATCH &&
         match->type  == 0;
}
