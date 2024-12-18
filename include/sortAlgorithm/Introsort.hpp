#ifndef INTROSORT_HPP
#define INTROSORT_HPP

#include <algorithm>  // For std::swap and std::partition
#include <cmath>      // For log2
#include <limits>     // For std::numeric_limits
#include "Sort.hpp"

/**
 * @brief 内省排序类，继承自 Sort 基类
 * @tparam T 数据类型
 * @tparam DisplayType 可视化类型
 */
template <typename T, typename DisplayType = DisplayPic<T>>
class IntroSort : public Sort<T, DisplayType> {
   private:
    /**
     * @brief 执行快速排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param depthLimit 最大递归深度
     */
    void quickSort(size_t low, size_t high, size_t depthLimit) {
        if (low < high) {
            if (depthLimit == 0) {
                heapSort(low, high);  // 如果递归深度超过阈值，使用堆排序
            } else {
                size_t pivotIndex = partition(low, high);
                // 排序后显示当前状态
                if (this->SPEED > 0 && this->GUI) {
                    this->display();
                    this->delay();
                }

                // 增加递归调用次数
                this->functionCalls++;
                this->recursionDepth++;
                this->maxRecursionDepth =
                    std::max(this->maxRecursionDepth, this->recursionDepth);

                quickSort(low, pivotIndex - 1, depthLimit - 1);   // 递归左边
                quickSort(pivotIndex + 1, high, depthLimit - 1);  // 递归右边

                // 完成当前层的递归后，递归深度回退
                this->recursionDepth--;
            }
        }
    }

    /**
     * @brief 分区操作，快速排序的核心
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @return 新的分区位置
     */
    size_t partition(size_t low, size_t high) {
        T pivot = this->arr[high];
        size_t i = low - 1;
        for (size_t j = low; j < high; ++j) {
            this->comparisons++;  // 增加比较计数
            if (this->arr[j] < pivot) {
                ++i;
                this->swap(this->arr[i], this->arr[j]);  // 交换
            }
            this->loopIterations++;  // 每次循环迭代时增加计数
        }
        this->swap(this->arr[i + 1], this->arr[high]);
        return i + 1;
    }

    /**
     * @brief 执行堆排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void heapSort(size_t low, size_t high) {
        buildMaxHeap(low, high);
        // 每次交换后显示
        if (this->SPEED > 0 && this->GUI) {
            this->display();
            this->delay();
        }
        for (size_t i = high; i > low; --i) {
            this->swap(this->arr[low], this->arr[i]);
            heapify(low, high, low);
            if (this->SPEED > 0 && this->GUI) {
                this->display();
                this->delay();
            }
        }
    }

    /**
     * @brief 构建最大堆
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void buildMaxHeap(size_t low, size_t high) {
        for (size_t i = (high - low) / 2; i >= low; --i) {
            heapify(low, high, i);
        }
    }

    /**
     * @brief 堆化操作
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param i 当前节点的位置
     */
    void heapify(size_t low, size_t high, size_t i) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t largest = i;
        if (left <= high && this->arr[left] > this->arr[largest]) {
            largest = left;
        }
        if (right <= high && this->arr[right] > this->arr[largest]) {
            largest = right;
        }
        if (largest != i) {
            this->swap(this->arr[i], this->arr[largest]);
            heapify(low, high, largest);
        }
    }

    /**
     * @brief 使用插入排序对小规模子数组进行排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void insertionSort(size_t low, size_t high) {
        for (size_t i = low + 1; i <= high; ++i) {
            T key = this->arr[i];
            size_t j = i;
            while (j > low && this->arr[j - 1] > key) {
                this->arr[j] = this->arr[j - 1];
                --j;
                this->comparisons++;  // 增加比较计数
            }
            this->arr[j] = key;
            // 每次插入后显示
            if (this->SPEED > 0 && this->GUI) {
                this->display();
                this->delay();
            }
            this->loopIterations++;  // 每次插入操作增加循环计数
        }
    }

   public:
    /**
     * @brief 执行内省排序
     */
    void sort() override {
        size_t n = this->arr.size();
        if (n <= 1)
            return;

        // 计算最大递归深度：log2(n) * 2
        size_t depthLimit = static_cast<size_t>(2 * std::log2(n));

        // 使用快速排序，并限制递归深度
        this->functionCalls++;  // 快速排序开始前，增加函数调用次数
        quickSort(0, n - 1, depthLimit);

        // 使用插入排序对小规模子数组进行排序
        insertionSort(0, n - 1);

        // 排序过程中的显示
        if (this->SPEED > 0 && this->GUI) {
            this->display();
            this->delay();
        }
    }
};

#endif
