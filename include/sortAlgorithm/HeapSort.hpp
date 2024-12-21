// HeapSort.hpp
#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <vector>
#include "headfile.hpp"
#include "sortAlgorithm/Sort.hpp"
/**
 * @brief 堆排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class HeapSort : public Sort<T> {
   public:
    /**
     * @brief 调整堆的大小
     *
     * @param arr 待排序的数组
     * @param n 数组大小
     * @param i 当前节点的索引
     */
    void heapify(std::vector<T>& arr, size_t n, size_t i);

    /**
     * @brief 执行堆排序
     */
    void sort() override;
    HeapSort(std::vector<T>& input,
             ftxui::ScreenInteractive& screen,
             size_t speed = 1000,
             bool GUI = true)
        : Sort<T>(input, screen, speed, GUI) {};
};

template <typename T>
void HeapSort<T>::heapify(std::vector<T>& arr, size_t n, size_t i) {
    size_t largest = i;        // 当前节点
    size_t left = 2 * i + 1;   // 左子节点
    size_t right = 2 * i + 2;  // 右子节点

    // 如果左子节点大于当前节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点大于当前最大值
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果当前节点不是最大值，交换并递归调整堆
    if (largest != i) {
        this->swap(arr[i], arr[largest]);  // 交换节点
        this->swaps++;                     // 增加交换次数
        this->loopIterations++;            // 增加循环次数

        // 每次堆调整后，显示当前状态
        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }

        // 递归调整被交换的子堆
        heapify(arr, n, largest);
    }
}

template <typename T>
void HeapSort<T>::sort() {
    size_t n = this->arr.size();
    if (n <= 1)
        return;

    // 构建最大堆
    for (size_t i = n / 2; i-- > 0;) {  // 从最后一个非叶子节点开始
        heapify(this->arr, n, i);
    }

    // 从堆顶取出最大元素，交换到数组末尾，并调整堆
    for (size_t i = n - 1; i > 0; --i) {
        // 交换堆顶元素和当前堆的最后一个元素
        this->swap(this->arr[0], this->arr[i]);
        this->swaps++;  // 增加交换次数

        // 调整堆，恢复堆性质
        heapify(this->arr, i, 0);  // i 是堆的大小
    }
}

#endif
