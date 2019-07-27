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

enum String {
  WORD_CAPACITY       = 31,
  STRING_CAPACITY     = 1023,
  BIG_STRING_CAPACITY = 65535
};

typedef void * RoyElement;
typedef void (* RoyOperate)(RoyElement);
typedef bool (* RoyCondition)(const RoyElement);
typedef int  (* RoyCompare)(const RoyElement, const RoyElement);

#define ROY_ELEMENT(element)     (RoyElement)(element)
#define ROY_OPERATE(operate)     (RoyOperate)(operate)
#define ROY_CONDITION(condition) (RoyCondition)(condition)
#define ROY_COMPARE(compare)     (RoyCompare)(compare)

#define ROY_ARRAY(array)   (RoyArray)(array)
#define ROY_QUEUE(queue)   (RoyQueue)(queue)
#define ROY_STACK(stack)   (RoyStack)(stack)
#define ROY_VECTOR(vector) (RoyVector)(vector)
#define ROY_SLIST(slist)   (RoySList)(slist)
#define ROY_LIST(list)     (RoyList)(list)
#define ROY_DEQUE(deque)   (RoyDeque)(deque)
#define ROY_SET(set)       (RoySet)(set)
#define ROY_MSET(mset)     (RoyMSet)(mset)
#define ROY_MAP(map)       (RoyMap)(map)
#define ROY_MMAP(mmap)     (RoyMMap)(mmap)

#endif // ROYINIT_H