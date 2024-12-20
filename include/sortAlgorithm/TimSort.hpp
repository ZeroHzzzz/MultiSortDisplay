// TimSort.hpp
#ifndef TIMSORT_HPP
#define TIMSORT_HPP

#include <algorithm>
#include <cmath>
#include <vector>
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief TimSort 类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class TimSort : public Sort<T> {
   private:
    const static size_t MIN_RUN = 32;  // 最小块大小，通常选择32

    // 插入排序：对小块进行插入排序
    void insertionSort(size_t left, size_t right);

    // 合并两个已排序的区间
    void merge(size_t left, size_t mid, size_t right);

    // 合并多个块
    void timSortMerge();

    // 创建 runs 并进行插入排序
    void createRuns();

    // TimSort 主排序函数
    void timSort();

   public:
    // 执行 TimSort 排序
    void sort() override;
};

#endif
