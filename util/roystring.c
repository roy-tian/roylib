#define PCRE2_CODE_UNIT_WIDTH 8

#include "../trivial/roystr.h"
#include "roystring.h"
#include <pcre2.h>

static RoyString * new_empty(void);
static bool valid_pos(const RoyString * string, size_t position);
static bool valid_pos_cnt(const RoyString * string, size_t position, size_t count);
static int find_regex(const RoyString * string, const char * regex, size_t position, int begin_end);

RoyString *
roy_string_new(const char * str) {
  return roy_string_assign(new_empty(), str);
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
roy_string_length(const RoyString * string) {
  return strlen(string->str);
}

RoyString *
roy_string_assign(RoyString  * string,
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
  return roy_string_assign(string, buf);
}

RoyString *
roy_string_assign_double(RoyString * string,
                         double      value) {
  enum { MAX_DOUBLE = 44 };
  char buf[MAX_DOUBLE] = {'\0'};
  sprintf(buf, "%.15g", value);
  return roy_string_assign(string, buf);
}

void
roy_string_clear(RoyString * string) {
  roy_string_assign(string, "");
}

bool
roy_string_insert(RoyString  * string,
                  const char * substr,
                  size_t       position) {
  if (valid_pos(string, position)) {
    ROY_STR(temp, roy_string_length(string) + strlen(substr) + 1)
    memcpy(temp, string->str, position);
    strcat(temp, substr);
    strncat(temp, string->str + position, roy_string_length(string) - position);
    roy_string_assign(string, temp);
    return true;
  } else {
    return false;
  }
}

void
roy_string_prepend(RoyString * string,
                   const char * substr) {
  roy_string_insert(string, substr, 0);
}

void
roy_string_append(RoyString  * string,
                  const char * substr) {
  roy_string_insert(string, substr, roy_string_length(string));
}

bool
roy_string_erase(RoyString * string,
                 size_t      position,
                 size_t      count) {
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, roy_string_length(string) - count + 1)
    memcpy(temp, string->str, position);
    strncat(temp, string->str + position + count,
            roy_string_length(string) - position - count);
    roy_string_assign(string, temp);
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
  return roy_string_erase(string, roy_string_length(string) - count, count);
}

bool
roy_string_replace(RoyString  * string,
                   const char * substr,
                   size_t       position,
                   size_t       count) {
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, roy_string_length(string) + strlen(substr) + 1)
    strncpy(temp, string->str, position);
    strcat(temp, substr);
    strcat(temp, string->str + position + count);
    string = roy_string_assign(string, temp);
    return true;
  } else {
    return false;
  }
}

RoyString *
roy_string_substring(RoyString * dest,
                     RoyString * string,
                     size_t      position,
                     size_t      count) {
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, count + 1)
    strncpy(temp, roy_string_cstr(string) + position, count);
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
                              roy_string_length(string) - count,
                              count);
}

void
roy_string_print(const RoyString * string) {
  printf("%s", roy_string_cstr(string));
}

void
roy_string_println(const RoyString * string) {
  roy_string_print(string);
  if (roy_string_at(string, roy_string_length(string) - 1) != '\n') {
    putchar('\n');
  }
}

void
roy_string_scan(RoyString * string,
                size_t      buffer_size) {
  ROY_STR(buf, buffer_size)
  fgets(buf, buffer_size, stdin);
  roy_string_assign(string, buf);
  roy_string_erase_right(string, 1);
}

int
roy_string_find(const RoyString  * string,
                const char       * substr,
                size_t             position) {
  const char * begin = string->str + position;
  const char * found = strstr(string->str + position, substr);
  return found ? (int)(found - begin) : -1;
}

int
roy_string_regex_begin(const RoyString * string,
                       const char      * regex,
                       size_t            position) {
  return find_regex(string, regex, position, 0);
}

int
roy_string_regex_end(const RoyString * string,
                     const char      * regex,
                     size_t            position) {
  return find_regex(string, regex, position, 1);
}


bool
roy_string_match(const RoyString * string,
                 const char      * regex) {
  return
  roy_string_regex_begin(string, regex, 0) == 0 &&
  roy_string_regex_end(string, regex, 0) == (int)roy_string_length(string) - 1;
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
roy_string_split(RoyDeque        * dest,
                 const RoyString * string,
                 const char      * regex) {
  
}

RoyString *
roy_string_join(RoyString      * dest,
                const RoyDeque * vector,
                const char     * splitter) {

}

/* PRIVATE FUNCTIONS DOWN HERE */

static RoyString *
new_empty(void) {
  RoyString * ret = malloc(sizeof(RoyString));
  ret->str = NULL;
  return ret;
}

static bool
valid_pos(const RoyString * string,
          size_t            position) {
  return position <= roy_string_length(string);
}

static bool
valid_pos_cnt(const RoyString * string,
              size_t            position,
              size_t            count) {
  size_t size = roy_string_length(string);
  return (position <= size) && (position + count <= size);
}

static int
find_regex(const RoyString * string,
      const char      * regex,
      size_t            position,
      int               begin_end) {
  const PCRE2_SPTR pattern = (PCRE2_SPTR)regex;
  int error_code;
  PCRE2_SIZE error_offset;

  pcre2_code * re = pcre2_compile(
    pattern,
    PCRE2_ZERO_TERMINATED,
    0U,
    &error_code,
    &error_offset,
    NULL
  );

  const PCRE2_SPTR subject = (PCRE2_SPTR)roy_string_cstr(string) + position;
  PCRE2_SIZE subject_length = strlen((const char *)subject);
  pcre2_match_data * match_data = pcre2_match_data_create_from_pattern(re, NULL);

  int rc = pcre2_match(re, subject, subject_length, 0ULL, 0U, match_data, NULL);

  int ret;
  if (rc < 0) {
    ret = rc;
  } else {
    PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(match_data);
    ret = ovector[begin_end];
  }

  pcre2_match_data_free(match_data);
  pcre2_code_free(re);
  return ret;
}