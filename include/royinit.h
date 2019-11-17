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

const uint64_t GAPS[] = {
             1,              5,             19,             41,            109,
           209,            505,            929,           2161,           3905,
          8929,          16001,          36289,          64769,         146305,
        260609,         587521,        1045505,        2354689,        4188161,
       9427969,       16764929,       37730305,       67084289,      150958081,
     268386305,      603906049,     1073643521,     2415771649,     4294770689,
    9663381505,    17179475969,    38654115841,    68718690305,   154617643009,
  274876334081,   618472931329,  1099508482049,  2473896443905,  4398040219649,
 9895595212801, 17592173461505, 39582399725569, 70368719011841, 158329636651009  
};

#endif // ROYINIT_H