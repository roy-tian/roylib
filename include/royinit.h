#ifndef ROYINIT_H
#define ROYINIT_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#define NDEBUG

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

#endif // ROYINIT_H