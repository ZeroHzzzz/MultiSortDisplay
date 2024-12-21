#ifndef SORT_HPP
#define SORT_HPP

#include <unistd.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
/**
 * @brief 排序方向枚举
 */
enum class SortOrder {
    ASCENDING,  // 递增
    DESCENDING  // 递减
};

/**
 * @brief 排序算法的基类，提供排序过程中的通用功能和指标统计
 *
 * @tparam T 数据类型
 */
template <typename T>
class Sort {
   protected:
    std::vector<T> arr;                          // 存储待排序数组
    size_t comparisons = 0;                      // 比较操作的次数
    size_t swaps = 0;                            // 交换操作的次数
    size_t functionCalls = 0;                    // 递归函数调用的次数
    size_t loopIterations = 0;                   // 循环执行的次数
    size_t recursionDepth = 0;                   // 当前递归的深度
    size_t maxRecursionDepth = 0;                // 最大递归深度
    std::chrono::duration<double> runTime;       // 排序运行时间
    SortOrder sortOrder = SortOrder::ASCENDING;  // 排序方向，默认为递增
    bool GUI = false;
    size_t SPEED = 0;

    void resetMetrics();                  // 重置所有指标
    void swap(T& a, T& b);                // 交换元素
    void delay() const;                   // 延时函数
    size_t calculateMemoryUsage() const;  // 计算数组占用的内存

   public:
    void setData(const std::vector<T>& input);  // 设置待排序的数据
    void setSortOrder(SortOrder order);         // 设置排序方向
    void executeSort(int speed = 0, bool gui = false);  // 执行排序
    void displayMetrics() const;                        // 输出排序指标

    virtual void sort() = 0;  // 纯虚函数，子类需要实现具体的排序逻辑

    virtual ~Sort() = default;
};
template <typename T>
void Sort<T>::resetMetrics() {
    comparisons = swaps = functionCalls = loopIterations = 0;
    recursionDepth = maxRecursionDepth = 0;
    runTime = std::chrono::duration<double>::zero();
}

template <typename T>
void Sort<T>::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    swaps++;
}

template <typename T>
void Sort<T>::delay() const {
    sleep(1);
    // std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
}

template <typename T>
size_t Sort<T>::calculateMemoryUsage() const {
    size_t arrayMemory = arr.capacity() * sizeof(T);  // 数组分配的内存
    size_t vectorMetadata = sizeof(std::vector<T>);  // vector 的元数据内存
    size_t stackMemory =
        maxRecursionDepth * 64;  // 递归栈内存，以每层栈帧64字节算
    return arrayMemory + vectorMetadata + stackMemory;
}

template <typename T>
void Sort<T>::setData(const std::vector<T>& input) {
    arr = input;
    resetMetrics();
}

template <typename T>
void Sort<T>::setSortOrder(SortOrder order) {
    sortOrder = order;
}

template <typename T>
void Sort<T>::executeSort(int speed, bool gui) {
    GUI = gui;
    SPEED = speed;
    resetMetrics();
    auto start = std::chrono::high_resolution_clock::now();

    functionCalls++;
    sort();
    auto end = std::chrono::high_resolution_clock::now();
    runTime = end - start;

    // display();  // 可添加显示逻辑
    displayMetrics();
    // system("pause");
}

template <typename T>
void Sort<T>::displayMetrics() const {
    // std::cout << "Sorting Metrics:\n";
    // std::cout << "  Comparisons: " << comparisons << "\n";
    // std::cout << "  Swaps: " << swaps << "\n";
    // std::cout << "  Function Calls: " << functionCalls << "\n";
    // std::cout << "  Loop Iterations: " << loopIterations << "\n";
    // std::cout << "  Max Recursion Depth: " << maxRecursionDepth << "\n";
    // std::cout << "  Memory Usage: " << calculateMemoryUsage() << " bytes\n";
    // std::cout << "  Run Time: " << runTime.count() << " seconds\n";
}

#endif
