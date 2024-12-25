#pragma once

#include <vector>
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 归并排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class MergeSort : public Sort<T> {
   private:
    /**
     * @brief 自定义的合并函数，用来合并两个已排序的子数组
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param mid 中间位置（左子数组的末尾）
     * @param right 右子数组的末尾位置
     */
    void merge(std::vector<T>& arr, size_t left, size_t mid, size_t right);

    /**
     * @brief 递归拆分数组并执行合并操作
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param right 右子数组的末尾位置
     */
    void mergeSort(std::vector<T>& arr, size_t left, size_t right);

   public:
    /**
     * @brief 实现归并排序的排序算法
     */
    void sort() override;
    MergeSort(std::vector<T>& input,
              ftxui::ScreenInteractive& screen,
              size_t speed = 1000,
              bool GUI = true,
              int order = 0)
        : Sort<T>(input, screen, speed, GUI, order) {};
    std::string getStability() const override { return this->stability; }
};

template <typename T>
void MergeSort<T>::merge(std::vector<T>& arr,
                         size_t left,
                         size_t mid,
                         size_t right) {
    this->functionCalls++;
    size_t n1 = mid - left + 1;  // 左子数组的长度
    size_t n2 = right - mid;     // 右子数组的长度

    // 创建临时数组来存储左右子数组
    std::vector<T> leftArr(n1), rightArr(n2);

    // 拷贝数据到临时数组
    std::copy(arr.begin() + left, arr.begin() + mid + 1, leftArr.begin());
    std::copy(arr.begin() + mid + 1, arr.begin() + right + 1, rightArr.begin());

    size_t i = 0, j = 0, k = left;

    // 合并左右子数组
    while (i < n1 && j < n2) {
        this->comparisons++;  // 增加比较次数

        bool condition = (this->sortOrder == SortOrder::ASCENDING)
                             ? (leftArr[i] <= rightArr[j])
                             : (leftArr[i] >= rightArr[j]);

        if (condition) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
        this->loopIterations++;  // 增加循环次数

        if (this->GUI) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
    }

    while (i < n1) {
        this->comparisons++;
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        this->comparisons++;
        arr[k++] = rightArr[j++];
    }

    this->swaps++;  // 合并过程中的交换

    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}

template <typename T>
void MergeSort<T>::mergeSort(std::vector<T>& arr, size_t left, size_t right) {
    this->functionCalls++;
    this->recursionDepth++;
    this->maxRecursionDepth =
        std::max(this->maxRecursionDepth, this->recursionDepth);
    if (left < right) {
        this->comparisons++;
        size_t mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
    this->recursionDepth--;
}

template <typename T>
void MergeSort<T>::sort() {
    this->stability = "Stable";
    this->functionCalls++;

    size_t n = this->arr.size();
    if (n <= 1)
        return;

    mergeSort(this->arr, 0, n - 1);
}
