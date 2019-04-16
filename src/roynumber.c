#include "../include/roynumber.h"
#include "../include/roystring.h"
#include <ctype.h>
#include <limits.h>

long long roy_parse_hexadecimal(const char * str) {
  long long ret = 0;
  long long pn = 1;
  if (strchr(str, '-') == str) {
    str += 1;
    pn = -1;
  } else if (strchr(str, '+') == str) {
    str += 1;
  }
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t len = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i < len; i++) {
    ret *= 16;
    int cur_chr = *(str + i);
    if (isdigit(cur_chr)) {
      ret += cur_chr - '0';
    } else if (strchr("ABCDEF", *(str + i))) {
      ret += cur_chr - 'A' + 10;
    } else if (strchr("abcdef", *(str + i))) {
      ret += cur_chr - 'a' + 10;
    }
  }
  return ret * pn;
}

char * roy_llong_to_string(char      * dest,
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
  if (!pn) { *pdest++ = '-'; }
  if (llong_min) { (*dest)++; }
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return roy_string_reverse(dest);
}

char * roy_ullong_to_string(char               * dest,
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