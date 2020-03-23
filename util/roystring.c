#define PCRE2_CODE_UNIT_WIDTH 8

#include "roystr.h"
#include "roystring.h"
#include <pcre2.h>

enum {
    INT_MAX_LENGTH = 21,
    DOUBLE_MAX_LENGTH = 44
};

static RoyString * new_empty(void);
static bool valid_pos(const RoyString * string, size_t position);
static bool valid_pos_cnt(const RoyString * string, size_t position, size_t count);

RoyString *
roy_string_new(const char * str) {
  return roy_string_assign(new_empty(), str);
}

RoyString *
roy_string_new_int(int value) {
  return roy_string_assign_int(new_empty(), value);
}

RoyString *
roy_string_new_double(double value) {
  return roy_string_assign_double(new_empty(), value);
}

RoyString *
roy_string_copy(const RoyString * other) {
  return roy_string_assign(new_empty(), roy_string_cstr(other, 0));
}

RoyString *
roy_string_read_file(const char * path) {
  FILE * fp = fopen(path, "r");

  if (!fp) {
    perror(path);
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char buf[size];
  memset(buf, '\0', size);
  fread(buf, sizeof(char), size, fp);

  RoyString * ret = new_empty();
  roy_string_assign(ret, buf);
  fclose(fp);
  return ret;
}

void
roy_string_delete(RoyString * string,
                  void      * user_data) {
  free(string->str);
  free(string);
}

int
roy_string_at(const RoyString * string,
              size_t            position) {
  return valid_pos(string, position) ? (int)*(string->str + position) : '\0';
}

char *
roy_string_str(RoyString * string,
               size_t      position) {
  return valid_pos(string, position) ? string->str + position : NULL;
}

const char *
roy_string_cstr(const RoyString * string,
                size_t            position) {
  return valid_pos(string, position) ? string->str + position : NULL;
}

bool
roy_string_empty(const RoyString * string) {
  return roy_string_at(string, 0) == '\0';
}

size_t
roy_string_length(const RoyString * string) {
  return strlen(string->str);
}

RoyString *
roy_string_assign(RoyString  * restrict string,
                  const char * restrict str) {
  string->str = realloc(string->str, (strlen(str) + 1) * sizeof(char));
  memcpy(string->str, str, strlen(str) + 1);
  return string;
}

RoyString *
roy_string_assign_int(RoyString * string,
                      int         value) {
  char buf[INT_MAX_LENGTH] = { '\0' };
  sprintf(buf, "%d", value);
  return roy_string_assign(string, buf);
}

RoyString *
roy_string_assign_double(RoyString * string,
                         double      value) {
  char buf[DOUBLE_MAX_LENGTH] = { '\0' };
  sprintf(buf, "%.15g", value);
  return roy_string_assign(string, buf);
}

void
roy_string_clear(RoyString * string) {
  roy_string_assign(string, "");
}

bool
roy_string_insert(RoyString  * restrict string,
                  const char * restrict substr,
                  size_t                position) {
  if (valid_pos(string, position)) {
    size_t length = roy_string_length(string);
    ROY_STR(temp, length + strlen(substr) + 1)
    memcpy (temp, roy_string_cstr(string, 0), position);
    strcat (temp, substr);
    strncat(temp, roy_string_cstr(string, position), length - position);
    roy_string_assign(string, temp);
    return true;
  }
  return false;
}

void
roy_string_prepend(RoyString  * restrict string,
                   const char * restrict substr) {
  roy_string_insert(string, substr, 0);
}

void
roy_string_append(RoyString  * restrict string,
                  const char * restrict substr) {
  roy_string_insert(string, substr, roy_string_length(string));
}

bool
roy_string_erase(RoyString * string,
                 size_t      position,
                 size_t      count) {
  if (valid_pos_cnt(string, position, count)) {
    size_t length = roy_string_length(string);
    ROY_STR(temp, length - count + 1)
    memcpy (temp, roy_string_cstr(string, 0), position);
    strncat(temp,
            roy_string_cstr(string, position + count),
            length - position - count);
    roy_string_assign(string, temp);
    return true;
  }
  return false;
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
roy_string_replace(RoyString  * restrict string,
                   const char * restrict substr,
                   size_t       position,
                   size_t       count) {
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, roy_string_length(string) + strlen(substr) + 1)
    strncpy(temp, roy_string_cstr(string, 0), position);
    strcat (temp, substr);
    strcat (temp, roy_string_cstr(string, position + count));
    string = roy_string_assign(string, temp);
    return true;
  }
  return false;
}

bool
roy_string_substring(RoyString * string,
                     size_t      position,
                     size_t      count) {
  if (valid_pos_cnt(string, position, count)) {
    ROY_STR(temp, count + 1)
    strncpy(temp, roy_string_cstr(string, position), count);
    roy_string_assign(string, temp);
    return true;
  }
  return false;
}

bool
roy_string_left(RoyString * string, 
                size_t      count) {
  return roy_string_substring(string, 0, count);
}

bool
roy_string_right(RoyString * string, 
                 size_t      count) {
  return
  roy_string_substring(string, roy_string_length(string) - count, count);
}

void
roy_string_print(const RoyString * string) {
  printf("%s", roy_string_cstr(string, 0));
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
                size_t      buf_size) {
  ROY_STR(temp, buf_size)
  fgets  (temp, buf_size, stdin);
  roy_string_assign(string, temp);
  roy_string_erase_right(string, 1);
}

RMatch
roy_string_find(const RoyString  * string,
                const char       * pattern,
                size_t             position) {
  RMatch ret = { PCRE2_ERROR_NOMATCH, PCRE2_ERROR_NOMATCH };
  const PCRE2_SPTR ptn = (const PCRE2_SPTR)pattern;
  int err_code;
  PCRE2_SIZE err_offset;
  pcre2_code * re =
    pcre2_compile(ptn, PCRE2_ZERO_TERMINATED, 0U, &err_code, &err_offset, NULL);

  if (re == NULL) {
    ret.begin = ret.end = PCRE2_ERROR_NULL;
  }

  const PCRE2_SPTR    sub = (const PCRE2_SPTR)roy_string_cstr(string, position);
  PCRE2_SIZE       sublen = strlen((const char *)sub);
  pcre2_match_data * data = pcre2_match_data_create_from_pattern(re, NULL);

  if (pcre2_match(re, sub, sublen, 0ULL, PCRE2_NOTEMPTY, data, NULL) > 0) {
    /* Since 'data' is create by 'pcre2_match_data_create_from_pattern',
       'pcre2_match' would never equal to 0. */
    PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(data);
    ret.begin = ovector[0];
    ret.end   = ovector[1];
  }

  pcre2_match_data_free(data);
  pcre2_code_free(re);
  return ret;
}

bool
roy_string_match(const RoyString * string,
                 const char      * pattern) {
  RMatch match = roy_string_find(string, pattern, 0);
  return match.begin == 0 && match.end == (int)roy_string_length(string);
}

int
roy_string_compare(const RoyString * string1,
                   const RoyString * string2) {
  return strcmp(roy_string_cstr(string1, 0), roy_string_cstr(string2, 0));
}

int
roy_string_to_int(const RoyString * string) {
  return atoi(roy_string_cstr(string, 0));
}

double
roy_string_to_double(const RoyString * string) {
  return atof(roy_string_cstr(string, 0));
}

size_t
roy_string_tokenize(RoyDeque        * restrict dest,
                    const RoyString * restrict string,
                    const char      * restrict pattern) {
  size_t pos = 0;
  RMatch match = roy_string_find(string, pattern, pos);
  while (match.begin != PCRE2_ERROR_NOMATCH) {
    RMatch * temp = malloc(sizeof(RMatch));
    temp->begin   = pos + match.begin;
    temp->end     = pos + match.end;
    roy_deque_push_back(dest, temp);
    pos += match.end;
    match = roy_string_find(string, pattern, pos);
  }
  return roy_deque_size(dest);
}

size_t
roy_string_split(RoyDeque        * restrict dest,
                 const RoyString * restrict string,
                 const char      * restrict separator) {
  size_t pos = 0;
  RMatch match = roy_string_find(string, separator, pos);
  while (match.begin != PCRE2_ERROR_NOMATCH) {
    RoyString * temp = roy_string_copy(string);
    roy_string_substring(temp, pos, match.begin);
    if (!roy_string_empty(temp)) {
      roy_deque_push_back(dest, temp);
    }
    pos += match.end;
    match = roy_string_find(string, separator, pos);
  }
  RoyString * temp = roy_string_copy(string);
  roy_string_erase_left(temp, pos);
  if (!roy_string_empty(temp)) {
    roy_deque_push_back(dest, temp);
  }
  return roy_deque_size(dest);
}

RoyString *
roy_string_join(RoyString      * restrict dest,
                const RoyDeque * restrict deque,
                const char     * restrict separator) {
  int i = 0;
  for (; i < (int)roy_deque_size(deque) - 1; i++) {
    roy_string_append(dest, roy_string_cstr(roy_deque_cpointer(deque, i), 0));
    roy_string_append(dest, separator);
  }
  roy_string_append(dest, roy_string_cstr(roy_deque_cpointer(deque, i), 0));
  return dest;
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