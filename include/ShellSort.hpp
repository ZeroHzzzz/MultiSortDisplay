#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "Sort.hpp"

/**
 * @brief 希尔排序类，继承自 Sort 基类
 * @tparam T 数据类型
 * @tparam DisplayType 可视化类型
 */
template <typename T, typename DisplayType = DisplayPic<T>>
class ShellSort : public Sort<T, DisplayType> {
   public:
    /**
     * @brief 执行希尔排序
     *
     * @param speed 排序过程中的动画速度（延时）
     * @param gui 是否启用图形化输出
     */
    void sort(int speed = 0, bool gui = false) override {
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
            if (speed > 0) {
                this->display();
                this->delay(speed);  // 使用传入的 speed 参数控制延时
            }

            gap /= 2;  // 减小增量
        }
    }
};

#endif
