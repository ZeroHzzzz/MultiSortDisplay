#pragma once

#include <algorithm>  // For std::swap and std::partition
#include <cmath>      // For log2
#include <limits>     // For std::numeric_limits
#include "sortAlgorithm/Sort.hpp"

// TODO:Segmentation fault Bug
/**
 * @brief 内省排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class IntroSort : public Sort<T> {
   private:
    /**
     * @brief 执行快速排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param depthLimit 最大递归深度
     */
    void quickSort(size_t low, size_t high, size_t depthLimit);

    /**
     * @brief 分区操作，快速排序的核心
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @return 新的分区位置
     */
    size_t partition(size_t low, size_t high);

    /**
     * @brief 执行堆排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void heapSort(size_t low, size_t high);

    /**
     * @brief 构建最大堆
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void buildMaxHeap(size_t low, size_t high);

    /**
     * @brief 堆化操作
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     * @param i 当前节点的位置
     */
    void heapify(size_t low, size_t high, size_t i);

    /**
     * @brief 使用插入排序对小规模子数组进行排序
     *
     * @param low 排序的起始位置
     * @param high 排序的结束位置
     */
    void insertionSort(size_t low, size_t high);

   public:
    /**
     * @brief 执行内省排序
     */
    void sort() override;
    IntroSort(std::vector<T>& input,
              ftxui::ScreenInteractive& screen,
              size_t speed = 1000,
              bool GUI = true,
              int order = 0)
        : Sort<T>(input, screen, speed, GUI, order) {
        this->stability = "Unstable";
    };
};

template <typename T>
void IntroSort<T>::quickSort(size_t low, size_t high, size_t depthLimit) {
    if (low < high) {
        if (depthLimit == 0) {
            heapSort(low, high);  // 如果递归深度超过阈值，使用堆排序
        } else {
            size_t pivotIndex = partition(low, high);
            if (this->GUI) {
                this->screen.PostEvent(ftxui::Event::Custom);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(this->SPEED));
            }

            this->functionCalls++;
            this->recursionDepth++;
            this->maxRecursionDepth =
                std::max(this->maxRecursionDepth, this->recursionDepth);

            quickSort(low, pivotIndex - 1, depthLimit - 1);
            quickSort(pivotIndex + 1, high, depthLimit - 1);

            this->recursionDepth--;
        }
    }
}

template <typename T>
size_t IntroSort<T>::partition(size_t low, size_t high) {
    T pivot = this->arr[high];
    size_t i = low - 1;
    for (size_t j = low; j < high; ++j) {
        this->comparisons++;
        if (this->arr[j] < pivot) {
            ++i;
            this->swap(this->arr[i], this->arr[j]);
        }
        this->loopIterations++;
    }
    this->swap(this->arr[i + 1], this->arr[high]);
    return i + 1;
}

template <typename T>
void IntroSort<T>::heapSort(size_t low, size_t high) {
    buildMaxHeap(low, high);
    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
    for (size_t i = high; i > low; --i) {
        this->swap(this->arr[low], this->arr[i]);
        heapify(low, i - 1, low);
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }
}

template <typename T>
void IntroSort<T>::buildMaxHeap(size_t low, size_t high) {
    for (size_t i = (high - low) / 2 + low; i >= low; --i) {
        heapify(low, high, i);
    }
}

template <typename T>
void IntroSort<T>::heapify(size_t low, size_t high, size_t i) {
    size_t left = 2 * (i - low) + 1 + low;
    size_t right = 2 * (i - low) + 2 + low;
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

template <typename T>
void IntroSort<T>::insertionSort(size_t low, size_t high) {
    for (size_t i = low + 1; i <= high; ++i) {
        T key = this->arr[i];
        size_t j = i;
        while (j > low && this->arr[j - 1] > key) {
            this->arr[j] = this->arr[j - 1];
            --j;
            this->comparisons++;
        }
        this->arr[j] = key;
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
        this->loopIterations++;
    }
}

template <typename T>
void IntroSort<T>::sort() {
    size_t n = this->arr.size();
    if (n <= 1)
        return;

    size_t depthLimit = static_cast<size_t>(2 * std::log2(n));

    this->functionCalls++;
    quickSort(0, n - 1, depthLimit);

    insertionSort(0, n - 1);

    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}
