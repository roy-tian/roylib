#ifndef ROYSTRING_H
#define ROYSTRING_H

#include "royinit.h"

// Converses all characters in 'str' to lowercase.
char * roy_string_to_lower(char * str);

// Converses all characters in 'str' to uppercase.
char * roy_string_to_upper(char * str);

// Reverses 'str' in place.
char * roy_string_reverse(char * str);

// Eliminates all but the first character 'ch' from every consecutive group of equivalent characters from 'str'.
char * roy_string_unique_char(char * str, int ch);

// Replaces all 'old_sub' with 'new_sub'.
// (The behavior is undefined if the length of 'str' grows out of its capacity.)
char * roy_string_replace_all(char * str, const char * old_sub, const char * new_sub, bool sensibility);

// Replaces 'old_sub'(starts at str[old_sub_pos], and is 'old_sub_len' character long) with 'new_sub'.
// (The behavior is undefined if 'str' and 'new_sub' are cascaded.)
char * roy_string_replace_index(char * str, size_t old_sub_position, size_t old_sub_length, const char * new_sub);

// Deprecated: regex is a possible more effective choice.
char * roy_string_replace_between(char * str, const char * pattern_head, const char * pattern_tail, const char * new_sub);

// Replaces all 'old_ch' with 'new_ch'.
char * roy_string_replace_all_char(char * str, int old_ch, int new_ch);

// Replaces all characters meet 'condition' with 'new_ch'.
char * roy_string_replace_all_char_if(char * str, int (* condition)(int), int new_ch);

// Gets the content of line 'line_number'.
// (The behavior is undefined if 'line_number' exceeds 'str', or 'dest' is insufficient or uninitialized.)
char * roy_string_line(char * dest, const char * src, size_t line_number);

// Trims the trailing blanks characters from single-lined string 'str'.
// (The behavior is undefined if 'str' is multi-lined or empty.)
char * roy_string_trim_line(char * str);

// Trims the trailing blanks characters from string 'str'.
// (This function can avoid the undefined behavior of 'trim_line', but runs slower.)
char * roy_string_trim(char * str);

// Returns a string where 'ch' occurs 'count' times,
// e.g. ch = 'a', count = 5, then 'dest' will be 'aaaaa'.
// (The behavior is undefined if the capacity of 'dest' is insufficient.)
char * roy_string_fill_char(char * dest, int ch, size_t count);

// Expands shorthand notations into its equivalent complete list, 
// e.g. 'pattern' = 'a-g', then 'dest' will be 'abcdefg'.
// The behavior is undefined if the capacity of 'dest' is insufficient.
char * roy_string_fill_sequence(char * dest, const char * pattern);

// Replaces all tabs with proper number of blanks.
char * roy_string_detab(char * str, size_t tab_size);

// Replaces strings of blanks by the minimum number of tabs and blanks that achieves the same spacing.
char * roy_string_entab(char * str, size_t tab_size);

// Folds the single-lined 'str' into two or more shorter lines
// after the last non-blank character that occurs before 'line_width'.
// The behavior is undefined if 'str' is multi-lined or empty.
char * roy_string_fold_line(char * str, size_t line_width);

// Folds all the long lines in 'str' into two or more shorter lines 
// after the last non-blank character that occurs before 'line_width'.
// (This function can avoid the undefined behavior of 'roy_string_fold_line', but runs slower.)
char * roy_string_fold(char * str, size_t line_width);

// Deletes every character in 'str' that matches any character in 'set'.
char * roy_string_squeeze(char * str, const char * set);

// Counts the occurrence times of 'ch' in 'str'.
size_t roy_string_count_char(const char * str, int ch);

// Counts the occurrence times of 'ch' in 'str' meets 'condition' function.
size_t roy_string_count_char_if(const char * str, int (* condition)(int));

// Counts the occurrence times of string 'sub' in 'str'.
size_t roy_string_count_substring(const char * str, const char * sub, bool sensibility);

// Counts the number of words in 'str'.
size_t roy_string_count_word(const char * str);

// Counts the number of words in 'str' which are 'length'-character long.
// (The behavior is undefined if 'length' is lesser than 1.)
size_t roy_string_count_word_if(const char * str, size_t length);

// Counts lines in 'str'.
size_t roy_string_count_line(const char * str);

// Returns the length of the given line_number.
// (The behavior is undefined if line_number exceeds.)
size_t roy_string_line_length(const char * str, size_t line_number);

// Scans 'str' for any character from 'set', returns the position index of that character,
// or strlen(str), which is an invalid output, indicates not found.
// (Similar to std 'strpbrk' except the return value.)
int roy_string_break_index(const char * str, const char * set);

// Reads the content of file at 'path' to 'dest'.
// (This is a convenient function with performance sacrificed.)
char * roy_string_read_from_file(char * dest, const char * path);

// Writes 'src' to the end of file at 'path'.
// (This is a convenient function with performance sacrificed.)
int roy_string_append_to_file(const char * src, const char * path);

// Writes 'src' to the beginning of file at 'path'.
// (This is a convenient function with performance sacrificed.)
int roy_string_write_to_file(const char * src, const char * path);

#endif // ROYSTRING_H
