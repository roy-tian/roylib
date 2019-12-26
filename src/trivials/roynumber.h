#ifndef ROYNUMBER_H
#define ROYNUMBER_H

#include "royinit.h"

/**
 * @brief Converts 'str' of binary digits into its equivalent unsigned value.
 * @note - The parsing phase ends immediately when 'str' turned to be ill-formed.
 */ 
uint64_t roy_parse_bin(const char * str);

/**
 * @brief Converts 'str' of octal digits into its equivalent unsigned value.
 * @note - The parsing phase ends immediately when 'str' turned to be ill-formed.
 */ 
uint64_t roy_parse_oct(const char * str);

/**
 * @brief Converts 'str' of hexadecimal digits into its equivalent unsigned value.
 * @note - The parsing phase ends immediately when 'str' turned to be ill-formed.
 */ 
uint64_t roy_parse_hex(const char * str);

/**
 * @brief Converts 'str' of digits into its equivalent value.
 * @note - The parsing phase ends immediately when 'str' turned to be ill-formed.
 */ 
int64_t roy_parse_int(const char * str);

/**
 * @brief Converts 'str' of floating point number into its equivalent value.
 * @note - The parsing phase ends immediately when 'str' turned to be ill-formed.
 */ 
double roy_parse_double(const char * str);

/**
 * @brief Converts the integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
 * @param dest - a pointer to the result string to write to.
 * @param base - base of 'number', eg. 2 represents binary, etc.
 * @param width - the minimal length of result string.
 * @param fill_zero - wether to fill blanks in 'dest' with '0' if the actual string is shorter than 'width'.
 * @note - The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).
 */
char * roy_int_to_str(char * dest, int64_t number, size_t base, size_t width, bool fill_zero);

/**
 * @brief Converts the unsinged integer 'number' into a 'width'-width, 'base' character representation in the string 'dest'.
 * @param dest - a pointer to the result string to write to.
 * @param base - base of 'number', eg. 2 represents binary, etc.
 * @param width - the minimal length of result string.
 * @param fill_zero - wether to fill blanks in 'dest' with '0' if the actual string is shorter than 'width'.
 * @note - The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).
 */
char * roy_uint_to_str(char * dest, uint64_t number, size_t base, size_t width, bool fill_zero);

// Returns 'dest' with the 'count' bits that begin at position 'position' set to the rightmost 'count' bits of 'src', 
// the other bits are left unchanged.
uint64_t roy_uint_set_bits(uint64_t * dest, size_t position, size_t count, uint64_t src);

// Returns 'dest' with the 'count' bits that begin at position 'position' inverted 
// (i.e., 1 changed into 0 and vice versa), the other bits are left unchanged.
uint64_t roy_uint_invert(uint64_t * number, size_t position, size_t count);

// Returns the value of the 'width'-width unsigned integer 'number' rotated to the right by 'steps' bit positions.
uint64_t roy_uint_ror(uint64_t * number, size_t steps, size_t width);

// Returns the value of the 'width'-width unsigned integer 'number' rotated to the left by 'steps' bit positions.
uint64_t roy_uint_rol(uint64_t * number, size_t steps, size_t width);

/// @brief Counts '1' bits in unsigned integer 'number'.
size_t roy_uint_count_bit(uint64_t number);

/// @brief Tests whether the given 'number' is a prime number.
bool roy_uint_prime(uint64_t number);

/// @brief Returns the next prime number nearest to the given 'number'.
uint64_t roy_next_prime(uint64_t number);

/// @brief Seeds the stdlib version generator.
void roy_random_new(void);

/// @brief Generates a pseudo-random integer N ∈ [min, max].
int64_t roy_next_random(int64_t min, int64_t max);

#endif // ROYNUMBER_H