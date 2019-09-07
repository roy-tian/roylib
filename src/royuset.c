#include "../include/royuset.h"
#include <math.h>

static uint64_t MurmurHash64A(const void * key, size_t key_size, uint64_t seed);
static bool     prime(size_t number);
static size_t   next_prime(size_t number);
static bool     valid_bucket_index(const RoyUSet * uset, int bucket_index);

RoyUSet *
roy_uset_new(size_t   bucket_count,
             size_t   element_size,
             uint64_t    seed,
             uint64_t (* hash)(const void *, size_t, uint64_t),
             int      (* compare)(const void *, const void *)) {
  RoyUSet * ret     = (RoyUSet *)malloc(sizeof(RoyUSet));
  ret->bucket_count = next_prime(bucket_count);
  ret->element_size = element_size;
  ret->size         = 0;
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash64A;
  ret->compare      = compare;
  ret->buckets      = (RoySList **)calloc(roy_uset_bucket_count(ret),
                                          sizeof(RoySList*));
  for (size_t i = 0; i != roy_uset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_uset_delete(RoyUSet * uset) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    roy_slist_delete(uset->buckets[i]);
  }
  free(uset->buckets);
  free(uset);
}

const void *
roy_uset_const_pointer(const RoyUSet * uset,
                       int             bucket_index,
                       int             bucket_position) {
  if (!valid_bucket_index(uset, bucket_index)) {
    return NULL;
  }
  const RoySList * iter =
  roy_slist_const_iterator(uset->buckets[bucket_index], bucket_position);
  return iter ? iter->data : NULL;
}

void *
roy_uset_element(void    * dest,
                 RoyUSet * uset,
                 int       bucket_index,
                 int       bucket_position) {
  return valid_bucket_index(uset, bucket_index)         ?
         roy_slist_element(dest,
                           uset->buckets[bucket_index],
                           uset->element_size,
                           bucket_position)             :
         NULL;
}

size_t
roy_uset_size(const RoyUSet * uset) {
  return uset->size;
}

bool
roy_uset_empty(const RoyUSet * uset) {
  return uset->size == 0;
}

RoyUSet *
roy_uset_insert(RoyUSet    * uset,
                const void * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (uset->compare(data, iter->data) == 0) {
      return uset;
    }
  }
  roy_slist_push_front(*node, data, uset->element_size);
  uset->size++;
  return uset;
}

RoyUSet *
roy_uset_erase(RoyUSet * uset,
               int       bucket_index,
               int       bucket_position) {
  if (!valid_bucket_index(uset, bucket_index)) {
    return uset;
  }
  RoySList ** node = &uset->buckets[bucket_index];
  size_t size = roy_slist_size(*node);
  roy_slist_erase(*node, bucket_position);
  size -= roy_slist_size(*node);
  uset->size -= size;
  return uset;
}

RoyUSet *
roy_uset_remove(RoyUSet * uset, const void * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  size_t size = roy_slist_size(*node);
  roy_slist_remove(*node, data, uset->compare);
  size -= roy_slist_size(*node);
  uset->size -= size;
  return uset;
}

const void *
roy_uset_find(const RoyUSet * uset,
              const void    * data) {
  RoySList ** node = &uset->buckets[roy_uset_bucket(uset, data)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (uset->compare(data, iter->data) == 0) {
      return iter->data;
    }
  }
  return NULL;
}

RoyUSet *
roy_uset_clear(RoyUSet * uset) {
  for (size_t i = 0; i != roy_uset_bucket_count(uset); i++) {
    roy_slist_clear(uset->buckets[i]);
  }
  return uset;
}

size_t
roy_uset_bucket_count(const RoyUSet * uset) {
  return uset->bucket_count;
}

size_t
roy_uset_bucket_size(const RoyUSet * uset, int bucket_index) {
  return roy_slist_size(uset->buckets[bucket_index]);
}

int64_t
roy_uset_bucket(const RoyUSet * uset, const void * data) {
  return uset->hash(data, uset->element_size, uset->seed) %
         roy_uset_bucket_count(uset);
}

double
roy_uset_load_factor(const RoyUSet * uset) {
  return (double)roy_uset_size(uset) / (double)roy_uset_bucket_count(uset);
}

RoyUSet * roy_uset_rehash(RoyUSet * uset, size_t bucket_count, uint64_t seed) {
  return uset;
}

void
roy_uset_for_each(RoyUSet * uset,
                  void   (* operate)(void * data)) {
  for (size_t i = 0; i != uset->bucket_count; i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_each(uset->buckets[i], operate);
    }
  }
}

void
roy_uset_for_which(RoyUSet * uset,
                   bool   (* condition)(const void *),
                   void   (* operate)(void *)) {
  for (size_t i = 0; i != uset->bucket_count; i++) {
    if (uset->buckets[i] && !roy_slist_empty(uset->buckets[i])) {
      roy_slist_for_which(uset->buckets[i], condition, operate);
    }
  }
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
  const uint64_t m = 0xc6a4a7935bd1e995ULL;
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

static bool
valid_bucket_index(const RoyUSet * uset,
                   int             bucket_index) {
  return bucket_index >= 0 && bucket_index < roy_uset_bucket_count(uset);
}
