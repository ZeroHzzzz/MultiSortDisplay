// BubbleSort.cpp
#include "sortAlgorithm/BubbleSort.hpp"
#include "headfile.hpp"

template <typename T>
void BubbleSort<T>::sort() {
    size_t n = this->arr.size();
    bool swapped;

    // 外循环控制排序轮数
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;

        // 内循环进行相邻元素比较和交换
        for (size_t j = 0; j < n - i - 1; ++j) {
            this->comparisons++;  // 比较次数增加

            // 根据排序方向进行判断
            bool condition = (this->sortOrder == SortOrder::ASCENDING)
                                 ? (this->arr[j] > this->arr[j + 1])
                                 : (this->arr[j] < this->arr[j + 1]);

            // 交换元素
            if (condition) {
                std::swap(this->arr[j],
                          this->arr[j + 1]);  // 使用std::swap进行交换
                swapped = true;
                this->swaps++;  // 交换次数增加
            }

            this->loopIterations++;  // 循环迭代次数增加

            // 显示当前状态
            if (this->SPEED > 0 && this->GUI && win.mode_selection) {
                win.update(this->arr);
                this->delay();
            }
        }

        // 如果一轮排序没有发生交换，则说明数组已经排序好了，提前结束
        if (!swapped) {
            break;
        }
    }
}
