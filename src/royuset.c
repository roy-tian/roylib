#include "../include/royuset.h"

static size_t default_hash(const void * elem, size_t set_size);
static bool default_equal(const void * elem1, const void * elem2);
static size_t next_prime(size_t set_size);