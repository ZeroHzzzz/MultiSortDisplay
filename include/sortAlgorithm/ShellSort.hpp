#pragma once

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
              size_t speed = 1000,
              bool GUI = true,
              int order = 0)
        : Sort<T>(input, screen, speed, GUI, order) {};
    std::string getStability() const override { return this->stability; }
};

template <typename T>
void ShellSort<T>::sort() {
    this->stability = "Unstable";
    this->functionCalls++;
    size_t n = this->arr.size();
    if (n <= 1)
        return;

    // 经典的希尔排序增量序列（n / 2, n / 4, ..., 1）
    size_t gap = n / 2;

    // 从较大的增量开始，逐步减小增量，直到 1
    while (gap > 0) {
        this->loopIterations++;
        // 对每个增量执行插入排序
        for (size_t i = gap; i < n; ++i) {
            this->loopIterations++;
            T key = this->arr[i];
            size_t j = i;

            // 按增量间隔进行插入排序
            while (j >= gap && this->arr[j - gap] > key) {
                this->arr[j] = this->arr[j - gap];
                j -= gap;
                this->swaps++;           // 交换次数
                this->loopIterations++;  // 循环次数
                this->comparisons++;
            }
            this->arr[j] = key;
        }

        // 每次完成一轮增量排序后显示当前状态
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }

        gap /= 2;  // 减小增量
    }
}
