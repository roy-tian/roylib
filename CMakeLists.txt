cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(
        /usr/local/include
        C:/Devs/MSYS/mingw64/lib/gcc/x86_64-w64-mingw32/*/include
)

add_library(roylib
        util/royinit.h    roy.h
        array/royarray.h  array/royarray.c
        array/roystack.h  array/roystack.c
        array/royqueue.h  array/royqueue.c
        array/royvector.h array/royvector.c
        list/royslist.h   list/royslist.c
        list/roylist.h    list/roylist.c
        list/roydeque.h   list/roydeque.c
        tree/royset.h     tree/royset.c
        tree/roymset.h    tree/roymset.c
        tree/roymap.h     tree/roymap.c
        tree/roymmap.h    tree/roymmap.c
        hash/hash.h       hash/hash.c
        hash/royuset.h    hash/royuset.c
        hash/royumset.h   hash/royumset.c
        hash/royumap.h    hash/royumap.c
        hash/royummap.h   hash/royummap.c
        util/roystring.h  util/roystring.c
        util/royshell.h   util/royshell.c
        util/roynumber.h  util/roynumber.c
        util/roystr.h     util/roystr.c
        util/roypair.h    util/roypair.c
        util/roymatch.c   util/roymatch.h)

target_link_libraries(roylib pcre2-8)
