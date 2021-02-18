#ifndef ROYNUMBER_H
#define ROYNUMBER_H

#include "../util/rpre.h"

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
 * @param fill_zero - whether to fill blanks in 'dest' with '0' if the actual string is shorter than 'width'.
 * @note - The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).
 */
char * roy_int_to_str(char * dest, int64_t number, size_t base, size_t width, bool fill_zero);

/**
 * @brief Converts the unsigned integer 'number' into a 'width'-width,
 *        'base' character representation in the string 'dest'.
 * @param dest - a pointer to the result string to write to.
 * @param base - base of 'number', eg. 2 represents binary, etc.
 * @param width - the minimal length of result string.
 * @param fill_zero - whether to fill blanks in 'dest' with '0' if the actual string is shorter than 'width'.
 * @note - The behavior is undefined if 'dest' or 'width' is insufficient, or 'base' is larger than 36 ([0-9a-z]).
 */
char * roy_uint_to_str(char * dest, uint64_t number, size_t base, size_t width, bool fill_zero);

#endif // ROYNUMBER_H
