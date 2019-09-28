cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
  /usr/local/include
  C:/Apps/MSYS/mingw64/x86_64-w64-mingw32/include
)

add_library(roylib
  include/royinit.h    roy.h
  include/roystr.h     src/roystr.c
  include/roystring.h  src/roystring.c
  include/roynumber.h  src/roynumber.c
  include/royshell.h   src/royshell.c
  include/roypointer.h src/roypointer.c
  include/royarray.h   src/royarray.c
  include/royvector.h  src/royvector.c
  include/roystack.h   src/roystack.c
  include/royqueue.h   src/royqueue.c
  include/royslist.h   src/royslist.c
  include/roylist.h    src/roylist.c
  include/roydeque.h   src/roydeque.c
  include/royset.h     src/royset.c
  include/roymset.h    src/roymset.c
  include/roymap.h     src/roymap.c
  include/roymmap.h    src/roymmap.c
  include/royuset.h    src/royuset.c
  include/royumset.h   src/royumset.c
  include/royumap.h    src/royumap.c
  include/royummap.h   src/royummap.c)

target_link_libraries(roylib pcre)
