#include "trivials/roystr.h"
#include "roystring.h"
#include <pcre.h>

static bool pos_correct(const RoyString * string, size_t position);
static bool pos_cnt_correct(const RoyString * string, size_t position, size_t count);

RoyString *
roy_string_new(const char * str) {
  RoyString * ret = (RoyString *)malloc(sizeof(RoyString));
  ret->str = (char *)calloc(strlen(str) + 1, sizeof(char));
  memcpy(ret->str, str, strlen(str) + 1);
  return ret;
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

int
roy_string_at(const RoyString * string,
              size_t            position) {
  if (pos_correct(string, position)) {
    return *(string->str + position);
  }
  return '\0';
}

char *
roy_string_str(RoyString * string) {
  return string->str;
}

const char *
roy_string_cstr(const RoyString * string) {
  return string->str;
}

bool
roy_string_empty(const RoyString * string) {
  return *string->str == '\0';
}

size_t
roy_string_size(const RoyString * string) {
  return strlen(string->str);
}

void
roy_string_clear(RoyString * string) {
  string = roy_string_assign(string, "");
}

bool
roy_string_insert_str(RoyString  * string,
                      const char * substr,
                      size_t       position) {
  if (pos_correct(string, position)) {
    ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
    memcpy(temp, string->str, position);
    strcat(temp, substr);
    strncat(temp, string->str + position, roy_string_size(string) - position);
    string = roy_string_assign(string, temp);
    return true;
  } else {
    return false;
  }
}

bool
roy_string_insert(RoyString       * string,
                  const RoyString * substring,
                  size_t            position) {
  return roy_string_insert_str(string, roy_string_cstr(substring), position);
}

void
roy_string_prepend_str(RoyString * string,
                       const char * substr) {
  roy_string_insert_str(string, substr, 0);
}

void
roy_string_prepend(RoyString      * string,
                   const RoyString * substring) {
  roy_string_prepend_str(string, roy_string_cstr(substring));
}

void
roy_string_append_str(RoyString  * string,
                      const char * substr) {
  roy_string_insert_str(string, substr, roy_string_size(string));
}

void
roy_string_append(RoyString       * string,
                  const RoyString * substring) {
  roy_string_append_str(string, roy_string_cstr(substring));
}

bool
roy_string_erase(RoyString * string,
                 size_t      position,
                 size_t      count) {
  if (pos_cnt_correct(string, position, count)) {
    ROY_STR(temp, roy_string_size(string) - count + 1)
    memcpy(temp, string->str, position);
    strncat(temp, string->str + position + count,
            roy_string_size(string) - position - count);
    string = roy_string_assign(string, temp);
    return true;
  } else {
    return false;
  }
}

bool
roy_string_erase_left(RoyString * string,
                      size_t      count) {
  return roy_string_erase(string, 0, count);
}

bool
roy_string_erase_right(RoyString * string,
                       size_t      count) {
  return roy_string_erase(string, roy_string_size(string) - count, count);
}

bool
roy_string_replace_str(RoyString  * string,
                       const char * substr,
                       size_t       position,
                       size_t       count) {
  if (pos_cnt_correct(string, position, count)) {
    ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
    strncpy(temp, string->str, position);
    strcat(temp, substr);
    strcat(temp, string->str + position + count);
    string = roy_string_assign(string, temp);
    return true;
  } else {
    return false;
  }
}

bool
roy_string_replace(RoyString       * string,
                   const RoyString * substring,
                   size_t            position,
                   size_t            count) {
  return roy_string_replace_str(string,
                                roy_string_cstr(substring),
                                position,
                                count);
}

RoyString *
roy_string_substring(RoyString * dest,
                     RoyString * string,
                     size_t      position,
                     size_t      count) {
  if (pos_cnt_correct(string, position, count)) {
    ROY_STR(temp, count + 1)
    strncpy(temp, string->str + position, count);
    return dest = roy_string_assign(dest, temp);
  } else {
    return NULL;
  }
}

RoyString *
roy_string_left(RoyString * dest, 
                RoyString * string, 
                size_t      count) {
  return roy_string_substring(dest, string, 0, count);
}

RoyString *
roy_string_right(RoyString * dest,
                 RoyString * string, 
                 size_t      count) {
  return roy_string_substring(dest, 
                              string,
                              roy_string_size(string) - count,
                              count);
}

void
roy_string_print(const RoyString * string) {
  printf("%s", roy_string_cstr(string));
}

void
roy_string_println(const RoyString * string) {
  roy_string_print(string);
  if (roy_string_at(string, roy_string_size(string) - 1) != '\n') {
    putchar('\n');
  }
}

int
roy_string_find_str(const RoyString  * string,
                    const char       * substr,
                    size_t             position) {
  const char * begin = string->str + position;
  const char * found = strstr(string->str + position, substr);
  return found ? (int)(found - begin) : -1;
}

int
roy_string_find(const RoyString * string,
                const RoyString * substr,
                size_t            position) {
  return roy_string_find_str(string, roy_string_cstr(substr), position);
}

int
roy_string_find_regex(const RoyString * string,
                      const char      * regex,
                      size_t            position) {
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
    ret = ovector[0];
  };
  free(re);
  free(rex);
  return ret;
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

bool
roy_string_equal(const RoyString * string1,
                 const RoyString * string2) {
  return strcmp(roy_string_cstr(string1), roy_string_cstr(string2)) == 0;
}

bool
roy_string_equal_str(const RoyString * string,
                     const char * str) {
  return strcmp(roy_string_cstr(string), str) == 0;
}

int
roy_string_compare(const RoyString * string1,
                   const RoyString * string2) {
  return strcmp(roy_string_cstr(string1), roy_string_cstr(string2));
}

/* PRIVATE FUNCTIONS DOWN HERE */

static bool
pos_correct(const RoyString * string,
            size_t            position) {
  return position <= roy_string_size(string);
}

static bool
pos_cnt_correct(const RoyString * string,
                size_t            position,
                size_t            count) {
  size_t size = roy_string_size(string);
  return (position <= size) && (position + count <= size);
}