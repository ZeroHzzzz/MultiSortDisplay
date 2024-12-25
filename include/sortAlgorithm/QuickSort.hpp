#pragma once

#include <cstdlib>  // 用于随机数生成
#include "sortAlgorithm/Sort.hpp"

/**
 * @brief 快速排序类，继承自 Sort 基类
 * @tparam T 数据类型
 */
template <typename T>
class QuickSort : public Sort<T> {
   private:
    /**
     * @brief 比较函数，根据排序方向进行比较
     *
     * @param a 比较的第一个元素
     * @param b 比较的第二个元素
     * @return true 如果满足当前排序方向的条件
     * @return false 否则
     */
    bool compare(const T& a, const T& b);

    /**
     * @brief 分区函数，将数组划分为两部分
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     * @return int 返回枢轴的最终位置
     */
    int partition(int low, int high);

    /**
     * @brief 快速排序递归函数
     *
     * @param low 子数组的起始索引
     * @param high 子数组的结束索引
     */
    void quickSort(int low, int high);

   public:
    /**
     * @brief 执行快速排序
     */
    void sort() override;

    QuickSort(std::vector<T>& input,
              ftxui::ScreenInteractive& screen,
              size_t speed = 1000,
              bool GUI = true,
              int order = 0)
        : Sort<T>(input, screen, speed, GUI, order) {};
    std::string getStability() const override { return this->stability; }
};

template <typename T>
bool QuickSort<T>::compare(const T& a, const T& b) {
    this->functionCalls++;
    if (this->sortOrder == SortOrder::ASCENDING) {
        return a > b;
    } else {
        return a < b;
    }
}

template <typename T>
int QuickSort<T>::partition(int low, int high) {
    this->functionCalls++;

    // 随机选择枢轴，避免最坏情况
    int pivotIndex = low + rand() % (high - low + 1);
    T pivot = this->arr[pivotIndex];
    this->swap(this->arr[pivotIndex],
               this->arr[high]);  // 将枢轴移动到数组的最后

    int i = low - 1;
    for (int j = low; j < high; ++j) {
        this->comparisons++;
        this->loopIterations++;
        if (!compare(this->arr[j], pivot)) {
            ++i;
            this->swap(this->arr[i], this->arr[j]);

            if (this->GUI) {
                this->screen.PostEvent(ftxui::Event::Custom);
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(this->SPEED));
            }
        }
    }

    this->swap(this->arr[i + 1], this->arr[high]);  // 将枢轴元素放到正确位置
    if (this->GUI) {
        this->screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->SPEED));
    }

    return i + 1;
}

template <typename T>
void QuickSort<T>::quickSort(int low, int high) {
    this->functionCalls++;

    if (low < high) {
        this->comparisons++;
        this->loopIterations++;

        // 获取分区后枢轴的正确位置
        int pivotIndex = partition(low, high);

        // 对左右子数组递归排序
        quickSort(low, pivotIndex - 1);
        quickSort(pivotIndex + 1, high);
    }
}

template <typename T>
void QuickSort<T>::sort() {
    this->stability = "Unstable";
    this->functionCalls++;

    quickSort(0, this->arr.size() - 1);
}
