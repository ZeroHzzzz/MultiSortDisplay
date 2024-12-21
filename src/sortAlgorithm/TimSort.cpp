// TimSort.cpp
#include "sortAlgorithm/TimSort.hpp"
#include "headfile.hpp"

template <typename T>
void TimSort<T>::insertionSort(size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
        T key = this->arr[i];
        size_t j = i;
        while (j > left && this->arr[j - 1] > key) {
            this->arr[j] = this->arr[j - 1];
            --j;
            this->comparisons++;
            this->swaps++;
        }
        this->arr[j] = key;
        if (win.mode_selection && win.graphics_selection) {
            this->screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
        }
        this->loopIterations++;
    }
}

template <typename T>
void TimSort<T>::merge(size_t left, size_t mid, size_t right) {
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
        this->comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            this->arr[k] = leftArr[i++];
        } else {
            this->arr[k] = rightArr[j++];
        }
        ++k;
        this->loopIterations++;
        this->swaps++;
    }

    while (i < len1) {
        this->arr[k++] = leftArr[i++];
        this->loopIterations++;
        this->swaps++;
    }

    while (j < len2) {
        this->arr[k++] = rightArr[j++];
        this->loopIterations++;
        this->swaps++;
    }

    if (win.mode_selection && win.graphics_selection) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}

template <typename T>
void TimSort<T>::timSortMerge() {
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

template <typename T>
void TimSort<T>::createRuns() {
    size_t n = this->arr.size();
    for (size_t start = 0; start < n; start += MIN_RUN) {
        size_t end = std::min(start + MIN_RUN - 1, n - 1);
        insertionSort(start, end);
    }
}

template <typename T>
void TimSort<T>::timSort() {
    this->functionCalls++;
    createRuns();
    timSortMerge();
}

template <typename T>
void TimSort<T>::sort() {
    if (this->arr.size() <= 1)
        return;

    this->functionCalls++;
    timSort();

    if (win.mode_selection && win.graphics_selection) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }
}
