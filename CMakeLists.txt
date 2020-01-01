cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/include)

add_library(roylib
  src/trivials/royinit.h   roy.h
  src/trivials/roystr.h    src/trivials/roystr.c
  src/trivials/roynumber.h src/trivials/roynumber.c
  src/trivials/roypair.h   src/trivials/roypair.c
  src/trivials/hash.h      src/trivials/hash.c
  src/trivials/shellsort.h src/trivials/shellsort.c
  src/royarray.h  src/royarray.c
  src/roystack.h  src/roystack.c
  src/royqueue.h  src/royqueue.c
  src/royvector.h src/royvector.c
  src/royslist.h  src/royslist.c
  src/roylist.h   src/roylist.c
  src/roydeque.h  src/roydeque.c
  src/royset.h    src/royset.c
  src/roymset.h   src/roymset.c
  src/roymap.h    src/roymap.c
  src/roymmap.h   src/roymmap.c
  src/royuset.h   src/royuset.c
  src/royumset.h  src/royumset.c
  src/royumap.h   src/royumap.c
  src/royummap.h  src/royummap.c
  src/roystring.h src/roystring.c
  src/royshell.h  src/royshell.c
)

target_link_libraries(roylib pcre)
