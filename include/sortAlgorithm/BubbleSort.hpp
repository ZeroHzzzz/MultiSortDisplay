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
    BubbleSort(std::vector<T>& input,
               ftxui::ScreenInteractive& screen,
               size_t speed = 1000)
        : Sort<T>(input, screen, speed) {};
    void sort() override;
};

#endif
