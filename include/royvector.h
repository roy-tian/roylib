#ifndef ROYVECTOR_H
#define ROYVECTOR_H

#include <stddef.h>
#include <stdbool.h>

struct _RoyVector {
  void   * data;
  size_t   size;
  size_t   element_size;
  size_t   capacity_unit;
  size_t   steps;
};

// RoyVector 容器: 封装可变长的向量。可根据添加、删除元素的情况自动调整向量的大小。
typedef struct _RoyVector RoyVector;

/* 构造和析构 */

// 初始化一个向量，使其足够存放 'capacity_unit' 个尺寸为 'element_size' 的元素，并返回一个指向该向量的指针。
// 若针对未初始化的 RoyVector 进行其它任意操作，则行为未定义。
RoyVector * roy_vector_new(size_t capacity, size_t element_size);

// 释放 'vector'（包括向量本身和所有的元素）所占用的内存空间。
// 若调用已被本函数销毁的 'vector'，则行为未定义。
// 若初始化的向量在使用完毕后没有由此函数进行销毁，则内存会泄漏。
void roy_vector_delete(RoyVector * vector);

/* 元素访问 */

// 返回一个指向 'vector' 中第 'position' 个元素的 void 指针。（不进行边界检查。）
void * roy_vector_pointer(RoyVector * vector, int position);

// 返回一个指向 'vector' 中第 'position' 个元素的 const void 指针。（不进行边界检查。）
const void * roy_vector_const_pointer(const RoyVector * vector, int position);

// 拷贝 'vector' 中第 'position' 个元素，返回一个指向该拷贝的 void 指针。（进行边界检查，越界返回 NULL。）
// 若 'dest' 未初始化，则行为未定义。
void * roy_vector_element(void * dest, const RoyVector * vector, int position);

// 返回一个指向 'vector' 中第 'position' 个元素的指针，指针具有类型 'element_type'。（进行边界检查，越界返回 NULL。）
#define roy_vector_at(vector, element_type, position)         \
        (position >= 0 && position < vector->size)          ? \
        (element_type*)roy_vector_pointer(vector, position) : \
        NULL

/* 容量 */

// 返回 'vector' 中当前元素总个数。
size_t roy_vector_size(const RoyVector * vector);

// 返回 'vector' 当前的容量，即当前状态下最多可容纳元素的个数。
size_t roy_vector_capacity(const RoyVector * vector);

// 检查 'vector' 当前是否为空，若不存在任何元素，则返回 true，否则返回 false。
bool roy_vector_empty(const RoyVector * vector);

// 检查 'vector' 当前是否已满，若已没有再添加新元素的空间，则返回 true，否则返回 false。
bool roy_vector_full(const RoyVector * vector);

/* MODIFIERS */

// 将 'data' 元素插入 'vector' 的 'position' 位置，原位置的元素依次后移；若向量已满，则自动扩充容量。
// 若 'position' 小于零，则 'data' 插入至向量当前第一个元素之前；若 'position' 达到或超出当前向量长度，则 'data' 插入至向量当前最后一个元素之后。
// 若 'dest' 未初始化，则行为未定义。
RoyVector * roy_vector_insert(RoyVector * vector, int position, const void * data);

// 将 'data' 元素插入至 'vector' 当前最后一个元素之后；若向量已满，则自动扩充容量。
// 若 'dest' 未初始化，则行为未定义。
RoyVector * roy_vector_push_back(RoyVector * vector, const void * data);

// 移除 'vector' 中位于 'position' 处的元素，空位由后续元素依次填充。
// 若 'position' 小于零，则向量当前第一个元素将被移除；若 'position' 达到或超出当前向量长度，则向量当前最后一个元素将被移除。
// 当向量较大且 'position' 较靠前时，本操作性能较差。若对元素排序不敏感，可用 'roy_vector_erase_fast' 代替。
RoyVector * roy_vector_erase(RoyVector * vector, int position);


// 移除 'vector' 中最后一个元素。若当前空位达到 capacity_unit，则向量自动缩小。
RoyVector * roy_vector_pop_back(RoyVector * vector);

// 移除 'vector' 中位于 'position' 处的元素，空位由数组当前最后一个元素填充。若当前空位达到 capacity_unit，则向量自动缩小。
// 若 'position' 小于零，则数组当前第一个元素将被移除；若 'position' 达到或超出数组长度，则数组当前最后一个元素将被移除。
// 一般情况下，本操作性能好于 'roy_vector_erase'，但会打乱元素原有的顺序。
RoyVector * roy_vector_erase_fast(RoyVector * vector, int position);

// 移除 'vector' 中所有的元素，重置容量至初始状态。
RoyVector * roy_vector_clear(RoyVector * vector);

#endif // ROYVECTOR_H