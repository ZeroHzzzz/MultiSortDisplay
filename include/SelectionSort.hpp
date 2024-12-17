#ifndef SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

#include "Sort.hpp"

/**
 * @brief 选择排序类，继承自 Sort 基类
 * @tparam T 数据类型
 * @tparam DisplayType 可视化类型
 */
template <typename T, typename DisplayType = DisplayPic<T>>
class SelectionSort : public Sort<T, DisplayType> {
   public:
    /**
     * @brief 执行选择排序
     *
     * @param speed 排序过程中的动画速度（延时）
     * @param gui 是否启用图形化输出
     */
    void sort(int speed = 0, bool gui = false) override {
        size_t n = this->arr.size();
        if (n <= 1)
            return;

        // 选择排序
        for (size_t i = 0; i < n - 1; ++i) {
            // 假设当前 i 位置的元素为最小
            size_t minIndex = i;

            // 在未排序部分找到最小元素
            for (size_t j = i + 1; j < n; ++j) {
                if (this->arr[j] < this->arr[minIndex]) {
                    minIndex = j;  // 更新最小元素的索引
                }
            }

            // 如果找到的最小元素不是当前元素，则交换
            if (minIndex != i) {
                this->swap(this->arr[i], this->arr[minIndex]);
            }

            // 每次完成一轮选择排序后显示当前状态
            if (speed > 0) {
                this->display();
                this->delay(speed);  // 使用传入的 speed 参数控制延时
            }
        }
    }
};

#endif
