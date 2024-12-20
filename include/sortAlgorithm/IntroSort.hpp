// IntroSort.hpp
#ifndef INTROSORT_HPP
#define INTROSORT_HPP

#include <algorithm>  // For std::swap and std::partition
#include <cmath>      // For log2
#include <limits>     // For std::numeric_limits
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 内省排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class IntroSort : public Sort<T> {
   private:
    /**
     * @brief 执行快速排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param depthLimit 最大递归深度
     */
    void quickSort(size_t low, size_t high, size_t depthLimit);

    /**
     * @brief 分区操作，快速排序的核心
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @return 新的分区位置
     */
    size_t partition(size_t low, size_t high);

    /**
     * @brief 执行堆排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void heapSort(size_t low, size_t high);

    /**
     * @brief 构建最大堆
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void buildMaxHeap(size_t low, size_t high);

    /**
     * @brief 堆化操作
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param i 当前节点的位置
     */
    void heapify(size_t low, size_t high, size_t i);

    /**
     * @brief 使用插入排序对小规模子数组进行排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void insertionSort(size_t low, size_t high);

   public:
    /**
     * @brief 执行内省排序
     */
    void sort() override;
};

#endif
