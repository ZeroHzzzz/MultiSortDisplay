// SelectionSort.hpp
#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 选择排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class SelectionSort : public Sort<T> {
   public:
        /**
     * @brief 执行选择排序
     */
    void sort() override;
    SelectionSort(std::vector<T>& input,
                  ftxui::ScreenInteractive& screen,
                  size_t speed = 1000);
};

#endif
