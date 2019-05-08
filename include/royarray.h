#ifndef ROYARRAY_H
#define ROYARRAY_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyArray {
  // 存放数组中的元素
  void   * data;
  // 数组中元素的个数
  size_t   size;
  // 数组中元素的大小
  size_t   element_size;
  // 数组的容量（最多能存放的元素个数）
  size_t   capacity;
};

// RoyArray 容器: 封装固定尺寸的数组。
typedef struct _RoyArray RoyArray;

/* 构造和析构 */

// 初始化一个数组，使其足够存放 'capacity' 个尺寸为 'element_size' 的元素，并返回一个指向该数组的指针。
// 若针对未初始化的 RoyArray 进行其它任意操作，则行为未定义。
RoyArray * roy_array_new(size_t capacity, size_t element_size);

// 释放 'array'（包括数组本身和所有的元素）所占用的内存空间。
// 若调用已被本函数销毁的 'array'，则行为未定义。
// 若初始化的数组在使用完毕后没有由此函数进行销毁，则内存会泄漏。
void roy_array_delete(RoyArray * array);

/* 成员访问 */

// 返回一个指向 'array' 中第 'position' 个元素的 void 指针。（不进行边界检查。）
void * roy_array_pointer(RoyArray * array, int position);

// 返回一个指向 'array' 中第 'position' 个元素的 const void 指针。（不进行边界检查。）
const void * roy_array_const_pointer(const RoyArray * array, int position);

// 拷贝 'array' 中第 'position' 个元素，返回一个指向该拷贝的 void 指针。（进行边界检查，越界返回 NULL。）
// 若 'dest' 未初始化，则行为未定义。
void * roy_array_element(void * dest, const RoyArray * array, int position);

// 返回一个指向 'array' 中第 'position' 个元素的指针，指针具有类型 'element_type'。（进行边界检查，越界返回 NULL。）
#define roy_array_at(array, element_type, position)           \
        (position >= 0 && position < array->size) ?           \
        ((element_type*)roy_array_pointer(array, position)) : \
        NULL

/* 容量 */

// 返回 'array' 中当前元素总个数。
size_t roy_array_size(const RoyArray * array);

// 返回 'array' 的容量，即最多可容纳元素的个数。
size_t roy_array_capacity(const RoyArray * array);

// 检查 'array' 当前是否为空，若不存在任何元素，则返回 true，否则返回 false。
bool roy_array_empty(const RoyArray * array);

// 检查 'array' 当前是否已满，若已没有再添加新元素的空间，则返回 true，否则返回 false。
bool roy_array_full(const RoyArray * array);

/* 修改 */

// 当数组未满时，将 'data' 元素插入 'array' 的 'position' 位置，原位置的元素依次后移；若当前数组已满，则不进行任何操作。
// 若 'position' 小于零，则 'data' 插入至数组当前第一个元素之前；若 'position' 达到或超出当前数组长度，则 'data' 插入至数组当前最后一个元素之后。
// 若 'dest' 未初始化，则行为未定义。
RoyArray * roy_array_insert(RoyArray * array, int position, const void * data);

// 当数组未满时，将 'data' 元素插入至 'array' 当前最后一个元素之后；若当前数组已满，则不进行任何操作。
// 若 'dest' 未初始化，则行为未定义。
RoyArray * roy_array_push_back(RoyArray * array, const void * data);

// 移除 'array' 中位于 'position' 处的元素，空位由后续元素依次填充。
// 若 'position' 小于零，则数组当前第一个元素将被移除；若 'position' 达到或超出当前数组长度，则数组当前最后一个元素将被移除。
// 当数组较大且 'position' 较靠前时，本操作性能较差。若对元素排序不敏感，可用 'roy_array_erase_fast' 代替。
RoyArray * roy_array_erase(RoyArray * array, int position);

// 移除 'array' 中位于 'position' 处的元素，空位由数组当前最后一个元素填充。
// 若 'position' 小于零，则数组当前第一个元素将被移除；若 'position' 达到或超出数组长度，则数组当前最后一个元素将被移除。
// 一般情况下，本操作性能好于 'roy_array_erase'，但会打乱元素原有的顺序。
RoyArray * roy_array_erase_fast(RoyArray * array, int position);

// 移除 'array' 中最后一个元素。
RoyArray * roy_array_pop_back(RoyArray * array);

// 移除 'array' 中所有的元素。
RoyArray * roy_array_clear(RoyArray * array);

/* 遍历 */

#define ROY_ITERATE_FUNC(operate) (void(*)(void *))(operate)
#define ROY_CONDITION_FUNC(condition) (bool(*)(const void *))(condition)

// 使用 'operate' 函数遍历 'array' 中所有的元素。 
void roy_array_for_each(RoyArray * array, void(* iterate)(void *));

// 使用 'operate' 函数遍历 'array' 中所有符合 'condition'（即调用它返回 true）的元素。 
void roy_array_for_which(RoyArray * array, bool(* condition)(const void *), void(* operate)(void *));

#endif // ROYARRAY_H