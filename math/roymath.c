#include "roymath.h"
#include <time.h>

bool
roy_uint_prime(uint64_t number) {
  if (number < 2 || (number != 2 && number % 2 == 0)) {
    return false;
  }
  for (size_t i = 3; i <= number / 2; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

uint64_t
roy_uint_prime_next(uint64_t number) {
  while (!roy_uint_prime(number)) {
    number++;
  }
  return number;
}

void
roy_random_new(void) {
  srand((unsigned)time(NULL));
}

uint64_t
roy_random_next(uint64_t min,
                uint64_t max) {
  return rand() % max + min;
}
