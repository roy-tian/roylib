#include "roystring.h"
#include <pcre.h>

RoyString *
roy_string_new(void) {
  RoyString * ret = (RoyString *)malloc(sizeof(RoyString));
  assert(ret != NULL);
  ret->str = NULL;
  return ret;
}

RoyString *
roy_string_new_with_content(const char * str) {
  return roy_string_assign(roy_string_new(), str);
}

void
roy_string_delete(RoyString * string) {
  free(string->str);
  free(string);
}

RoyString *
roy_string_assign(RoyString  * string,
                  const char * str) {
  assert(string != NULL);
  string->str = (char *)realloc(string->str, strlen(str) + 1);
  memcpy(string->str, str, strlen(str) + 1);
  return string;
}

/* CHARACTER ACCESS */

int
roy_string_at(const RoyString * string,
              size_t            position) {
  assert(string != NULL);
  assert(position < roy_string_size(string));
  return (int)*(string->str + position);
}

char *
roy_string_str(RoyString * string) {
  assert(string != NULL);
  return string->str;
}

const char *
roy_string_cstr(const RoyString * string) {
  assert(string != NULL);
  return string->str;
}

/* CAPACITY */

bool
roy_string_empty(const RoyString * string) {
  assert(string != NULL);
  return roy_string_at(string, 0) == '\0';
}

size_t
roy_string_size(const RoyString * string) {
  assert(string != NULL);
  return strlen(string->str);
}

/* OPERATIONS */

RoyString *
roy_string_clear(RoyString * string) {
  assert(string != NULL);
  return string = roy_string_assign(string, "");
}

RoyString *
roy_string_insert_str(RoyString  * string,
                      const char * substr,
                      size_t position) {
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
  memcpy(temp, string->str, position);
  strcat(temp, substr);
  strncat(temp, string->str + position, roy_string_size(string) - position);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_insert(RoyString       * string,
                  const RoyString * substring,
                  size_t            position) {
  assert(string != NULL);
  assert(substring != NULL);
  assert(position < roy_string_size(string));
  return roy_string_insert_str(string, roy_string_cstr(substring), position);
}

RoyString *
roy_string_erase(RoyString * string,
                 size_t      position,
                 size_t      count) {
  assert(string);
  assert(position + count < roy_string_size(string));
  ROY_STR(temp, roy_string_size(string) - count + 1)
  memcpy(temp, string->str, position);
  strncat(temp, string->str + position + count,
          roy_string_size(string) - position - count);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_append_str(RoyString  * string,
                      const char * substr) {
  assert(string != NULL);
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1);
  memcpy(temp, string->str, roy_string_size(string) + 1);
  strcat(temp, substr);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_append(RoyString       * string,
                  const RoyString * substring) {
  assert(string != NULL);
  return roy_string_append_str(string, roy_string_cstr(substring));
}

RoyString *
roy_string_replace_str(RoyString  * string,
                       const char * substr,
                       size_t       position,
                       size_t       count) {
  assert(string != NULL);
  assert(position + count < roy_string_size(string));
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
  strncpy(temp, string->str, position);
  strcat(temp, substr);
  strcat(temp, string->str + position + count);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_replace(RoyString       * string,
                   const RoyString * substring,
                   size_t            position,
                   size_t            count) {
  assert(string != NULL);
  assert(position + count < roy_string_size(string));
  return roy_string_replace_str(string,
                                roy_string_cstr(substring),
                                position,
                                count);
}

RoyString *
roy_string_substring(RoyString * string,
                     RoyString * substring,
                     size_t      position,
                     size_t      count) {
  assert(string != NULL);
  assert(position + count < roy_string_size(string));
  ROY_STR(temp, count + 1)
  strncpy(temp, string->str + position, count);
  return substring = roy_string_assign(substring, temp);
}

/* SEARCH */

int
roy_string_find_str(const RoyString  * string,
                    const char       * substr,
                    size_t             position) {
  assert(string != NULL);
  assert(position < roy_string_size(string));
  const char * begin = string->str + position;
  const char * found = strstr(string->str + position, substr);
  return found ? (int)(found - begin) : -1;
}

int
roy_string_find(const RoyString * string,
                const RoyString * substr,
                size_t            position) {
  assert(string != NULL);
  assert(position < roy_string_size(string));
  return roy_string_find_str(string, roy_string_cstr(substr), position);
}

int
roy_string_find_regex(const RoyString * string,
                      const char      * regex,
                      size_t            position) {
  assert(string != NULL);
  assert(position < roy_string_size(string));
  const char * err_info;
  int err_offset;
  pcre * re = pcre_compile(regex, 0, &err_info, &err_offset, NULL);
  pcre_extra * rex = pcre_study(re, 0, &err_info);
  enum { OVECSIZE = 30 };
  int ovector[OVECSIZE];
  int ret = -1;
  if (pcre_exec(re,
                rex,
                roy_string_cstr(string),
                roy_string_size(string),
                position,
                0,
                ovector,
                OVECSIZE) != PCRE_ERROR_NOMATCH) {
  ret = ovector[0];
};
  free(re);
  free(rex);
  return ret;
}

char *
roy_string_regex(char            * dest,
                 const RoyString * string,
                 const char      * regex,
                 size_t            position) {
  assert(string != NULL);
  assert(position < roy_string_size(string));
  const char * err_info;
  int err_offset;
  pcre * re = pcre_compile(regex, 0, &err_info, &err_offset, NULL);
  pcre_extra * rex = pcre_study(re, 0, &err_info);
  enum { OVECSIZE = 30 };
  int ovector[OVECSIZE];
  int ret = PCRE_ERROR_NOMATCH;
  if (pcre_exec(re,
                rex,
                roy_string_cstr(string),
                roy_string_size(string),
                position,
                0,
                ovector,
                OVECSIZE) != PCRE_ERROR_NOMATCH) {
  strncpy(dest, roy_string_cstr(string) + ovector[0], ovector[1] - ovector[0]);
  *(dest + strlen(dest)) = '\0';
};
  free(re);
  free(rex);
  return dest;
}


bool
roy_string_match(const RoyString * string,
                 const char      * regex) {
  assert(string != NULL);
  ROY_STR(re, strlen(regex) + 2)
  *re = '^';
  strcat(re, regex);
  strcat(re, "$");
  return roy_string_find_regex(string, re, 0) == 0;
}