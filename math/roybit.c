#include "roybit.h"

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
