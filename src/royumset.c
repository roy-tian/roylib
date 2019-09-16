#include "../include/royumset.h"
#include "../include/royuset.h"
#include <math.h>

static uint64_t MurmurHash64A(const void * key, size_t key_size, uint64_t seed);
static bool     prime(size_t number);
static size_t   next_prime(size_t number);

RoyUMSet *
roy_umset_new(size_t      bucket_count,
              size_t      element_size,
              uint64_t    seed,
              uint64_t (* hash)(const void *, size_t, uint64_t),
              int      (* compare)(const void *, const void *)) {
  RoyUMSet * ret    = (RoyUMSet *)malloc(sizeof(RoyUMSet));
  ret->bucket_count = next_prime(bucket_count);
  ret->element_size = element_size;
  ret->size         = 0;
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash64A;
  ret->compare      = compare;
  ret->buckets      = (RoySList **)calloc(roy_umset_bucket_count(ret),
                                          sizeof(RoySList*));
  for (size_t i = 0; i != roy_umset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_umset_delete(RoyUMSet * umset) {
  roy_uset_delete((RoyUSet *)umset);
}

const void *
roy_umset_const_pointer(const RoyUMSet * umset,
                        int              bucket_index,
                        int              bucket_position) {
  return
  roy_uset_const_pointer((RoyUSet *)umset, bucket_index, bucket_position);
}

void *
roy_umset_element(void    * dest,
                 RoyUMSet * umset,
                 int        bucket_index,
                 int        bucket_position) {
  return
  roy_uset_element(dest, (RoyUSet *)umset, bucket_index, bucket_position);
}

size_t
roy_umset_size(const RoyUMSet * umset) {
  return roy_uset_size((RoyUSet *)umset);
}

bool
roy_umset_empty(const RoyUMSet * umset) {
  return roy_uset_empty((RoyUSet *)umset);
}

RoyUMSet *
roy_umset_insert(RoyUMSet  * umset,
                const void * data) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data)];
  roy_slist_push_front(*node, data, umset->element_size);
  umset->size++;
  return umset;
}

RoyUMSet *
roy_umset_erase(RoyUMSet * umset,
                int        bucket_index,
                int        bucket_position) {
  return
  (RoyUMSet *)roy_uset_erase((RoyUSet *)umset, bucket_index, bucket_position);
}

RoyUMSet *
roy_umset_remove(RoyUMSet   * umset,
                 const void * data) {
  return (RoyUMSet *)roy_uset_remove((RoyUSet *)umset, data);
}

const void *
roy_umset_find(const RoyUMSet * umset,
               const void     * data) {
  return roy_uset_find((RoyUSet *)umset, data);
}

RoyUMSet *
roy_umset_clear(RoyUMSet * umset) {
  return (RoyUMSet *)roy_uset_clear((RoyUSet *)umset);
}

size_t
roy_umset_bucket_count(const RoyUMSet * umset) {
  return roy_uset_bucket_count((RoyUSet *)umset);
}

size_t
roy_umset_bucket_size(const RoyUMSet * umset,
                      int              bucket_index) {
  return roy_uset_bucket_size((RoyUSet *)umset, bucket_index);
}

int64_t
roy_umset_bucket(const RoyUMSet * umset,
                 const void     * data) {
  return roy_uset_bucket((RoyUSet *)umset, data);
}

double
roy_umset_load_factor(const RoyUMSet * umset) {
  return roy_uset_load_factor((RoyUSet *)umset);
}

RoyUMSet * roy_umset_rehash(RoyUMSet * umset,
                            size_t     bucket_count,
                            uint64_t   seed) {
  return (RoyUMSet *)roy_uset_rehash((RoyUSet *)umset, bucket_count, seed);
}

void
roy_umset_for_each(RoyUMSet * umset,
                   void    (* operate)(void *)) {
  roy_uset_for_each((RoyUSet *)umset, operate);
}

void
roy_umset_for_which(RoyUMSet * umset,
                    bool    (* condition)(const void *),
                    void    (* operate)        (void *)) {
  roy_uset_for_which((RoyUSet *)umset, condition, operate);
}

/* PRIVATE FUNCTIONS */

static bool
prime(size_t number) {
  if (number < 2 || (number != 2 && number % 2 == 0)) {
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
next_prime(size_t number) {
  while (!prime(number)) {
    number++;
  }
  return number;
}

// MurmurHash2, 64-bit versions, by Austin Appleby
// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.
// 64-bit hash for 64-bit platforms
static uint64_t
MurmurHash64A ( const void * key, size_t key_size, uint64_t seed ) {
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
