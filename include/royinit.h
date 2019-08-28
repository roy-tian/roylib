#ifndef ROYINIT_H
#define ROYINIT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

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

#define ROY_STR(str, length) char str[length + 1]; memset(str, '\0', length + 1);

#define ROY_OPERATE(operate)     (void(*)(void *))(operate)
#define ROY_CONDITION(condition) (bool(*)(const void *))(condition)
#define ROY_COMPARE(compare)     (int (*)(const void *, const void *))(compare)

#define ROY_ARRAY(array)   (RoyArray *)(array)
#define ROY_QUEUE(queue)   (RoyQueue *)(queue)
#define ROY_STACK(stack)   (RoyStack *)(stack)
#define ROY_VECTOR(vector) (RoyVector *)(vector)
#define ROY_SLIST(slist)   (RoySList *)(slist)
#define ROY_LIST(list)     (RoyList *)(list)
#define ROY_DEQUE(deque)   (RoyDeque *)(deque)
#define ROY_SET(set)       (RoySet *)(set)
#define ROY_MSET(mset)     (RoyMSet *)(mset)
#define ROY_MAP(map)       (RoyMap *)(map)
#define ROY_MMAP(mmap)     (RoyMMap *)(mmap)
#define ROY_USET(uset)     (RoyUSet *)(uset)
#define ROY_UMSET(umset)   (RoyUMSet *)(umset)


#endif // ROYINIT_H