#ifndef ROYSTRING_H
#define ROYSTRING_H

#include "../trivial/royinit.h"
#include "../list/roydeque.h"

struct RoyString_ {
  char * str;
};

/// @brief RoyString: stores and manipulates sequences of chars, offering common string operations.
typedef struct RoyString_ RoyString;

/* CONSTRUCTION AND DESTRUCTION */

/// @brief Constructs a RoyString with given 'str'.
RoyString * roy_string_new(const char * str);

/// @brief Constructs a RoyString with given integer 'value'.
RoyString * roy_string_new_int(int64_t value);

/// @brief Constructs a RoyString with given double 'value'.
RoyString * roy_string_new_double(double value);

/**
 * @brief Releases all memory and destroys the RoyString - 'string' itself.
 * @note - Always call this function after the work is done by the given 'string' to get rid of memory leaking.
 */
void roy_string_delete(RoyString * string);

/* CHARACTER ACCESS */

/**
 * @brief Accesses the specified character.
 * @return the character at 'position'.
 * @return NULL - if 'position' exceeds or 'string' is empty.
 */
int roy_string_at(const RoyString * string, size_t position);

/// @brief Returns a standard C character array version of 'string'.
char * roy_string_str(RoyString * string);

/// @brief Returns a non-modifiable standard C character array version of 'string'.
const char * roy_string_cstr(const RoyString * string);

/* CAPACITY */

/**
 * @brief Checks whether 'string' is empty.
 * @retval true - there is no character in 'string'.
 * @retval false - otherwise.
 */
bool roy_string_empty(const RoyString * string);

/// @brief Returns the number of characters in 'string'.
size_t roy_string_length(const RoyString * string);

/* OPERATIONS */

/**
 * @brief Copies strings from one to another.
 * @param dest - the new string to write to.
 * @param src - the specified C char-array to read from.
 */ 
RoyString * roy_string_assign(RoyString * dest, const char * src);

/// @brief Assigns integer 'value' to 'string'.
RoyString * roy_string_assign_int(RoyString * string, int64_t value);

/// @brief Assigns double number 'value' to 'string'.
RoyString * roy_string_assign_double(RoyString * string, double value);

/// @brief Clears the contents of 'string'.
void roy_string_clear(RoyString * string);

/**
 * @brief Inserts characters into 'string'.
 * @param substr - additional C char-array to insert.
 * @param position - position before which the characters will be inserted.
 * @retval true - the operation is successful.
 * @retval false - 'position' exceeds.
 */
bool roy_string_insert(RoyString * string, const char * substr, size_t position);

/**
 * @brief Adds additional characters to the left end of 'string'.
 * @param substr - additional C char-array to insert.
 */
void roy_string_prepend(RoyString * string, const char * substr);

/**
 * @brief Adds additional characters to the right end of 'string'.
 * @param substr - additional C char-array to insert.
 */
void roy_string_append(RoyString * string, const char * substr);

/**
 * @brief Removes characters from 'string'.
 * @param position - first character to remove.
 * @param count - number of characters to remove.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 */
bool roy_string_erase(RoyString * string, size_t position, size_t count);

/**
 * @brief Removes characters from left end of 'string'.
 * @param count - number of characters from left end to remove.
 * @retval true - the operation is successful.
 * @retval false - 'count' exceeds.
 */
bool roy_string_erase_left(RoyString * string, size_t count);

/**
 * @brief Removes characters from right end of 'string'.
 * @param count - number of characters from right end to remove.
 * @retval true - the operation is successful.
 * @retval false - 'count' exceeds.
 */
bool roy_string_erase_right(RoyString * string, size_t count);

/**
 * @brief Replaces the part of the string indicated by [position, position + count) with a new string.
 * @param substr - additional C char-array to insert.
 * @param position - first character to be replaced.
 * @param count - number of characters to be replaced.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 */
 bool roy_string_replace(RoyString * string, const char * substr, size_t position, size_t count);

/**
 * @brief Returns a substring [pos, pos+count).
 * @param dest - the returned RoyString.
 * @param string - the original RoyString.
 * @param position - first character of the substring.
 * @param count - number of characters of the substring.
 * @return 'dest' after the successful operation.
 * @return NULL - 'position' or 'position' + 'count' exceeds.
 */
RoyString * roy_string_substring(RoyString * dest, RoyString * string, size_t position, size_t count);

/**
 * @brief Returns a substring [0, count).
 * @param dest - the returned RoyString.
 * @param string - the original RoyString.
 * @param count - number of characters of the substring.
 * @return 'dest' after the successful operation.
 * @return NULL - 'count' exceeds.
 */
RoyString * roy_string_left(RoyString * dest, RoyString * string, size_t count);

/**
 * @brief Returns a substring [size() - count, size()).
 * @param dest - the returned RoyString.
 * @param string - the original RoyString.
 * @param count - number of characters of the substring.
 * @return 'dest' after the successful operation.
 * @return NULL - 'count' exceeds.
 */
RoyString * roy_string_right(RoyString * dest, RoyString * string, size_t count);

/// @brief Writes 'string' to stdout.
void roy_string_print(const RoyString * string);

/// @brief Writes 'string' to stdout, adds a new line to the end of 'string' if there wasn't one.
void roy_string_println(const RoyString * string);

/**
 * @brief Writes 'string' according to stdin.
 * @param buffer_size - size of the buffer inside the function.
 */ 
void roy_string_scan(RoyString * string, size_t buffer_size);

/* SEARCH */

/**
 * @brief Finds the position where the first substr occur (takes advantages of 'strstr').
 * @param substr - substr to be found.
 * @param position - position at which to start the search from 'string'.
 * @return Position of the first character of the found substring.
 * @return -1 - 'substr' not found.
 */
int roy_string_find(const RoyString * string, const char * substr, size_t position);

/**
 * @brief Finds the position where the given regular expression begins for the first time.
 * @param regex - pattern to be found.
 * @param position - position at which to start the search from 'string'.
 * @return Position of the first character of the found pattern.
 * @return -1 - pattern not found.
 * @return -51 - pattern is ill-formed.
 */
int roy_string_regex_begin(const RoyString * string, const char * regex, size_t position);

/**
 * @brief Finds the position where the given regular expression ends for the first time.
 * @param regex - pattern to be found.
 * @param position - position at which to start the search from 'string'.
 * @return Position of the first character right after the found pattern.
 * @return -1 - pattern not found.
 * @return -51 - pattern is ill-formed.
 */
int roy_string_regex_end(const RoyString * string, const char * regex, size_t position);

/**
 * @brief Finds all regular expressions repeatly from 'string'.
 * @param dest - where the regular expression found to pushed into.
 * @param regex - pattern to be found.
 * @param position - position at which to start the search from 'string'.
 * @return the destination deque.
 */
RoyDeque * roy_string_all_regex(RoyDeque * dest, const RoyString * string, const char * regex, size_t position);

/// @brief Test whether 'string' totally matches the given regular expression 'regex'.
bool roy_string_match(const RoyString * string, const char * regex);

/* UTILITIES */

/**
 * @brief Compares two strings lexicographically.
 * @retval Negative value if 'lhs' appears before 'rhs' in lexicographical order.
 * @retval Zero if 'lhs' and 'rhs' compare equal.
 * @retval Positive value if 'lhs' appears after 'rhs' in lexicographical order.
 */
int roy_string_compare(const RoyString * lhs, const RoyString * rhs);

/**
 *  @brief Interprets an integer value in a RoyString 'string'.
 *  @note Discards any whitespace characters until the first non-whitespace character is found, then takes as many characters as possible to form a valid integer number representation and converts them to an integer value.
 */
int64_t roy_string_to_int(const RoyString * string);

/**
 * @brief Interprets a floating-point value in a byte string pointed to by str.
 * @note Function discards any whitespace characters until first non-whitespace character is found. Then it takes as many characters as possible to form a valid floating-point representation and converts them to a floating-point value.
 */
double roy_string_to_double(const RoyString * string);

RoyDeque * roy_string_split(RoyDeque * dest, const RoyString * string, const char * regex);

RoyString * roy_string_join(RoyString * dest, const RoyDeque * vector, const char * splitter);

#endif // ROYSTRING_H