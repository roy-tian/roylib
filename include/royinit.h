#ifndef ROYINIT_H
#define ROYINIT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

enum {
  PTR_SIZE = sizeof(RData)
};

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

typedef       void * RData;
typedef const void * RCData;

typedef void     (* ROperate)   (RData);
typedef bool     (* RCondition) (RCData);
typedef int      (* RCompare)   (RCData, RCData);
typedef uint64_t (* RHash)      (RCData, size_t, uint64_t);

#endif // ROYINIT_H