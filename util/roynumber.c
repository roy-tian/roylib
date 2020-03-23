#include "roynumber.h"
#include "roystr.h"
#include <limits.h>
#include <math.h>
#include <time.h>

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

uint64_t
roy_parse_bin(const char * str) {
  uint64_t result = 0ULL;
  STR_TRIM_LEFT(str)
  size_t len = strspn(str, "01");
  for (size_t i = 0 ; i != len; i++) {
    result <<= 1ULL;
    if (*(str + i) == '1') {
      result += 1ULL;
    }
  }
  return result;
}

uint64_t
roy_parse_oct(const char * str) {
  uint64_t result = 0ULL;
  STR_TRIM_LEFT(str)
  STR_INC("0", str)
  size_t len = strspn(str, "01234567");
  for (size_t i = 0; i != len; i++) {
    result <<= 3ULL;
    result += *(str + i) - '0';
  }
  return result; 
}

uint64_t
roy_parse_hex(const char * str) {
  uint64_t result = 0ULL;
  STR_TRIM_LEFT(str)
  if (strstr(str, "0X") == str || strstr(str, "0x") == str) {
    str += 2;
  }
  size_t len = strspn(str, "0123456789ABCDEFabcdef");
  for (size_t i = 0; i != len; i++) {
    result <<= 4ULL;
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

int64_t
roy_parse_int(const char * str) {
  long long result = 0LL;
  STR_TRIM_LEFT(str)
  int pn = *str == '-' ? -1 : 1;
  STR_INC("+-", str)
  STR_TO_INT(result, str)
  return pn * result;
}

double
roy_parse_double(const char * str) {
  double result = 0.0;
  STR_TRIM_LEFT(str)
  int pn = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  STR_TO_INT(result, str)
  STR_INC(".", str)
  const char * pstr = str;
  double expo = 1.0;
  STR_TO_INT(result, str)
  expo /= pow(10.0, (double)(str - pstr));
  STR_INC("eE", str)
  int pn_expo = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  double nexpo = 0.0;
  STR_TO_INT(nexpo, str)
  expo *= pow(10.0, pn_expo * nexpo);
  return pn * result * expo;
}

char *
roy_int_to_str(char    * dest,
               int64_t   number,
               size_t    base,
               size_t    width,
               bool      fill_zero) {
  bool pn = true, int64_min = false;
  if (number == LLONG_MIN) {
    int64_min = true;
    number++;
  }
  if (number < 0) {
    pn = false;
    number = -number;
  }
  char * pdest = dest;
  do {
    int cur_digit = (int)(number % base);
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0);
  if (!pn) {
    *pdest++ = '-';
  }
  if (int64_min) {
    (*dest)++;
  }
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return roy_str_reverse(dest);
}

char *
roy_uint_to_str(char     * dest,
                uint64_t   number,
                size_t     base,
                size_t     width,
                bool       fill_zero) {
  char * pdest = dest;
  do {
    int cur_digit = (int)(number % base);
    *pdest++ = cur_digit + (cur_digit <= 9 ? '0' : 'A' - 10);
  } while ((number /= base) > 0); 
  size_t dest_width = pdest - dest;
  while (width-- > dest_width) {
    *pdest++ = fill_zero ? '0' : ' ';
  }
  *pdest = '\0';
  return roy_str_reverse(dest);
}

uint64_t
roy_uint_set_bits(uint64_t * dest,
                  uint64_t   src,
                  size_t     position,
                  size_t     count) {
  return *dest = (*dest & ~(~(~0ULL << count) << (position + 1 - count))) |
                 ( src  &   ~(~0ULL << count) << (position + 1 - count));
}

uint64_t
roy_uint_invert(uint64_t * number,
                size_t     position,
                size_t     count) {
  return *number = *number ^ ~(~0ULL << count) << (position + 1 - count);
}

uint64_t
roy_uint_ror(uint64_t * number,
             size_t     steps,
             size_t     width) {
  uint64_t right = (*number & ~(~0ULL << steps)) << (width - steps);
  *number >>= steps;
  *number |= right;
  return *number;
}

uint64_t
roy_uint_rol(uint64_t * number,
             size_t     steps,
             size_t     width) {
  uint64_t right = (*number & ~(~0ULL << (width - steps))) << steps;
  *number >>= width - steps;
  *number |= right;
  return *number;
}

size_t
roy_uint_count_bit(uint64_t number) {
  size_t count = 0;
  // 'n & n - 1' deletes the rightmost '1' of n.
  for (; number != 0; number &= number - 1) { 
    count++;
  }
  return count;
}


bool
roy_uint_prime(uint64_t number) {
  if (number < 2 || (number != 2 && number % 2 == 0)) {
    return false;
  }
  for (size_t i = 3; i <= number / 2; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

uint64_t
roy_next_prime(uint64_t number) {
  while (!roy_uint_prime(number)) {
    number++;
  }
  return number;
}

void
roy_random_new(void) {
  srand((unsigned)time(NULL));
}

uint64_t
roy_random_next(uint64_t min,
                uint64_t max) {
  if (max < min) {
    return max;
  }
  uint64_t ret = max + 1;
  while (ret > max) {
    ret = rand() / ( (RAND_MAX + 1U) / max ) + min;
  }
  return ret;
}
