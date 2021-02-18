#ifndef RHASH_H
#define RHASH_H

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif

#include "rpre.h"

/**
 * @brief MurmurHash2, 64-bit versions, by Austin Appleby
 *
 * The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
 * and endian-ness issues if used across multiple platforms.
 *
 * 64-bit hash for 64-bit platforms
 */
uint64_t MurmurHash2(const void * key, size_t key_size, uint64_t seed);

#endif // RHASH_H