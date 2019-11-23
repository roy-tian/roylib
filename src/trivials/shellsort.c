#include "shellsort.h"

int
gap_index(size_t n_elements) {
  int index = 0;
  while (!(GAPS[index] >= n_elements && GAPS[index + 1] <= n_elements)) {
    index++;
  }
  return index;
}