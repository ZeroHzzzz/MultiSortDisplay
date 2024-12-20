// HeapSort.hpp
#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <vector>
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 堆排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class HeapSort : public Sort<T> {
   private:
    /**
     * @brief 调整堆的大小
     *
     * @param arr 待排序的数组
     * @param n 数组大小
     * @param i 当前节点的索引
     */
    void heapify(std::vector<T>& arr, size_t n, size_t i);

   public:
    /**
     * @brief 执行堆排序
     */
    void sort() override;
};

#endif
