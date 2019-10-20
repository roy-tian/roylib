#ifndef ROYSTRING_H
#define ROYSTRING_H


#include "royinit.h"

struct RoyString_ {
  char * str;
};

// RoyString: stores and manipulates sequences of chars, offering common string operations.
typedef struct RoyString_ RoyString;

/* CONSTRUCTION AND DESTRUCTION */

RoyString * roy_string_new(void);

RoyString * roy_string_new_with_content(const char * str);

RoyString * roy_string_assign(RoyString * string, const char * str);

void roy_string_delete(RoyString * string);

/* CHARACTER ACCESS */

int roy_string_at(const RoyString * string, size_t position);

char * roy_string_str(RoyString * string);

const char * roy_string_cstr(const RoyString * string);

/* CAPACITY */

bool roy_string_empty(const RoyString * string);

size_t roy_string_size(const RoyString * string);

/* OPERATIONS */

RoyString * roy_string_clear(RoyString * string);

RoyString * roy_string_insert_str(RoyString * string, const char * substr, size_t position);

RoyString * roy_string_insert(RoyString * string, const RoyString * substring, size_t position);

RoyString * roy_string_erase(RoyString * string, size_t position, size_t count);

RoyString * roy_string_prepend_str(RoyString * string, const char * substr);

RoyString * roy_string_prepend(RoyString * string, const RoyString * substring);

RoyString * roy_string_append_str(RoyString * string, const char * substr);

RoyString * roy_string_append(RoyString * string, const RoyString * substring);

RoyString * roy_string_replace_str(RoyString * string, const char * substr, size_t position, size_t count);

RoyString * roy_string_replace(RoyString * string, const RoyString * substr, size_t position, size_t count);

RoyString * roy_string_substring(RoyString * string, RoyString * substring, size_t position, size_t count);

void roy_string_print(const RoyString * string);

void roy_string_println(const RoyString * string);

/* SEARCH */

int roy_string_find_str(const RoyString * string, const char * substr, size_t position);

int roy_string_find(const RoyString * string, const RoyString * substr, size_t position);

int roy_string_find_regex(const RoyString * string, const char * regex, size_t position);

char * roy_string_regex(char * dest, const RoyString * string, const char * regex, size_t position);

bool roy_string_match(const RoyString * string, const char * regex);

bool roy_string_equal(const RoyString * string1, const RoyString * string2);

bool roy_string_equal_str(const RoyString * string, const char * str);

#endif // RoyString *_H