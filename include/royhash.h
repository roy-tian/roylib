#ifndef ROYHASH_H
#define ROYHASH_H

#include "royinit.h"

// MurmurHash2, 64-bit versions, by Austin Appleby
// beware of alignment and endianness issues if used across multiple platforms.
uint64_t MurmurHash64A(const void * key, size_t key_size, uint64_t seed);

#endif // ROYHASH_H