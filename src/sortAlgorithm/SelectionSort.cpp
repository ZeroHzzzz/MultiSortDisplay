// SelectionSort.cpp
#include "sortAlgorithm/SelectionSort.hpp"
#include "headfile.hpp"

template <typename T>
void SelectionSort<T>::sort() {
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
        if (win.mode_selection && win.graphics_selection) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }
}