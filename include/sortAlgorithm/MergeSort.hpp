// MergeSort.hpp
#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 归并排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class MergeSort : public Sort<T> {
   private:
    /**
     * @brief 自定义的合并函数，用来合并两个已排序的子数组
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param mid 中间位置（左子数组的末尾）
     * @param right 右子数组的末尾位置
     */
    void merge(std::vector<T>& arr, size_t left, size_t mid, size_t right);

    /**
     * @brief 递归拆分数组并执行合并操作
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param right 右子数组的末尾位置
     */
    void mergeSort(std::vector<T>& arr, size_t left, size_t right);

   public:
    /**
     * @brief 实现归并排序的排序算法
     */
    void sort() override;
};

#endif
