// ShellSort.hpp
#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 希尔排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class ShellSort : public Sort<T> {
   public:
    /**
     * @brief 执行希尔排序
     */
    void sort() override;
    ShellSort(std::vector<T>& input,
              ftxui::ScreenInteractive& screen,
              size_t speed = 1000);
};

#endif
