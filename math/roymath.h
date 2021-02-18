#ifndef ROYMATH_H
#define ROYMATH_H

#include "../util/rpre.h"

/// @brief Tests whether the given 'number' is a prime number.
bool roy_uint_prime(uint64_t number);

/// @brief Returns the next prime number nearest to the given 'number'.
uint64_t roy_uint_prime_next(uint64_t number);

/// @brief Seeds the stdlib version generator.
// TODO write a effective version of random func.
void roy_random_new(void);

/// @brief Generates a pseudo-random integer N ∈ [min, max).
// TODO write a effective version of random func.
uint64_t roy_random_next(uint64_t min, uint64_t max);

#endif //ROYLIB_ROYMATH_H
