CMAKE_MINIMUM_REQUIRED (VERSION 3.14)

PROJECT (roylib C)

SET (CMAKE_C_STANDARD 11)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY (roylib
             src/roystring.c
             src/roynumber.c
             src/royarray.c
             src/royvector.c
             src/roystack.c
             src/royqueue.c
             src/royslist.c
             src/roylist.c
             src/roydeque.c
             src/roymap.c)