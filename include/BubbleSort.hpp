#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "Sort.hpp"

/**
 * @brief 冒泡排序类，继承自 Sort 基类
 * @tparam T 数据类型
 * @tparam DisplayType 可视化类型
 */
template <typename T, typename DisplayType = DisplayPic<T>>
class BubbleSort : public Sort<T, DisplayType> {
   public:
    /**
     * @brief 实现冒泡排序的排序算法
     *
     * @param speed 排序过程中的动画速度（延时）
     * @param gui 是否启用图形化输出
     */
    void sort(int speed = 0, bool gui = false) override {
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
                if (gui) {
                    this->display();
                    this->delay(speed);
                }
            }

            // 如果一轮排序没有发生交换，则说明数组已经排序好了，提前结束
            if (!swapped) {
                break;
            }
        }
    }
};

#endif
