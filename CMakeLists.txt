cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
  /usr/local/include
  C:/Apps/MSYS/mingw64/x86_64-w64-mingw32/include
)

add_library(roylib
  roy.h                include/royinit.h
  include/roystr.h     include/roystr.c
  include/roystring.h  include/roystring.c
  include/roynumber.h  include/roynumber.c
  include/royshell.h   include/royshell.c
  include/roypointer.h include/roypointer.c
  include/royarray.h   include/royarray.c
  include/royvector.h  include/royvector.c
  include/roystack.h   include/roystack.c
  include/royqueue.h   include/royqueue.c
  include/royslist.h   include/royslist.c
  include/roylist.h    include/roylist.c
  include/roydeque.h   include/roydeque.c
  include/royset.h     include/royset.c
  include/roymset.h    include/roymset.c
  include/roymap.h     include/roymap.c
  include/roymmap.h    include/roymmap.c
  include/royuset.h    include/royuset.c
  include/royumset.h   include/royumset.c
)

target_link_libraries(roylib pcre)
