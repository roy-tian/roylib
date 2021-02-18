#ifndef ROYBIT_H
#define ROYBIT_H

#include "../util/rpre.h"

/**
 * @brief Returns a string with the 'count' bits that begin at position 'position'
 *        set to the rightmost 'count' bits of 'src', the other bits are left unchanged.
 * @param src - the number to copy from.
 * @param position - position of the first bit to include.
 * @param count - length of the bit segment.
 */
uint64_t roy_uint_set_bits(uint64_t * dest, uint64_t src, size_t position, size_t count);

/**
 * @brief Inverts a specified segment in number, (i.e., 1 changed into 0 and vice versa),
 *        the other bits are left unchanged.
 * @param position - position of the first bit to include.
 * @param count - length of the bit segment.
 */
uint64_t roy_uint_invert(uint64_t * number, size_t position, size_t count);

/**
 * @brief Rotates 'width'-width unsigned integer 'number' to right by 'steps' bit position.
 * @param steps - number of bit to be rotated.
 * @param width - width of 'number'.
 */
uint64_t roy_uint_ror(uint64_t * number, size_t steps, size_t width);

/**
 * @brief Rotates 'width'-width unsigned integer 'number' to left by 'steps' bit position.
 * @param steps - number of bit to be rotated.
 * @param width - width of 'number'.
 */
uint64_t roy_uint_rol(uint64_t * number, size_t steps, size_t width);

/// @brief Counts '1' bits in unsigned integer 'number'.
size_t roy_uint_count_bit(uint64_t number);

#endif // ROYBIT_H