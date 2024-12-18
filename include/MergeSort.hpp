#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "Sort.hpp"

/**
 * @brief 归并排序类，继承自 Sort 基类
 * @tparam T 数据类型
 * @tparam DisplayType 可视化类型
 */
template <typename T, typename DisplayType = DisplayPic<T>>
class MergeSort : public Sort<T, DisplayType> {
   private:
    /**
     * @brief 自定义的合并函数，用来合并两个已排序的子数组
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param mid 中间位置（左子数组的末尾）
     * @param right 右子数组的末尾位置
     */
    void merge(std::vector<T>& arr, size_t left, size_t mid, size_t right) {
        size_t n1 = mid - left + 1;  // 左子数组的长度
        size_t n2 = right - mid;     // 右子数组的长度

        // 创建临时数组来存储左右子数组
        std::vector<T> leftArr(n1), rightArr(n2);

        // 拷贝数据到临时数组
        std::copy(arr.begin() + left, arr.begin() + mid + 1, leftArr.begin());
        std::copy(arr.begin() + mid + 1, arr.begin() + right + 1,
                  rightArr.begin());

        size_t i = 0, j = 0, k = left;

        // 合并左右子数组
        while (i < n1 && j < n2) {
            this->comparisons++;  // 增加比较次数

            // 判断排序方向（递增或递减）
            bool condition = (this->sortOrder == SortOrder::ASCENDING)
                                 ? (leftArr[i] <= rightArr[j])
                                 : (leftArr[i] >= rightArr[j]);

            if (condition) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
            this->loopIterations++;  // 增加循环次数

            // 每 50 次循环显示一次当前状态（可以调整为更高频次）
            if (this->SPEED > 0 && this->GUI) {
                this->display();  // 显示当前排序状态
                this->delay();
            }
        }

        // 将剩余的元素拷贝到原数组
        while (i < n1) {
            arr[k++] = leftArr[i++];
        }
        while (j < n2) {
            arr[k++] = rightArr[j++];
        }

        this->swaps++;  // 合并过程中的交换

        // 合并后显示当前状态
        if (this->SPEED > 0 && this->GUI) {
            this->display();
            this->delay();
        }
    }

    /**
     * @brief 递归拆分数组并执行合并操作
     *
     * @param arr 待排序的数组
     * @param left 左子数组的起始位置
     * @param right 右子数组的末尾位置
     */
    void mergeSort(std::vector<T>& arr, size_t left, size_t right) {
        if (left < right) {
            size_t mid = left + (right - left) / 2;

            // 递归排序左半部分
            mergeSort(arr, left, mid);
            // 递归排序右半部分
            mergeSort(arr, mid + 1, right);

            // 合并两个已排序的部分
            merge(arr, left, mid, right);
        }
    }

   public:
    /**
     * @brief 实现归并排序的排序算法
     */
    void sort() override {
        this->comparisons = 0;
        this->swaps = 0;
        this->loopIterations = 0;

        size_t n = this->arr.size();
        if (n <= 1)
            return;

        // 执行归并排序
        mergeSort(this->arr, 0, n - 1);
    }
};

#endif
