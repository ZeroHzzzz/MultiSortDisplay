// InsertionSort.hpp
#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <algorithm>  // For std::lower_bound (binary search)
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 插入排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class InsertionSort : public Sort<T> {
   private:
    /**
     * @brief 使用二分查找找到插入位置
     *
     * @param arr 待排序的数组
     * @param left 排序范围的起始位置
     * @param right 排序范围的结束位置
     * @param key 要插入的元素
     * @return 插入位置的索引
     */
    size_t binarySearch(const std::vector<T>& arr,
                        size_t left,
                        size_t right,
                        const T& key) const;

   public:
    /**
     * @brief 执行插入排序
     */
    void sort() override;
};

#endif