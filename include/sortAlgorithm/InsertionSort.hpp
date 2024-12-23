#pragma once

#include <algorithm>  // For std::lower_bound (binary search)
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 插入排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class InsertionSort : public Sort<T> {
   private:
    /**
     * @brief 使用二分查找找到插入位置
     *
     * @param arr 待排序的数组
     * @param left 排序范围的起始位置
     * @param right 排序范围的结束位置
     * @param key 要插入的元素
     * @return 插入位置的索引
     */
    size_t binarySearch(const std::vector<T>& arr,
                        size_t left,
                        size_t right,
                        const T& key) const;

   public:
    /**
     * @brief 执行插入排序
     */
    void sort() override;
    InsertionSort(std::vector<T>& input,
                  ftxui::ScreenInteractive& screen,
                  size_t speed = 1000,
                  bool GUI = true)
        : Sort<T>(input, screen, speed, GUI) {
        this->stability = "Stable";
    };
};

template <typename T>
size_t InsertionSort<T>::binarySearch(const std::vector<T>& arr,
                                      size_t left,
                                      size_t right,
                                      const T& key) const {
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

template <typename T>
void InsertionSort<T>::sort() {
    size_t n = this->arr.size();
    if (n <= 1)
        return;

    // 提前扩展数组，确保不会越界
    this->arr.reserve(n + 1);

    // 插入排序，使用二分查找来优化
    for (size_t i = 1; i < n; ++i) {
        T key = this->arr[i];
        size_t j = i;

        // 使用二分查找找到插入位置
        size_t pos = binarySearch(this->arr, 0, j, key);

        // 移动元素：从当前位置向后移动
        while (j > pos) {
            this->arr[j] = this->arr[j - 1];
            --j;
            this->swaps++;           // 增加交换次数
            this->loopIterations++;  // 增加循环次数
        }

        // 将 key 插入到正确的位置
        this->arr[pos] = key;

        // 每一次插入后显示当前状态
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }
}