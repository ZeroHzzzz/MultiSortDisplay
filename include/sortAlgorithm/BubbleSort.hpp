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
               size_t speed = 1000,
               bool GUI = true)
        : Sort<T>(input, screen, speed, GUI) {};
    void sort() override;
};

template <typename T>
void BubbleSort<T>::sort() {
    size_t n = this->arr.size();
    bool swapped;

    // 外循环控制排序轮数
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;

        // 内循环进行相邻元素比较和交换
        for (size_t j = 0; j < n - i - 1; ++j) {
            this->comparisons++;  // 比较次数增加

            // 根据排序方向进行判断
            bool condition = (this->sortOrder == SortOrder::ASCENDING)
                                 ? (this->arr[j] > this->arr[j + 1])
                                 : (this->arr[j] < this->arr[j + 1]);

            // 交换元素
            if (condition) {
                std::swap(this->arr[j],
                          this->arr[j + 1]);  // 使用std::swap进行交换
                swapped = true;
                this->swaps++;  // 交换次数增加
            }

            this->loopIterations++;  // 循环迭代次数增加

            // 显示当前状态
            if (this->GUI) {
                this->screen.PostEvent(ftxui::Event::Custom);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(this->SPEED));
            }
        }

        // 如果一轮排序没有发生交换，则说明数组已经排序好了，提前结束
        if (!swapped) {
            break;
        }
    }
    // this->screen.PostEvent(ftxui::Event::Custom);
}
#endif
