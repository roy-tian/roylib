#ifndef RPREFIX_H
#define RPREFIX_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef void     (* ROperate)   (void *, void *);
typedef bool     (* RCondition) (const void *);
typedef int      (* RCompare)   (const void *, const void *);
typedef uint64_t (* RHash)      (const void *, size_t, uint64_t);

enum RSize {
  R_PTR_SIZE = sizeof(void *),
  R_BUF_SIZE = 0x400
};

enum RNumeral {
  R_BINARY     = 0b10,
  R_OCTAL      =  010,
  R_DECIMAL    =   10,
  R_HEXDECIMAL = 0x10
};

enum RWidth {
  R_BYTE  =  010,
  R_WORD  = 0x10,
  R_DWORD = 0x20,
  R_QWORD = 0x40
};

#endif // RPREFIX_H