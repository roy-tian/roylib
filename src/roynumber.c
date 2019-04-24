#include "../include/roynumber.h"
#include "../include/roystring.h"
#include <ctype.h>
#include <limits.h>
#include <math.h>

// Converts pure number string 'str' into decimal number.
#define STR_TO_INT(num, str)      \
        while (isdigit(*str)) {   \
          num *= 10;              \
          num += *str++ - '0';    \
        }

// Trims the first character of 'str' if it's in 'set'.
#define STR_INC(set, str)         \
        if (strchr(set, *str)) {  \
          str++;                  \
        }
// Trims all blanks and tabs on the left of 'str'.
#define STR_TRIM_LEFT(str)        \
        str += strspn(str, " \t");

unsigned long long
roy_parse_binary(const char * str) {
  unsigned long long result = 0ULL;
  STR_TRIM_LEFT(str)
  size_t len = strspn(str, "01");
  for (size_t i = 0 ; i != len; i++) {
    result <<= 1;
    if (*(str + i) == '1') {
      result += 1;
    }
  }
  return result;
}

unsigned long long
roy_parse_octal(const char * str) {
  unsigned long long result = 0ULL;
  STR_TRIM_LEFT(str)
  STR_INC("0", str)
  size_t len = strspn(str, "01234567");
  for (size_t i = 0; i != len; i++) {
    result <<= 3;
    result += *(str + i) - '0';
  }
  return result; 
}

unsigned long long
roy_parse_hexadecimal(const char * str) {
  unsigned long long result = 0ULL;
  STR_TRIM_LEFT(str)
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t len = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i != len; i++) {
    result <<= 4;
    int cur_chr = *(str + i);
    if (isdigit(cur_chr)) {
      result += cur_chr - '0';
    } else if (strchr("ABCDEF", *(str + i))) {
      result += cur_chr - 'A' + 10;
    } else /* if (strchr("abcdef", *(str + i))) */ {
      result += cur_chr - 'a' + 10;
    }
  }
  return result;
}

long long
roy_parse_integer(const char * str) {
  long long result = 0LL;
  STR_TRIM_LEFT(str)
  int pn = *str == '-' ? -1 : 1;
  STR_INC("+-", str)
  STR_TO_INT(result, str)
  return pn * result;
}

double roy_parse_double(const char * str) {
  double result = 0.0;
  STR_TRIM_LEFT(str)
  int pn = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  STR_TO_INT(result, str)
  STR_INC(".", str)
  const char * pstr = str;
  double expo = 1.0;
  STR_TO_INT(result, str)
  expo /= pow(10, str - pstr);
  STR_INC("eE", str)
  int pn_expo = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  double nexpo = 0.0;
  STR_TO_INT(nexpo, str)
  expo *= pow(10.0, pn_expo * nexpo);
  return pn * result * expo;
}

char *
roy_llong_to_string(char      * dest,
                    long long   number,
                    size_t      base,
                    size_t      width,
                    bool        fill_zero) {
  bool pn = true, llong_min = false;
  if (number == LLONG_MIN) {
    llong_min = true;
    number++;
  }
  if (number < 0) {
    pn = false;
    number = -number;
  }
  char * pdest = dest;
  do {
    int cur_digit = number % base;
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0);
  if (!pn) {
    *pdest++ = '-';
  }
  if (llong_min) {
    (*dest)++;
  }
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return roy_string_reverse(dest);
}

char *
roy_ullong_to_string(char               * dest,
                     unsigned long long   number,
                     size_t               base,
                     size_t               width,
                     bool                 fill_zero) {
  char * pdest = dest;
  do {
    int cur_digit = number % base;
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0); 
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return roy_string_reverse(dest);
}

unsigned long long
roy_ullong_set_bits(unsigned long long * dest,
                    int                  position,
                    size_t               count,
                    unsigned long long   src) {
  return *dest = (*dest & ~(~(~0ULL << count) << (position + 1 - count))) |
                 ( src  &   ~(~0ULL << count) << (position + 1 - count));
}

unsigned long long
roy_ullong_invert(long long * number,
                  int         position,
                  size_t      count) {
  return *number = *number ^ ~(~0ULL << count) << (position + 1 - count);
}

unsigned long long
roy_ullong_rotate_right(unsigned long long * number,
                        int                  steps,
                        size_t               width) {
  unsigned long long right = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= right;
  return *number;
}

unsigned long long
roy_ullong_rotate_left(unsigned long long * number,
                       int                  steps,
                       size_t               width) {
  unsigned long long right = (*number & ~(~0ULL << (width - steps))) << steps;
  *number >>= width - steps;
  *number |= right;
  return *number;
}

size_t
roy_ullong_count_bit(unsigned long long number) {
  size_t count = 0;
  // 'n & n - 1' deletes the rightmost '1' of n.
  for (; number != 0; number &= number - 1) { 
    count++;
  }
  return count;
}