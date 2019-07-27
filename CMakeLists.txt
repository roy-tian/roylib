cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(roylib
            src/roystr.c
            src/roystring.c
            src/roynumber.c
            src/royshell.c
            src/roypointer.c
            src/royarray.c
            src/royvector.c
            src/roystack.c
            src/royqueue.c
            src/royslist.c
            src/roylist.c
            src/roydeque.c
            src/royset.c
            src/roymset.c
            src/roymap.c
            src/roymmap.c)

target_link_libraries(roylib pcre)