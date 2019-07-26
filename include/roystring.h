#ifndef ROYSTRING_H
#define ROYSTRING_H

#include "royinit.h"

struct _RoyString {
  char * str;
};

// RoyString: stores and manipulates sequences of chars, offering common string operations.
typedef struct _RoyString RoyString;

/* CONSTRUCTION AND DESTRUCTION */

RoyString * roy_string_new(void);

RoyString * roy_string_new_with_content(const char * str);

RoyString * roy_string_assign(RoyString * string, const char * str);

void roy_string_delete(RoyString * string);

/* CHARACTER ACCESS */

int roy_string_at(const RoyString * string, int index);

char * roy_string_str(RoyString * string);

const char * roy_string_cstr(const RoyString * string);

/* CAPACITY */

bool roy_string_empty(const RoyString * string);

size_t roy_string_size(const RoyString * string);

/* OPERATIONS */

RoyString * roy_string_clear(RoyString * string);

RoyString * roy_string_insert_str(RoyString * string, const char * substr, int index);

RoyString * roy_string_insert(RoyString * string, const RoyString * substring, int index);

RoyString * roy_string_erase(RoyString * string, int index, size_t count);

RoyString * roy_string_append_str(RoyString * string, const char * substr);

RoyString * roy_string_append(RoyString * string, const RoyString * substring);

RoyString * roy_string_replace_str(RoyString * string, const char * substr, int index, size_t count);

RoyString * roy_string_replace(RoyString * string, const RoyString * substr, int index, size_t count);

RoyString * roy_string_substring(RoyString * string, RoyString * substring, int index, size_t count);

/* SEARCH */

int roy_string_find_str(RoyString * string, const char * substr, int index);

int roy_string_find(RoyString * string, const RoyString * substr, int index);

int roy_string_find_regex(RoyString * string, const char * regex);

bool * roy_string_match(RoyString * string, const char * regex);

#endif // ROYSTRING_H