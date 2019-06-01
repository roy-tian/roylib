#ifndef ROYINIT_H
#define ROYINIT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

enum NumeralSystem {
  ROY_BINARY     = 2,
  ROY_OCTAL      = 8,
  ROY_DECIMAL    = 10,
  ROY_HEXDECIMAL = 16
};

enum BinaryWidths {
  ROY_BYTE  = 8,
  ROY_WORD  = 16,
  ROY_DWORD = 32,
  ROY_QWORD = 64
};

enum String {
  WORD_CAPACITY        = 31,
  STRING_CAPACITY      = 1023,
  STRING_CAPACITY_HUGE = 65535
};

#define ROY_ARRAY(array)   ((RoyArray *)(array))
#define ROY_QUEUE(queue)   ((RoyQueue *)(queue))
#define ROY_STACK(stack)   ((RoyStack *)(stack))
#define ROY_VECTOR(vector) ((RoyVector *)(vector))
#define ROY_SLIST(slist)   ((RoySList *)(slist))
#define ROY_LIST(list)     ((RoyList *)(list))
#define ROY_DEQUE(deque)   ((RoyDeque *)(deque))
#define ROY_SET(set)       ((RoySet *)(set))
#define ROY_MSET(mset)     ((RoyMSet *)(mset))

#define ROY_ITERATOR(iterate) ((void(*)(void *))(iterate))
#define ROY_CONDITION(condition) ((bool(*)(const void *))(condition))
#define ROY_COMPARE(compare) ((int(*)(const void *, const void *))(compare))

// Formulates an empty character string which named 'str' and is 'size'-character long.
#define ROY_STRING(str, size)         \
        char str[size + 1];           \
        memset(str, '\0', size + 1);

#endif // ROYINIT_H