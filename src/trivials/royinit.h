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
  R_PTR_SIZE = sizeof(void *)
};

enum NumeralSystem {
  R_BINARY     = 2,
  R_OCTAL      = 8,
  R_DECIMAL    = 10,
  R_HEXDECIMAL = 16
};

enum BinaryWidths {
  R_BYTE  = 8,
  R_WORD  = 16,
  R_DWORD = 32,
  R_QWORD = 64
};

#endif // ROYINIT_H