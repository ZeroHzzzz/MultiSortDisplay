// MergeSort.cpp
#include "sortAlgorithm/MergeSort.hpp"
#include "headfile.hpp"

template <typename T>
void MergeSort<T>::merge(std::vector<T>& arr,
                         size_t left,
                         size_t mid,
                         size_t right) {
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

        if (this->SPEED > 0 && this->GUI && win.mode_selection) {
            win.update(this->arr);
            this->delay();
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    this->swaps++;  // 合并过程中的交换

    if (this->SPEED > 0 && this->GUI && win.mode_selection) {
        win.update(this->arr);
        this->delay();
    }
}

template <typename T>
void MergeSort<T>::mergeSort(std::vector<T>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

template <typename T>
void MergeSort<T>::sort() {
    this->comparisons = 0;
    this->swaps = 0;
    this->loopIterations = 0;

    size_t n = this->arr.size();
    if (n <= 1)
        return;

    mergeSort(this->arr, 0, n - 1);
}
