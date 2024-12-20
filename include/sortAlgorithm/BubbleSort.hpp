// BubbleSort.hpp
#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 冒泡排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class BubbleSort : public Sort<T> {
   public:
    /**
     * @brief 实现冒泡排序的排序算法
     */
    void sort() override;
};

#endif
