// QuickSort.cpp
#include "sortAlgorithm/QuickSort.hpp"
#include "headfile.hpp"

template <typename T>
void QuickSort<T>::insertionSort(int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        T key = this->arr[i];
        int j = i - 1;

        while (j >= low && compare(this->arr[j], key)) {
            this->arr[j + 1] = this->arr[j];
            j--;
            this->comparisons++;
            this->swaps++;
        }
        this->arr[j + 1] = key;

        if (this->SPEED > 0 && this->GUI && win.mode_selection) {
            win.update(this->arr);
            this->delay();
        }
    }
}

template <typename T>
bool QuickSort<T>::compare(const T& a, const T& b) const {
    if (this->sortOrder == SortOrder::ASCENDING) {
        return a > b;
    } else {
        return a < b;
    }
}

template <typename T>
int QuickSort<T>::partition(int low, int high) {
    T pivot = this->arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        this->comparisons++;
        this->loopIterations++;

        if (!compare(this->arr[j], pivot)) {
            ++i;
            this->swap(this->arr[i], this->arr[j]);

            if (this->SPEED > 0 && this->GUI && win.mode_selection) {
                win.update(this->arr);
                this->delay();
            }
        }
    }

    this->swap(this->arr[i + 1], this->arr[high]);

    if (this->SPEED > 0 && this->GUI && win.mode_selection) {
        win.update(this->arr);
        this->delay();
    }

    return i + 1;
}

template <typename T>
void QuickSort<T>::optimizedQuickSort(int low, int high, int depth) {
    while (low < high) {
        this->functionCalls++;

        if (high - low + 1 <= 10) {
            insertionSort(low, high);
            break;
        }

        int pivotIndex = partition(low, high);

        if (depth > this->maxRecursionDepth) {
            this->maxRecursionDepth = depth;
        }

        if (pivotIndex - low < high - pivotIndex) {
            optimizedQuickSort(low, pivotIndex - 1, depth + 1);
            low = pivotIndex + 1;
        } else {
            optimizedQuickSort(pivotIndex + 1, high, depth + 1);
            high = pivotIndex - 1;
        }
    }
}

template <typename T>
void QuickSort<T>::sort() {
    this->functionCalls = 0;
    this->maxRecursionDepth = 0;

    optimizedQuickSort(0, this->arr.size() - 1, 1);
}