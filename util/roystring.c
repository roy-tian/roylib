#include "../trivial/roystr.h"
#include "roystring.h"
#include <pcre.h>

static inline RoyString * new_empty(void);
static inline bool valid_pos(const RoyString * string, size_t position);
static inline bool valid_pos_cnt(const RoyString * string, size_t position, size_t count);

RoyString *
roy_string_new(const RoyString * string) {
  RoyString * ret = new_empty();
  return string ?
         roy_string_assign(ret, string) :
         roy_string_assign_str(ret, "");
}

RoyString *
roy_string_new_str(const char * str) {
  return roy_string_assign_str(new_empty(), str);
}

RoyString *
roy_string_new_int(int64_t value) {
  return roy_string_assign_int(new_empty(), value);
}

RoyString *
roy_string_new_double(double value) {
  return roy_string_assign_double(new_empty(), value);
}

void
roy_string_delete(RoyString * string) {
  free(string->str);
  free(string);
}

int
roy_string_at(const RoyString * string,
              size_t            position) {
  if (valid_pos(string, position)) {
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

RoyString *
roy_string_assign(RoyString       * dest,
                  const RoyString * src) {
  return roy_string_assign_str(dest, roy_string_cstr(src));
}

RoyString *
roy_string_assign_str(RoyString  * string,
                      const char * str) {
  string->str = realloc(string->str, (strlen(str) + 1) * sizeof(char));
  memcpy(string->str, str, strlen(str) + 1);
  return string;
}

RoyString *
roy_string_assign_int(RoyString * string,
                      int64_t     value) {
  enum { MAX_INT = 21 };
  char buf[MAX_INT] = {'\0'};
  sprintf(buf, "%lld", value);
  return roy_string_assign_str(string, buf);
}

RoyString *
roy_string_assign_double(RoyString * string,
                         double      value) {
  enum { MAX_DOUBLE = 44 };
  char buf[MAX_DOUBLE] = {'\0'};
  sprintf(buf, "%.15g", value);
  return roy_string_assign_str(string, buf);
}

void
roy_string_clear(RoyString * string) {
  roy_string_assign_str(string, "");
}

bool
roy_string_insert_str(RoyString  * string,
                      const char * substr,
                      size_t       position) {
  if (valid_pos(string, position)) {
    ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
    memcpy(temp, string->str, position);
    strcat(temp, substr);
    strncat(temp, string->str + position, roy_string_size(string) - position);
    roy_string_assign_str(string, temp);
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
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, roy_string_size(string) - count + 1)
    memcpy(temp, string->str, position);
    strncat(temp, string->str + position + count,
            roy_string_size(string) - position - count);
    roy_string_assign_str(string, temp);
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
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, roy_string_size(string) + strlen(substr) + 1)
    strncpy(temp, string->str, position);
    strcat(temp, substr);
    strcat(temp, string->str + position + count);
    string = roy_string_assign_str(string, temp);
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
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, count + 1)
    strncpy(temp, string->str + position, count);
    return dest = roy_string_assign_str(dest, temp);
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

void
roy_string_scan(RoyString * string,
                size_t      buffer_size) {
  ROY_STR(buf, buffer_size)
  fgets(buf, buffer_size, stdin);
  roy_string_assign_str(string, buf);
  roy_string_erase_right(string, 1);
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

int64_t
roy_string_to_int(const RoyString * string) {
  return strtoll(roy_string_cstr(string), NULL, 0);
}

double
roy_string_to_double(const RoyString * string) {
  return strtod(roy_string_cstr(string), NULL);
}

RoyDeque *
roy_string_split(RoyDeque * dest,
                 const RoyString * string,
                 const char * regex) {

}

RoyString * roy_string_join(RoyString * dest, const RoyDeque * vector, const char * splitter);

/* PRIVATE FUNCTIONS DOWN HERE */

static inline RoyString *
new_empty(void) {
  RoyString * ret = malloc(sizeof(RoyString));
  ret->str = NULL;
  return ret;
}

static inline bool
valid_pos(const RoyString * string,
          size_t            position) {
  return position <= roy_string_size(string);
}

static inline bool
valid_pos_cnt(const RoyString * string,
              size_t            position,
              size_t            count) {
  size_t size = roy_string_size(string);
  return (position <= size) && (position + count <= size);
}