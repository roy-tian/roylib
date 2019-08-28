#include "../include/royumset.h"
#include <math.h>

static uint64_t MurmurHash64A(const void * key, size_t key_size, uint64_t seed);
static bool     prime(size_t number);
static size_t   next_prime(size_t number);
static bool     valid_bucket_index(const RoyUMSet * umset, int bucket_index);

RoyUMSet *
roy_umset_new(size_t     bucket_count,
              size_t      element_size,
              uint64_t    seed,
              uint64_t (* hash)(const void *, size_t, uint64_t),
              int      (* compare)(const void *, const void *)) {
  RoyUMSet * ret    = ROY_UMSET(malloc(sizeof(RoyUMSet)));
  ret->bucket_count = next_prime(bucket_count);
  ret->element_size = element_size;
  ret->size         = 0;
  ret->seed         = seed;
  ret->hash         = hash ? hash : MurmurHash64A;
  ret->compare      = compare;
  ret->buckets      = (RoySList **)calloc(ret->bucket_count, sizeof(RoySList*));
  for (size_t i = 0; i != roy_umset_bucket_count(ret); i++) {
    ret->buckets[i] = roy_slist_new();
  }
  return ret;
}

void
roy_umset_delete(RoyUMSet * umset) {
  for (size_t i = 0; i != roy_umset_bucket_count(umset); i++) {
    roy_slist_delete(umset->buckets[i]);
  }
  free(umset->buckets);
  free(umset);
}

const void *
roy_umset_const_pointer(const RoyUMSet * umset,
                        int             bucket_index,
                        int             bucket_position) {
  if (!valid_bucket_index(umset, bucket_index)) {
    return NULL;
  }
  const RoySList * iter =
  roy_slist_const_iterator(umset->buckets[bucket_index], bucket_position);
  return iter ? iter->data : NULL;
}

void *
roy_umset_element(void    * dest,
                 RoyUMSet * umset,
                 int       bucket_index,
                 int       bucket_position) {
  return valid_bucket_index(umset, bucket_index)        ?
         roy_slist_element(dest,
                           umset->buckets[bucket_index],
                           umset->element_size,
                           bucket_position)             :
         NULL;
}

size_t
roy_umset_size(const RoyUMSet * umset) {
  return umset->size;
}

bool
roy_umset_empty(const RoyUMSet * umset) {
  return umset->size == 0;
}

RoyUMSet *
roy_umset_insert(RoyUMSet    * umset,
                const void * data) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data)];
  roy_slist_push_front(*node, data, umset->element_size);
  umset->size++;
  return umset;
}

RoyUMSet *
roy_umset_erase(RoyUMSet * umset,
               int       bucket_index,
               int       bucket_position) {
  if (!valid_bucket_index(umset, bucket_index)) {
    return umset;
  }
  RoySList ** node = &umset->buckets[bucket_index];
  size_t size = roy_slist_size(*node);
  roy_slist_erase(*node, bucket_position);
  size -= roy_slist_size(*node);
  umset->size -= size;
  return umset;
}

RoyUMSet *
roy_umset_remove(RoyUMSet * umset, const void * data) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data)];
  size_t size = roy_slist_size(*node);
  roy_slist_remove(*node, data, umset->compare);
  size -= roy_slist_size(*node);
  umset->size -= size;
  return umset;
}

const void *
roy_umset_find(const RoyUMSet * umset,
              const void    * data) {
  RoySList ** node = &umset->buckets[roy_umset_bucket(umset, data)];
  for (RoySList * iter = roy_slist_begin(*node); iter; iter = iter->next) {
    if (umset->compare(data, iter->data) == 0) {
      return iter->data;
    }
  }
  return NULL;
}

RoyUMSet *
roy_umset_clear(RoyUMSet * umset) {
  for (size_t i = 0; i != roy_umset_bucket_count(umset); i++) {
    roy_slist_clear(umset->buckets[i]);
  }
  return umset;
}

size_t
roy_umset_bucket_count(const RoyUMSet * umset) {
  return umset->bucket_count;
}

size_t
roy_umset_bucket_size(const RoyUMSet * umset, int bucket_index) {
  return roy_slist_size(umset->buckets[bucket_index]);
}

int64_t
roy_umset_bucket(const RoyUMSet * umset, const void * data) {
  return umset->hash(data, umset->element_size, umset->seed) %
         roy_umset_bucket_count(umset);
}

double
roy_umset_load_factor(const RoyUMSet * umset) {
  return (double)roy_umset_size(umset) / (double)roy_umset_bucket_count(umset);
}

RoyUMSet * roy_umset_rehash(RoyUMSet * umset, size_t bucket_count, uint64_t seed) {
  return umset;
}

void
roy_umset_for_each(RoyUMSet * umset,
                  void   (* operate)(void * data)) {
  for (size_t i = 0; i != umset->bucket_count; i++) {
    if (umset->buckets[i] && !roy_slist_empty(umset->buckets[i])) {
      roy_slist_for_each(umset->buckets[i], operate);
    }
  }
}

void
roy_umset_for_which(RoyUMSet * umset,
                   bool   (* condition)(const void *),
                   void   (* operate)(void *)) {
  for (size_t i = 0; i != umset->bucket_count; i++) {
    if (umset->buckets[i] && !roy_slist_empty(umset->buckets[i])) {
      roy_slist_for_which(umset->buckets[i], condition, operate);
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
valid_bucket_index(const RoyUMSet * umset,
                   int             bucket_index) {
  return bucket_index >= 0 && bucket_index < roy_umset_bucket_count(umset);
}
