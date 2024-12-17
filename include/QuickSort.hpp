#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <cstdlib>  // 用于随机数生成
#include "Sort.hpp"

template <typename T>
class QuickSort : public Sort<T> {
   private:
    /**
     * @brief 插入排序，当子数组较小时调用
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @param speed 延时速度
     * @param gui 是否启用图形化
     */
    void insertionSort(int low, int high, int speed, bool gui) {
        for (int i = low + 1; i <= high; ++i) {
            T key = this->arr[i];
            int j = i - 1;

            while (j >= low && compare(this->arr[j], key)) {
                this->arr[j + 1] = this->arr[j];
                j--;
                this->comparisons++;
                this->swaps++;
            }
            this->arr[j + 1] = key;

            if (gui) {
                this->delay(speed);
                this->display();
            }
        }
    }

    /**
     * @brief 比较函数，根据排序方向进行比较
     *
     * @param a 比较的第一个元素
     * @param b 比较的第二个元素
     * @return true 如果满足当前排序方向的条件
     * @return false 否则
     */
    bool compare(const T& a, const T& b) const {
        if (this->sortOrder == SortOrder::ASCENDING) {
            return a > b;
        } else {
            return a < b;
        }
    }

    /**
     * @brief 分区函数，将数组划分为两部分
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @param speed 延时速度
     * @param gui 是否启用图形化
     * @return int 返回枢轴的最终位置
     */
    int partition(int low, int high, int speed, bool gui) {
        T pivot = this->arr[high];  // 选择最后一个元素作为枢轴
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            this->comparisons++;
            this->loopIterations++;

            if (!compare(this->arr[j], pivot)) {  // 根据排序方向进行比较
                ++i;
                this->swap(this->arr[i], this->arr[j]);

                if (gui) {
                    this->delay(speed);
                    this->display();
                }
            }
        }

        this->swap(this->arr[i + 1], this->arr[high]);

        if (gui) {
            this->delay(speed);
            this->display();
        }

        return i + 1;
    }

    /**
     * @brief 优化后的快速排序函数
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @param depth 当前递归深度
     * @param speed 延时速度
     * @param gui 是否启用图形化
     */
    void optimizedQuickSort(int low, int high, int depth, int speed, bool gui) {
        while (low < high) {
            this->functionCalls++;

            // 小数组切换为插入排序
            if (high - low + 1 <= 10) {
                insertionSort(low, high, speed, gui);
                break;
            }

            // 分区操作
            int pivotIndex = partition(low, high, speed, gui);

            // 更新最大递归深度
            if (depth > this->maxRecursionDepth) {
                this->maxRecursionDepth = depth;
            }

            // 尾递归优化
            if (pivotIndex - low < high - pivotIndex) {
                optimizedQuickSort(low, pivotIndex - 1, depth + 1, speed, gui);
                low = pivotIndex + 1;
            } else {
                optimizedQuickSort(pivotIndex + 1, high, depth + 1, speed, gui);
                high = pivotIndex - 1;
            }
        }
    }

   public:
    /**
     * @brief 执行快速排序
     *
     * @param speed 延时速度（用于可视化）
     * @param gui 是否启用图形化
     */
    void sort(int speed = 0, bool gui = false) override {
        this->functionCalls = 0;
        this->maxRecursionDepth = 0;

        optimizedQuickSort(0, this->arr.size() - 1, 1, speed, gui);
    }
};

#endif
