#ifndef SORT_HPP
#define SORT_HPP

#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>  // for memory usage calculation
#include <thread>
#include <vector>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"  // Windows
#else
#define CLEAR_SCREEN "clear"  // Linux/Unix
#endif

/**
 * @brief 排序方向枚举
 */
enum class SortOrder {
    ASCENDING,  // 递增
    DESCENDING  // 递减
};

// 定义显示方式接口
template <typename T>
struct Display {
    virtual void operator()(const std::vector<T>& arr) const = 0;
    virtual ~Display() = default;
};

// 图形化显示
template <typename T>
struct DisplayPic : public Display<T> {
    void operator()(const std::vector<T>& arr) const override {
        system(CLEAR_SCREEN);
        for (const auto& val : arr) {
            for (int i = 0; i < val; ++i) {
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        std::cout << std::string(20, '-') << std::endl;  // 分隔线
    }
};

// 显示数字
template <typename T>
struct DisplayNum : public Display<T> {
    void operator()(const std::vector<T>& arr) const override {
        for (const auto& val : arr) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

/**
 * @brief 排序算法的基类，提供排序过程中的通用功能和指标统计
 *
 * @tparam T 数据类型
 */
template <typename T,
          typename DisplayType = DisplayPic<T>>  // 改变可视化方式改这里就行
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
    DisplayType display_;
    bool GUI = false;
    size_t SPEED = 0;

    // 重置所有指标
    void resetMetrics() {
        comparisons = swaps = functionCalls = loopIterations = 0;
        recursionDepth = maxRecursionDepth = 0;
        runTime = std::chrono::duration<double>::zero();
    }

    // 交换元素
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
        swaps++;
    }

    // 延时函数
    void delay() const {
        std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
    }

    // 计算数组占用的内存
    size_t calculateMemoryUsage() const {
        size_t arrayMemory = arr.capacity() * sizeof(T);  // 数组分配的内存
        size_t vectorMetadata = sizeof(std::vector<T>);   // vector 的元数据内存
        size_t stackMemory =
            maxRecursionDepth * 64;  // 递归栈内存，以每层栈帧64字节算
        return arrayMemory + vectorMetadata + stackMemory;
    }

   public:
    /**
     * @brief 设置待排序的数据
     *
     * @param input 输入的数据数组
     */
    void setData(const std::vector<T>& input) {
        arr = input;
        resetMetrics();
    }

    /**
     * @brief 设置排序方向
     *
     * @param order 排序方向（递增或递减）
     */
    void setSortOrder(SortOrder order) { sortOrder = order; }

    /**
     * @brief 可视化
     */
    virtual void display() const { display_(arr); }

    // 执行排序
    void executeSort(int speed = 0, bool gui = false) {
        GUI = gui;
        SPEED = speed;
        resetMetrics();
        auto start = std::chrono::high_resolution_clock::now();

        functionCalls++;
        sort();

        auto end = std::chrono::high_resolution_clock::now();
        runTime = end - start;

        std::cout << "Sorted Array: ";
        display();
        displayMetrics();
        system("pause");
    }

    // 输出排序指标
    void displayMetrics() const {
        std::cout << "Sorting Metrics:\n";
        std::cout << "  Comparisons: " << comparisons << "\n";
        std::cout << "  Swaps: " << swaps << "\n";
        std::cout << "  Function Calls: " << functionCalls << "\n";
        std::cout << "  Loop Iterations: " << loopIterations << "\n";
        std::cout << "  Max Recursion Depth: " << maxRecursionDepth << "\n";
        std::cout << "  Memory Usage: " << calculateMemoryUsage() << " bytes\n";
        std::cout << "  Run Time: " << runTime.count() << " seconds\n";
    }

    /**
     * @brief 纯虚函数，子类需要实现具体的排序逻辑
     */
    virtual void sort() = 0;

    virtual ~Sort() = default;
};

#endif
