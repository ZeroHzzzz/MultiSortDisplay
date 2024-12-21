// InsertionSort.cpp
#include "sortAlgorithm/InsertionSort.hpp"
#include "headfile.hpp"

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
        if (win.mode_selection && win.graphics_selection) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }
}