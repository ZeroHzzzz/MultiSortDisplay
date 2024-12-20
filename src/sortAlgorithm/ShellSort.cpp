// ShellSort.cpp
#include "sortAlgorithm/ShellSort.hpp"
#include "headfile.hpp"

template <typename T>
void ShellSort<T>::sort() {
    size_t n = this->arr.size();
    if (n <= 1)
        return;

    // 经典的希尔排序增量序列（n / 2, n / 4, ..., 1）
    size_t gap = n / 2;

    // 从较大的增量开始，逐步减小增量，直到 1
    while (gap > 0) {
        // 对每个增量执行插入排序
        for (size_t i = gap; i < n; ++i) {
            T key = this->arr[i];
            size_t j = i;

            // 按增量间隔进行插入排序
            while (j >= gap && this->arr[j - gap] > key) {
                this->arr[j] = this->arr[j - gap];
                j -= gap;
                this->swaps++;           // 交换次数
                this->loopIterations++;  // 循环次数
            }
            this->arr[j] = key;
        }

        // 每次完成一轮增量排序后显示当前状态
        if (this->SPEED > 0 && this->GUI && win.mode_selection) {
            win.update(this->arr);
            this->delay();
        }

        gap /= 2;  // 减小增量
    }
}
