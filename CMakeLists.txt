CMAKE_MINIMUM_REQUIRED (VERSION 3.13)

PROJECT (roylib C)

SET (CMAKE_C_STANDARD 11)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY (roylib
             src/roystring.c include/roystring.h
             src/roynumber.c include/roynumber.h
             src/royarray.c  include/royarray.h
             src/royvector.c include/royvector.h
             src/royslist.c  include/royslist.h
             src/roylist.c   include/roylist.h
             src/roydeque.c  include/roydeque.h
            )