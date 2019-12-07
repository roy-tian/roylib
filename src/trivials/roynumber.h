#ifndef ROYNUMBER_H
#define ROYNUMBER_H

#include "royinit.h"
#include <stdint.h>
#include <time.h>
#include <math.h>

// Converts 'str' of binary digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
uint64_t roy_parse_bin(const char * str);

// Converts 'str' of octal digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
uint64_t roy_parse_oct(const char * str);

// Converts 'str' of hexadecimal digits into its equivalent unsigned value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
uint64_t roy_parse_hex(const char * str);

// Converts 'str' of digits into its equivalent value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
int64_t roy_parse_int(const char * str);

// Converts 'str' of floating point number into its equivalent value.
// (The parsing phase ends immediately when 'str' turned to be ill-formed.)
double roy_parse_double(const char * str);

// Converts the integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
// (The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).)
char * roy_int64_to_str(char * dest, int64_t number, size_t base, size_t width, bool fill_zero);

// Converts the unsigned integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
// (The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).)
char * roy_uint64_to_str(char * dest, uint64_t number, size_t base, size_t width, bool fill_zero);

// Returns 'dest' with the 'count' bits that begin at position 'position' set to the rightmost 'count' bits of 'src', 
// the other bits are left unchanged.
uint64_t roy_uint64_set_bits(uint64_t * dest, size_t position, size_t count, uint64_t src);

// Returns 'dest' with the 'count' bits that begin at position 'position' inverted 
// (i.e., 1 changed into 0 and vice versa), the other bits are left unchanged.
uint64_t roy_uint64_invert(uint64_t * number, size_t position, size_t count);

// Returns the value of the 'width'-width unsigned integer 'number' rotated to the right by 'steps' bit positions.
uint64_t roy_uint64_ror(uint64_t * number, size_t steps, size_t width);

// Returns the value of the 'width'-width unsigned integer 'number' rotated to the left by 'steps' bit positions.
uint64_t roy_uint64_rol(uint64_t * number, size_t steps, size_t width);

// Counts '1' bits in unsigned integer 'number'.
size_t roy_uint64_count_bit(uint64_t number);

// Tests whether the given 'number' is a prime number.
bool roy_uint64_prime(uint64_t number);

// Returns the next prime number nearest to the given 'number'.
uint64_t roy_next_prime(uint64_t number);

// Seeds the stdlib version generator.
void roy_random_new(void);

// Generates a pseudo-random integer ∈ [min, max].
int64_t roy_next_random(int64_t min, int64_t max);

#endif // ROYNUMBER_H