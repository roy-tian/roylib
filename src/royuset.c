#include "../include/royuset.h"
#include "../include/royslist.h"
#include <math.h>

static uint64_t MurmurHash64A(const void * key, size_t key_size, uint64_t seed);
static bool default_equal(const void * elem1, const void * elem2, size_t element_size);
static bool prime(size_t number);
static size_t next_prime(size_t capacity);

RoyUSet *
roy_uset_new(size_t     capacity,
             size_t     element_size,
             uint64_t   hash_seed,
             size_t  (* hash)(const void *, size_t, size_t),
             bool    (* equal)(const void *, const void *, size_t)) {
  RoyUSet * ret     = ROY_USET(malloc(sizeof(RoyUSet)));
  ret->capacity     = next_prime(capacity);
  ret->element_size = element_size;
  ret->hash_seed    = hash_seed;
  ret->hash         = hash ? hash : MurmurHash64A;
  ret->equal        = equal ? equal : default_equal;
  ret->table        = roy_vector_new(ret->capacity, sizeof(RoySList**));
  return ret;
}

void roy_uset_delete(RoyUSet * uset) {
  for (size_t i = 0; i != roy_vector_size(uset->table); i++) {
    if (*roy_vector_at(uset->table, RoySList*, i)) {
      roy_slist_delete(*roy_vector_at(uset->table, RoySList*, i));
    }
  }
  roy_vector_delete(uset->table);
  free(uset);
}



/* PRIVATE FUNCTIONS */

static bool
prime(size_t number) {
  if (number < 2 || number != 2 && number % 2 == 0) {
    return false;
  }
  for (size_t i = 3; i <= (size_t)sqrt((double)number); i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}

static size_t
next_prime(size_t capacity) {
  while (!prime(capacity)) {
    capacity++;
  }
  return capacity;
}

// MurmurHash2, 64-bit versions, by Austin Appleby
// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment 
// and endian-ness issues if used across multiple platforms.
// 64-bit hash for 64-bit platforms
static uint64_t
MurmurHash64A ( const void * key, size_t key_size, uint64_t seed ) {
  const uint64_t m = 0xc6a4a7935bd1e995ULL;
  const int r = 47;

  uint64_t h = seed ^ (key_size * m);

  const uint64_t * data = (const uint64_t *)key;
  const uint64_t * end = data + (key_size / 8);

  while (data != end) {
    uint64_t k = *data++;

    k *= m; 
    k ^= k >> r; 
    k *= m; 
    
    h ^= k;
    h *= m; 
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(key_size & 7) {
  case 7: h ^= (uint64_t)(data2[6]) << 48;
  case 6: h ^= (uint64_t)(data2[5]) << 40;
  case 5: h ^= (uint64_t)(data2[4]) << 32;
  case 4: h ^= (uint64_t)(data2[3]) << 24;
  case 3: h ^= (uint64_t)(data2[2]) << 16;
  case 2: h ^= (uint64_t)(data2[1]) << 8;
  case 1: h ^= (uint64_t)(data2[0]);
          h *= m;
  };
 
  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
} 

static bool
default_equal(const void * key1, const void * key2, size_t key_size) {
  const char * pkey1 = key1;
  const char * pkey2 = key2;
  while (key_size-- != 0) {
    if (*pkey1++ != *pkey2++) {
      return false;
    }
  }
  return true;
}