// IntroSort.cpp
#include "sortAlgorithm/IntroSort.hpp"
#include "headfile.hpp"

template <typename T>
void IntroSort<T>::quickSort(size_t low, size_t high, size_t depthLimit) {
    if (low < high) {
        if (depthLimit == 0) {
            heapSort(low, high);  // 如果递归深度超过阈值，使用堆排序
        } else {
            size_t pivotIndex = partition(low, high);
            if (this->SPEED > 0 && this->GUI && win.mode_selection) {
                win.update(this->arr);
                this->delay();
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
    if (this->SPEED > 0 && this->GUI && win.mode_selection) {
        win.update(this->arr);
        this->delay();
    }
    for (size_t i = high; i > low; --i) {
        this->swap(this->arr[low], this->arr[i]);
        heapify(low, i - 1, low);
        if (this->SPEED > 0 && this->GUI && win.mode_selection) {
            win.update(this->arr);
            this->delay();
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
        if (this->SPEED > 0 && this->GUI && win.mode_selection) {
            win.update(this->arr);
            this->delay();
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

    if (this->SPEED > 0 && this->GUI && win.mode_selection) {
        win.update(this->arr);
        this->delay();
    }
}