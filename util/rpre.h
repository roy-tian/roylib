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


typedef void     (* RDoer)     (void * object, void * user_data);
typedef bool     (* RChecker)  (const void * object);
typedef int      (* RComparer) (const void * lhs, const void * rhs);
typedef uint64_t (* RHash)     (const void * key, size_t key_size, uint64_t seed);

enum RNumber {
  R_PTR_SIZE = sizeof(void *),
  R_BUF_SIZE = 0x400,
  R_BIN      = 0b10,
  R_OCT      =  010,
  R_DEC      =   10,
  R_HEX      = 0x10,
  R_BYTE     =  010,
  R_WORD     = 0x10,
  R_DWORD    = 0x20,
  R_QWORD    = 0x40
};

#endif // RPREFIX_H