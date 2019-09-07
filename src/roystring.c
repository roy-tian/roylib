#include "../include/roystring.h"
#include <pcre.h>

RoyString *
roy_string_new(void) {
  RoyString * ret = (RoyString *)malloc(sizeof(RoyString));
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
  string->str = (char *)realloc(string->str, strlen(str) + 1);
  memcpy(string->str, str, strlen(str) + 1);
  return string;
}

/* CHARACTER ACCESS */

int
roy_string_at(const RoyString * string,
              int               index) {
  return (int)*(string->str + index);
}

char *
roy_string_str(RoyString * string) {
  return string->str;
}

const char *
roy_string_cstr(const RoyString * string) {
  return string->str;
}

/* CAPACITY */

bool
roy_string_empty(const RoyString * string) {
  return roy_string_at(string, 0) == '\0';
}

size_t
roy_string_size(const RoyString * string) {
  return strlen(string->str);
}

/* OPERATIONS */

RoyString *
roy_string_clear(RoyString * string) {
  return string = roy_string_assign(string, "");
}

RoyString *
roy_string_insert_str(RoyString  * string,
                      const char * substr,
                      int          index) {
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
  memcpy(temp, string->str, index);
  strcat(temp, substr);
  strncat(temp, string->str + index, roy_string_size(string) - index);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_insert(RoyString       * string,
                  const RoyString * substring,
                  int               index) {
  return
  roy_string_insert_str(string, roy_string_cstr(substring), index);
}

RoyString *
roy_string_erase(RoyString * string,
                 int         index,
                 size_t   count) {
  ROY_STR(temp, roy_string_size(string) - count + 1)
  memcpy(temp, string->str, index);
  strncat(temp, string->str + index + count,
          roy_string_size(string) - index - count);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_append_str(RoyString  * string,
                      const char * substr) {
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1);
  memcpy(temp, string->str, roy_string_size(string) + 1);
  strcat(temp, substr);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_append(RoyString       * string,
                  const RoyString * substring) {
  return roy_string_append_str(string, roy_string_cstr(substring));
}

RoyString *
roy_string_replace_str(RoyString  * string,
                       const char * substr,
                       int          index,
                       size_t    count) {
  ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
  strncpy(temp, string->str, index);
  strcat(temp, substr);
  strcat(temp, string->str + index + count);
  return string = roy_string_assign(string, temp);
}

RoyString *
roy_string_replace(RoyString       * string,
                   const RoyString * substring,
                   int               index, 
                   size_t         count) {
  return roy_string_replace_str(string,
                                roy_string_cstr(substring),
                                index,
                                count);
}

RoyString *
roy_string_substring(RoyString * string,
                     RoyString * substring,
                     int         index,
                     size_t   count) {
  ROY_STR(temp, count + 1)
  strncpy(temp, string->str + index, count);
  return substring = roy_string_assign(substring, temp);
}

/* SEARCH */

int
roy_string_find_str(const RoyString  * string,
                    const char       * substr,
                    int                index) {
  const char * begin = string->str + index;
  const char * found = strstr(string->str + index, substr);
  return found ? (int)(found - begin) : -1;
}

int
roy_string_find(const RoyString * string,
                const RoyString * substr,
                int               index) {
  return roy_string_find_str(string, roy_string_cstr(substr), index);
}

int
roy_string_find_regex(const RoyString * string,
                      const char      * regex,
                      int               index) {
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
                index,
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
                 int               index) {
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
                index,
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
  ROY_STR(re, strlen(regex) + 2)
  *re = '^';
  strcat(re, regex);
  strcat(re, "$");
  return roy_string_find_regex(string, re, 0) == 0;
}