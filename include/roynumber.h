#ifndef ROYNUMBER_H
#define ROYNUMBER_H

#include <stddef.h>
#include <stdbool.h>

enum NumeralSystem {
  ROY_NUMERAL_BINARY = 2,
  ROY_NUMERAL_OCTAL = 8,
  ROY_NUMERAL_DECIMAL = 10,
  ROY_NUMERAL_HEXDECIMAL = 16
};

// Converts 'str' of binary digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
unsigned long long roy_parse_binary(const char * str);

// Converts 'str' of octal digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
unsigned long long roy_parse_octal(const char * str);

// Converts 'str' of hexadecimal digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
unsigned long long roy_parse_hexadecimal(const char * str);

// Converts 'str' of digits into its equivalent value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
long long roy_parse_integer(const char * str);

// Converts 'str' of floating number into its equivalent value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
double roy_parse_double(const char * str);

// Converts the integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
// (The behavior is undefined if 'dest' or 'width' is insefi`cient, or 'base' is larger than 36 ([0-9a-z]).)
char * roy_llong_to_string(char * dest, long long number, size_t base, size_t width, bool fill_zero);

// Converts the unsigned integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
// (The behavior is undefined if 'dest' or 'width' is insefi`cient, or 'base' is larger than 36 ([0-9a-z]).)
char * roy_ullong_to_string(char * dest, unsigned long long number, size_t base, size_t width, bool fill_zero);

unsigned long long roy_ullong_set_bits(unsigned long long * dest, int position, size_t count, unsigned long long src);

unsigned long long roy_ullong_invert(long long * number, int position, size_t count);

unsigned long long roy_ullong_rotate_right(unsigned long long * number, int steps, size_t width); 

unsigned long long roy_ullong_rotate_left(unsigned long long * number, int steps, size_t width); 

size_t roy_ullong_count_bit(unsigned long long number);
#endif // ROYNUMBER_H