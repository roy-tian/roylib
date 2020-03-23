#include "hash.h"

uint64_t
MurmurHash2(const void * key,
            size_t       key_size,
            uint64_t     seed) {
  const uint64_t m = 0Xc6a4a7935bd1e995ULL;
  const uint64_t r = 47ULL;
  const uint64_t * data = (const uint64_t *)key;
  const uint64_t * end = data + (key_size / 8);
  uint64_t h = seed ^ (key_size * m);

  while (data != end) {
    uint64_t k = *data++;

    k *= m;
    k ^= k >> r;
    k *= m;

    h ^= k;
    h *= m;
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(key_size & 7ULL) {
    case 7: h ^= (uint64_t)(data2[6]) << 48ULL;
    case 6: h ^= (uint64_t)(data2[5]) << 40ULL;
    case 5: h ^= (uint64_t)(data2[4]) << 32ULL;
    case 4: h ^= (uint64_t)(data2[3]) << 24ULL;
    case 3: h ^= (uint64_t)(data2[2]) << 16ULL;
    case 2: h ^= (uint64_t)(data2[1]) << 8ULL;
    case 1: h ^= (uint64_t)(data2[0]);
      h *= m;
  };

  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}