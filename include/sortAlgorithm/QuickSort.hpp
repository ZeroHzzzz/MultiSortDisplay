#pragma once

#include <cstdlib>  // 用于随机数生成
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 快速排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class QuickSort : public Sort<T> {
   private:
    /**
     * @brief 插入排序，当子数组较小时调用
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     */
    void insertionSort(int low, int high);

    /**
     * @brief 比较函数，根据排序方向进行比较
     *
     * @param a 比较的第一个元素
     * @param b 比较的第二个元素
     * @return true 如果满足当前排序方向的条件
     * @return false 否则
     */
    bool compare(const T& a, const T& b) const;

    /**
     * @brief 分区函数，将数组划分为两部分
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @return int 返回枢轴的最终位置
     */
    int partition(int low, int high);

    /**
     * @brief 优化后的快速排序函数
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @param depth 当前递归深度
     */
    void optimizedQuickSort(int low, int high, int depth);

   public:
    /**
     * @brief 执行快速排序
     */
    void sort() override;
    QuickSort(std::vector<T>& input,
              ftxui::ScreenInteractive& screen,
              size_t speed = 1000,
              bool GUI = true)
        : Sort<T>(input, screen, speed, GUI) {
        this->stability = "Unstable";
    };
};

template <typename T>
void QuickSort<T>::insertionSort(int low, int high) {
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

        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }
}

template <typename T>
bool QuickSort<T>::compare(const T& a, const T& b) const {
    if (this->sortOrder == SortOrder::ASCENDING) {
        return a > b;
    } else {
        return a < b;
    }
}

template <typename T>
int QuickSort<T>::partition(int low, int high) {
    T pivot = this->arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        this->comparisons++;
        this->loopIterations++;

        if (!compare(this->arr[j], pivot)) {
            ++i;
            this->swap(this->arr[i], this->arr[j]);

            if (this->GUI) {
                this->screen.PostEvent(ftxui::Event::Custom);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(this->SPEED));
            }
        }
    }

    this->swap(this->arr[i + 1], this->arr[high]);

    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }

    return i + 1;
}

template <typename T>
void QuickSort<T>::optimizedQuickSort(int low, int high, int depth) {
    while (low < high) {
        this->functionCalls++;

        if (high - low + 1 <= 10) {
            insertionSort(low, high);
            break;
        }

        int pivotIndex = partition(low, high);

        if (depth > this->maxRecursionDepth) {
            this->maxRecursionDepth = depth;
        }

        if (pivotIndex - low < high - pivotIndex) {
            optimizedQuickSort(low, pivotIndex - 1, depth + 1);
            low = pivotIndex + 1;
        } else {
            optimizedQuickSort(pivotIndex + 1, high, depth + 1);
            high = pivotIndex - 1;
        }
    }
}

template <typename T>
void QuickSort<T>::sort() {
    this->functionCalls = 0;
    this->maxRecursionDepth = 0;

    optimizedQuickSort(0, this->arr.size() - 1, 1);
}