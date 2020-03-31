#ifndef ROYSTRING_H
#define ROYSTRING_H

#include "royinit.h"
#include "roymatch.h"
#include "../list/roydeque.h"

#define RE_COMMENT "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/"
#define RE_NUMBER  "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?"

struct RoyString_ {
  char * str;
};

/// @brief RoyString: stores and manipulates sequences of chars, offering common string operations.
typedef struct RoyString_ RoyString;

/* CONSTRUCTION AND DESTRUCTION */

/// @brief Constructs a RoyString with given 'str'.
RoyString * roy_string_new(const char * str);

/// @brief Constructs a RoyString with given integer 'value'.
RoyString * roy_string_new_int(int value);

/// @brief Constructs a RoyString with given double 'value'.
RoyString * roy_string_new_double(double value);

/// @brief Constructs a RoyString with the content of another RoyString.
RoyString * roy_string_copy(const RoyString * other);

/// @brief Constructs a RoyString with given double 'value'.
RoyString * roy_string_read_file(const char * path);

/**
 * @brief Releases all memory and destroys the RoyString - 'string' itself.
 * @note - Always call this function after the work is done by the given 'string' to get rid of memory leaking.
 */
void roy_string_delete(RoyString * string, void * user_data);

/* CHARACTER ACCESS */

/**
 * @brief Accesses the specified character.
 * @return the character at 'position'.
 * @return NULL - if 'position' exceeds or 'string' is empty.
 */
int roy_string_at(const RoyString * string, size_t position);

/**
 * @brief Returns a standard C character array version at 'position' of 'string'.
 * @return NULL - if 'position' exceeds or 'string' is empty.
 */
char * roy_string_str(RoyString * string, size_t position);

/**
 * @brief Returns a non-modifiable standard C character array version at 'position' of 'string'.
 * @return NULL - if 'position' exceeds or 'string' is empty.
 */
const char * roy_string_cstr(const RoyString * string, size_t position);

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
RoyString * roy_string_assign(RoyString * restrict dest, const char * restrict src);

/// @brief Assigns integer 'value' to 'string'.
RoyString * roy_string_assign_int(RoyString * string, int value);

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
bool roy_string_insert(RoyString * restrict string, const char * restrict substr, size_t position);

/**
 * @brief Adds additional characters to the left end of 'string'.
 * @param substr - additional C char-array to insert.
 */
void roy_string_prepend(RoyString * restrict string, const char * restrict substr);

/**
 * @brief Adds additional characters to the right end of 'string'.
 * @param substr - additional C char-array to insert.
 */
void roy_string_append(RoyString * restrict string, const char * restrict substr);

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
 bool roy_string_replace(RoyString * restrict string, const char * restrict substr, size_t position, size_t count);

/**
 * @brief Returns a substring [pos, pos+count).
 * @param dest - the destination RoyString.
 * @param src - the original RoyString.
 * @param position - first character of the substring.
 * @param count - number of characters of the substring.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 * @note 'dest' and 'src' can be identical for self operation.
 */
bool roy_string_substring(RoyString * dest, const RoyString * src, size_t position, size_t count);

/**
 * @brief Returns a substring [0, count).
 * @param dest - the destination RoyString.
 * @param src - the original RoyString.
 * @param count - number of characters of the substring.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 * @note 'dest' and 'src' can be identical for self operation.
 */
bool roy_string_left(RoyString * dest, const RoyString * src, size_t count);

/**
 * @brief Returns a substring [size() - count, size()).
 * @param dest - the destination RoyString.
 * @param src - the original RoyString.
 * @param count - number of characters of the substring.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 * @note 'dest' and 'src' can be identical for self operation.
 */
bool roy_string_right(RoyString * dest, const RoyString * src, size_t count);

/**
 * @brief Returns a substring [match.begin, match.end).
 * @param dest - the destination RoyString.
 * @param src - the original RoyString.
 * @param match - offer the range of the returning substring.
 * @retval true - the operation is successful.
 * @retval false - 'position' or 'position' + 'count' exceeds.
 * @note 'dest' and 'src' can be identical for self operation.
 */
bool roy_string_sub_match(RoyString * dest, const RoyString * src, const RoyMatch * match);

/// @brief Writes 'string' to stdout.
void roy_string_print(const RoyString * string);

/// @brief Writes 'string' to stdout, adds a new line to the end of 'string' if there wasn't one.
void roy_string_println(const RoyString * string);

/**
 * @brief Writes 'string' according to stdin.
 * @param buffer_size - size of the buffer inside the function.
 */ 
void roy_string_scan(RoyString * string, size_t buf_size);

/* SEARCH */

/**
 * @brief Finds the position where the first substr occur (takes advantages of pcre2).
 * @param pattern - substring to be found, char string literals and regexs are allowed.
 * @param position - position at which to start the search from 'string'.
 * @return the first pattern found, can be accessed by '.begin' '.end', -1 if not found, -51 if 'pattern' is a ill-formed regex.
 */
RoyMatch roy_string_find(const RoyString * string, const char * pattern, size_t position);

/**
 * @brief Tests whether 'string' exactly matches the given string 'pattern'. 
 * @param pattern - string to be compared, char string literals and regexs are allowed.
 */
bool roy_string_match(const RoyString * string, const char * pattern);

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
 *  @note Discards any whitespace characters until the first non-whitespace character is found,
 *        then takes as many characters as possible to form a valid integer number representation and
 *        converts them to an integer value.
 */
int64_t roy_string_to_int(const RoyString * string);

/**
 * @brief Interprets a floating-point value in a byte string pointed to by str.
 * @note Function discards any whitespace characters until first non-whitespace character is found.
 *       Then it takes as many characters as possible to form a valid floating-point representation and
 *       converts them to a floating-point value.
 */
double roy_string_to_double(const RoyString * string);

/**
 * @brief Finds all regular expressions repeatedly and greedily from 'string', stores them in deque 'dest'.
 * @param dest - where the position info (RMatch) to pushed into.
 * @param pattern - pattern to be parsed.
 * @return the size of the destination deque, aka number of tokenized strings.
 */
size_t roy_string_tokenize(RoyDeque * restrict dest, const RoyString * restrict string, int pattern_count, ...);

/**
 * @brief Separates 'string' into substrings using 'separator', and stores all substrings in deque 'dest'.
 * @param dest - where the substrings to pushed into.
 * @param separator - The string where each split should occur. Can be a string or a regular expression.
 * @return the size of the destination deque, aka number of split strings.
 */
size_t roy_string_split(RoyDeque * restrict dest, const RoyString * restrict string, const char * restrict separator);

/**
 * @brief Creates and returns a new string by concatenating all of the substrings in 'deque'.
 * @param separator - the specified separator The dest string will be separated.
 * @note If 'deque' has only one string, then that string will be returned without using the separator.
 */
RoyString * roy_string_join(RoyString * restrict dest, const RoyDeque * restrict deque, const char * restrict separator);


#endif // ROYSTRING_H
