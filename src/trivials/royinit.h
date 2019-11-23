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

typedef void     (* ROperate)   (void *);
typedef bool     (* RCondition) (const void *);
typedef int      (* RCompare)   (const void *, const void *);
typedef uint64_t (* RHash)      (const void *, size_t, uint64_t);

enum CommonConstants {
  PTR_SIZE = sizeof(void *)
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


#endif // ROYINIT_H