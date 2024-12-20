// QuickSort.hpp
#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <cstdlib>  // 用于随机数生成
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 快速排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class QuickSort : public Sort<T> {
   private:
    /**
     * @brief 插入排序，当子数组较小时调用
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     */
    void insertionSort(int low, int high);

    /**
     * @brief 比较函数，根据排序方向进行比较
     *
     * @param a 比较的第一个元素
     * @param b 比较的第二个元素
     * @return true 如果满足当前排序方向的条件
     * @return false 否则
     */
    bool compare(const T& a, const T& b) const;

    /**
     * @brief 分区函数，将数组划分为两部分
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @return int 返回枢轴的最终位置
     */
    int partition(int low, int high);

    /**
     * @brief 优化后的快速排序函数
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @param depth 当前递归深度
     */
    void optimizedQuickSort(int low, int high, int depth);

   public:
    /**
     * @brief 执行快速排序
     */
    void sort() override;
};

#endif
