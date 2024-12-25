#pragma once

#include <unistd.h>
#include <atomic>
#include <chrono>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
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
   public:
    std::vector<T>& arr;                         // 存储待排序数组
    std::string stability = "";                  // 稳定性
    size_t comparisons = 0;                      // 比较操作的次数
    size_t swaps = 0;                            // 交换操作的次数
    size_t functionCalls = 0;                    // 递归函数调用的次数
    size_t loopIterations = 0;                   // 循环执行的次数
    size_t recursionDepth = 0;                   // 当前递归的深度
    size_t maxRecursionDepth = 0;                // 最大递归深度
    std::chrono::duration<double> runTime;       // 排序运行时间
    SortOrder sortOrder = SortOrder::ASCENDING;  // 排序方向，默认为递增

    ftxui::ScreenInteractive& screen;
    bool GUI = false;
    size_t SPEED = 0;

    Sort(std::vector<T>& input,
         ftxui::ScreenInteractive& screen,
         size_t speed,
         bool GUI,
         int order = 0)
        : arr(input), screen(screen), SPEED(speed), GUI(GUI) {
        sortOrder = (order == 0) ? SortOrder::ASCENDING : SortOrder::DESCENDING;
    };
    void swap(T& a, T& b);                // 交换元素
    size_t calculateMemoryUsage() const;  // 计算数组占用的内存

    // void setData(const std::vector<T>& input);  // 设置待排序的数据
    void setSortOrder(SortOrder order);                 // 设置排序方向
    void executeSort(int speed = 0, bool gui = false);  // 执行排序
    void updateMetrics(std::map<std::string, std::string>&) const;
    void resetMetrics(std::map<std::string, std::string>&);  // 重置所有指标

    virtual void sort() = 0;  // 纯虚函数，子类需要实现具体的排序逻辑
    virtual std::string getStability() const {
        return "Unknown";  // 默认返回一个“未知”值，子类可以重写此方法
    }
    virtual ~Sort() = default;
};

template <typename T>
void Sort<T>::resetMetrics(std::map<std::string, std::string>& metrics) {
    comparisons = swaps = functionCalls = loopIterations = 0;
    recursionDepth = maxRecursionDepth = 0;
    runTime = std::chrono::duration<double>::zero();
    stability = "";
    updateMetrics(metrics);
}

template <typename T>
void Sort<T>::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    swaps++;
}

template <typename T>
size_t Sort<T>::calculateMemoryUsage() const {
    size_t arrayMemory = arr.capacity() * sizeof(T);  // 数组分配的内存
    size_t vectorMetadata = sizeof(std::vector<T>);   // vector 的元数据内存
    size_t stackMemory =
        maxRecursionDepth * 64;  // 递归栈内存，以每层栈帧64字节算
    return arrayMemory + vectorMetadata + stackMemory;
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
}

template <typename T>
void Sort<T>::updateMetrics(std::map<std::string, std::string>& metrics) const {
    metrics["Comparisons"] = std::to_string(comparisons);
    metrics["Swaps"] = std::to_string(swaps);
    metrics["FunctionCall"] = std::to_string(functionCalls);
    metrics["LoopIterations"] = std::to_string(loopIterations);
    metrics["Depth"] = std::to_string(maxRecursionDepth);
    metrics["Memory"] = std::to_string(calculateMemoryUsage());
    metrics["RunTime"] = std::to_string(runTime.count());
    metrics["Stability"] = stability;
}
