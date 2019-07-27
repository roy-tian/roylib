#ifndef ROYSTR_H
#define ROYSTR_H

#include "royinit.h"

typedef char * RoyStr;
typedef const char * RoyStrLiteral;

#define ROY_STR(str, length) char str[length + 1]; memset(str, '\0', length + 1);

// Converses all characters in 'str' to lowercase.
RoyStr roy_str_to_lower(RoyStr str);

// Converses all characters in 'str' to uppercase.
RoyStr roy_str_to_upper(RoyStr str);

// Reverses 'str' in place.
RoyStr roy_str_reverse(RoyStr str);

// Eliminates all but the first character 'ch' from every consecutive group of equivalent characters from 'str'.
RoyStr roy_str_unique_char(RoyStr str, int ch);

// Replaces all 'old_sub' with 'new_sub'.
// (The behavior is undefined if the length of 'str' grows out of its capacity.)
RoyStr roy_str_replace_all(RoyStr str, RoyStrLiteral old_sub, RoyStrLiteral new_sub, bool sensibility);

// Replaces 'old_sub'(starts at str[old_sub_pos], and is 'old_sub_len' character long) with 'new_sub'.
// (The behavior is undefined if 'str' and 'new_sub' are cascaded.)
RoyStr roy_str_replace_index(RoyStr str, size_t old_sub_position, size_t old_sub_length, RoyStrLiteral new_sub);

// Deprecated: regex is a possible more effective choice.
RoyStr roy_str_replace_between(RoyStr str, RoyStrLiteral pattern_head, RoyStrLiteral pattern_tail, RoyStrLiteral new_sub);

// Replaces all 'old_ch' with 'new_ch'.
RoyStr roy_str_replace_all_char(RoyStr str, int old_ch, int new_ch);

// Replaces all characters meet 'condition' with 'new_ch'.
RoyStr roy_str_replace_all_char_if(RoyStr str, int (* condition)(int), int new_ch);

// Gets the content of line 'line_number'.
// (The behavior is undefined if 'line_number' exceeds 'str', or 'dest' is insufficient or uninitialized.)
RoyStr roy_str_line(RoyStr dest, RoyStrLiteral src, size_t line_number);

// Trims the trailing blanks characters from single-lined string 'str'.
// (The behavior is undefined if 'str' is multi-lined or empty.)
RoyStr roy_str_trim_line(RoyStr str);

// Trims the trailing blanks characters from string 'str'.
// (This function can avoid the undefined behavior of 'trim_line', but runs slower.)
RoyStr roy_str_trim(RoyStr str);

// Returns a string where 'ch' occurs 'count' times,
// e.g. ch = 'a', count = 5, then 'dest' will be 'aaaaa'.
// (The behavior is undefined if the capacity of 'dest' is insufficient.)
RoyStr roy_str_fill_char(RoyStr dest, int ch, size_t count);

// Expands shorthand notations into its equivalent complete list, 
// e.g. 'pattern' = 'a-g', then 'dest' will be 'abcdefg'.
// (The behavior is undefined if the capacity of 'dest' is insufficient.)
RoyStr roy_str_fill_sequence(RoyStr dest, RoyStrLiteral pattern);

// Replaces all tabs with proper number of blanks.
RoyStr roy_str_detab(RoyStr str, size_t tab_size);

// Replaces strings of blanks by the minimum number of tabs and blanks that achieves the same spacing.
RoyStr roy_str_entab(RoyStr str, size_t tab_size);

// Folds the single-lined 'str' into two or more shorter lines
// after the last non-blank character that occurs before 'line_width'.
// The behavior is undefined if 'str' is multi-lined or empty.
RoyStr roy_str_fold_line(RoyStr str, size_t line_width);

// Folds all the long lines in 'str' into two or more shorter lines 
// after the last non-blank character that occurs before 'line_width'.
// (This function can avoid the undefined behavior of 'roy_str_fold_line', but runs slower.)
RoyStr roy_str_fold(RoyStr str, size_t line_width);

// Deletes every character in 'str' that matches any character in 'set'.
RoyStr roy_str_squeeze(RoyStr str, RoyStrLiteral set);

// Counts the occurrence times of 'ch' in 'str'.
size_t roy_str_count_char(RoyStrLiteral str, int ch);

// Counts the occurrence times of 'ch' in 'str' meets 'condition' function.
size_t roy_str_count_char_if(RoyStrLiteral str, int (* condition)(int));

// Counts the occurrence times of string 'sub' in 'str'.
size_t roy_str_count_substring(RoyStrLiteral str, RoyStrLiteral sub, bool sensibility);

// Counts the number of words in 'str'.
size_t roy_str_count_word(RoyStrLiteral str);

// Counts the number of words in 'str' which are 'length'-character long.
// (The behavior is undefined if 'length' is lesser than 1.)
size_t roy_str_count_word_if(RoyStrLiteral str, size_t length);

// Counts lines in 'str'.
size_t roy_str_count_line(RoyStrLiteral str);

// Returns the length of the given line_number.
// (The behavior is undefined if line_number exceeds.)
size_t roy_str_line_length(RoyStrLiteral str, size_t line_number);

// Scans 'str' for any character from 'set', returns the position index of that character,
// or strlen(str), which is an invalid output, indicates not found.
// (Similar to std 'strpbrk' except the return value.)
int roy_str_break_index(RoyStrLiteral str, RoyStrLiteral set);

bool roy_str_match(RoyStrLiteral str, RoyStrLiteral regex);

int roy_str_regex_index(RoyStrLiteral str, RoyStrLiteral regex);

// Reads the content of file at 'path' to 'dest'.
// (This is a convenient function with performance sacrificed.)
RoyStr roy_str_read_from_file(RoyStr dest, RoyStrLiteral path);

// Writes 'src' to the end of file at 'path'.
// (This is a convenient function with performance sacrificed.)
int roy_str_append_to_file(RoyStrLiteral src, RoyStrLiteral path);

// Writes 'src' to the beginning of file at 'path'.
// (This is a convenient function with performance sacrificed.)
int roy_str_write_to_file(RoyStrLiteral src, RoyStrLiteral path);

#endif // ROYSTR_H
