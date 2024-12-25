#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief TimSort 类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class TimSort : public Sort<T> {
   private:
    const static size_t MIN_RUN = 32;  // 最小块大小，通常选择32

    // 插入排序：对小块进行插入排序
    void insertionSort(size_t left, size_t right);

    // 合并两个已排序的区间
    void merge(size_t left, size_t mid, size_t right);

    // 合并多个块
    void timSortMerge();

    // 创建 runs 并进行插入排序
    void createRuns();

    // TimSort 主排序函数
    void timSort();

   public:
    // 执行 TimSort 排序
    void sort() override;

    TimSort(std::vector<T>& input,
            ftxui::ScreenInteractive& screen,
            size_t speed = 1000,
            bool GUI = true,
            int order = 0)
        : Sort<T>(input, screen, speed, GUI, order) {};
    std::string getStability() const override { return this->stability; }
};

template <typename T>
void TimSort<T>::insertionSort(size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
        T key = this->arr[i];
        size_t j = i;
        while (j > left && this->arr[j - 1] > key) {
            this->arr[j] = this->arr[j - 1];
            --j;
            this->comparisons++;     // 增加比较次数
            this->swaps++;           // 增加交换次数
            this->loopIterations++;  // 增加循环次数
        }
        this->arr[j] = key;
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
        this->loopIterations++;  // 增加插入排序的循环次数
    }
}

template <typename T>
void TimSort<T>::merge(size_t left, size_t mid, size_t right) {
    size_t len1 = mid - left + 1;
    size_t len2 = right - mid;

    std::vector<T> leftArr(len1);
    std::vector<T> rightArr(len2);

    for (size_t i = 0; i < len1; ++i) {
        leftArr[i] = this->arr[left + i];
    }
    for (size_t i = 0; i < len2; ++i) {
        rightArr[i] = this->arr[mid + 1 + i];
    }

    size_t i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        this->comparisons++;  // 比较次数
        if (leftArr[i] <= rightArr[j]) {
            this->arr[k++] = leftArr[i++];
        } else {
            this->arr[k++] = rightArr[j++];
        }
        this->loopIterations++;  // 增加循环次数
        this->swaps++;           // 交换次数
    }

    // 复制剩余元素
    while (i < len1) {
        this->arr[k++] = leftArr[i++];
        this->loopIterations++;  // 增加循环次数
        this->swaps++;           // 交换次数
    }

    while (j < len2) {
        this->arr[k++] = rightArr[j++];
        this->loopIterations++;  // 增加循环次数
        this->swaps++;           // 交换次数
    }

    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}

template <typename T>
void TimSort<T>::timSortMerge() {
    for (size_t size = MIN_RUN; size < this->arr.size(); size = size * 2) {
        for (size_t left = 0; left < this->arr.size(); left += 2 * size) {
            size_t mid = std::min(left + size - 1, this->arr.size() - 1);
            size_t right =
                std::min((left + 2 * size - 1), (this->arr.size() - 1));
            if (mid < right) {
                merge(left, mid, right);
            }
        }
    }
}

template <typename T>
void TimSort<T>::createRuns() {
    size_t n = this->arr.size();
    for (size_t start = 0; start < n; start += MIN_RUN) {
        size_t end = std::min(start + MIN_RUN - 1, n - 1);
        insertionSort(start, end);  // 对每个块使用插入排序
    }
}

template <typename T>
void TimSort<T>::timSort() {
    this->functionCalls++;  // 增加函数调用次数
    createRuns();           // 创建并排序 runs
    timSortMerge();         // 合并所有 runs
}

template <typename T>
void TimSort<T>::sort() {
    this->stability = "Stable";
    if (this->arr.size() <= 1)
        return;

    this->functionCalls++;  // 增加函数调用次数
    timSort();              // 执行 TimSort 排序

    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}
