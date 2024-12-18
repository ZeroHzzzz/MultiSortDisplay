#ifndef TIMSORT_HPP
#define TIMSORT_HPP

#include <algorithm>
#include <cmath>
#include <vector>
#include "Sort.hpp"

template <typename T, typename DisplayType = DisplayPic<T>>
class TimSort : public Sort<T, DisplayType> {
   private:
    const static size_t MIN_RUN = 32;  // 最小块大小，通常选择32

    // 插入排序：对小块进行插入排序
    void insertionSort(size_t left, size_t right) {
        for (size_t i = left + 1; i <= right; ++i) {
            T key = this->arr[i];
            size_t j = i;
            while (j > left && this->arr[j - 1] > key) {
                this->arr[j] = this->arr[j - 1];
                --j;
                this->comparisons++;  // 增加比较计数
                this->swaps++;        // 每次移动一个元素，模拟交换
            }
            this->arr[j] = key;
            // 显示当前状态
            if (this->SPEED > 0 && this->GUI) {
                this->display();
                this->delay();
            }
            this->loopIterations++;  // 每次插入操作增加循环计数
        }
    }

    // 合并两个已排序的区间
    void merge(size_t left, size_t mid, size_t right) {
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
            this->comparisons++;  // 增加比较计数
            if (leftArr[i] <= rightArr[j]) {
                this->arr[k] = leftArr[i++];
            } else {
                this->arr[k] = rightArr[j++];
            }
            ++k;
            this->loopIterations++;  // 每次循环增加计数
            this->swaps++;           // 每次赋值操作视作交换
        }

        while (i < len1) {
            this->arr[k++] = leftArr[i++];
            this->loopIterations++;  // 每次循环增加计数
            this->swaps++;           // 每次赋值操作视作交换
        }

        while (j < len2) {
            this->arr[k++] = rightArr[j++];
            this->loopIterations++;  // 每次循环增加计数
            this->swaps++;           // 每次赋值操作视作交换
        }

        // 合并后显示当前状态
        if (this->SPEED > 0 && this->GUI) {
            this->display();
            this->delay();
        }
    }

    // 合并多个块
    void timSortMerge() {
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

    // 创建 runs 并进行插入排序
    void createRuns() {
        size_t n = this->arr.size();
        for (size_t start = 0; start < n; start += MIN_RUN) {
            size_t end = std::min(start + MIN_RUN - 1, n - 1);
            insertionSort(start, end);
        }
    }

    // TimSort 主排序函数
    void timSort() {
        this->functionCalls++;  // 统计 TimSort 调用次数
        createRuns();           // Step 1: 创建 runs 并插入排序
        timSortMerge();         // Step 2: 合并 runs
    }

   public:
    // 执行 TimSort 排序
    void sort() override {
        if (this->arr.size() <= 1)
            return;

        this->functionCalls++;  // 统计外层排序调用次数
        timSort();              // 执行 TimSort

        // 最终显示
        if (this->SPEED > 0 && this->GUI) {
            this->display();
            this->delay();
        }
    }
};

#endif
