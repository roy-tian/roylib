cmake_minimum_required(VERSION 3.0.0)
project(roylib VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_library(roylib
        util/rpre.h roy.h
        array/royarray.h   array/royarray.c
        array/roystack.h   array/roystack.c
        array/royqueue.h   array/royqueue.c
        array/royvector.h  array/royvector.c
        list/royslist.h    list/royslist.c
        list/roylist.h     list/roylist.c
        list/roydeque.h    list/roydeque.c
        tree/royset.h      tree/royset.c
        tree/roymset.h     tree/roymset.c
        tree/roymap.h      tree/roymap.c
        tree/roymmap.h     tree/roymmap.c
        hash/royuset.h     hash/royuset.c
        hash/royumset.h    hash/royumset.c
        hash/royumap.h     hash/royumap.c
        hash/royummap.h    hash/royummap.c
        string/roystr.h    string/roystr.c
        string/roystring.h string/roystring.c
        string/royshell.h  string/royshell.c
        math/roynumber.h   math/roynumber.c
        math/roybit.h      math/roybit.c
        math/roymath.h     math/roymath.c
        util/rhash.h       util/rhash.c
        util/rpair.h       util/rpair.c
        util/rmatch.c      util/rmatch.h
)

target_link_libraries(roylib pcre2-8)
