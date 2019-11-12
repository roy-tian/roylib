#ifndef ROYHASH_H
#define ROYHASH_H

#include "royinit.h"

// MurmurHash2, 64-bit versions, by Austin Appleby
//
// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.
//
// 64-bit hash for 64-bit platforms
uint64_t MurmurHash2(const void * key, size_t key_size, uint64_t seed);

#endif // ROYHASH_H