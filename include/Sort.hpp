#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>  // for memory usage calculation
#include <thread>
#include <vector>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"  // Windows 清屏命令
#else
#define CLEAR_SCREEN "clear"  // Linux/Unix 清屏命令
#endif

/**
 * @brief 排序方向枚举
 */
enum class SortOrder {
    ASCENDING,  // 递增排序
    DESCENDING  // 递减排序
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
    void delay(int milliseconds) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    // 计算数组占用的内存
    size_t calculateMemoryUsage() const {
        size_t arrayMemory = arr.capacity() * sizeof(T);  // 数组分配的内存
        size_t vectorMetadata = sizeof(std::vector<T>);   // vector 的元数据内存
        size_t stackMemory =
            maxRecursionDepth * 64;  // 递归栈内存（假设每层栈帧为64字节）
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
     * @brief 显示当前数组内容
     */
    virtual void display() const {
        for (const auto& val : arr) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief 绘图函数：控制台输出数组状态，清除屏幕后重新绘制
     *
     * @param scale 缩放比例
     */
    virtual void draw(int scale = 1) const {
        system(CLEAR_SCREEN);  // 清除屏幕

        T maxElement =
            *std::max_element(arr.begin(), arr.end());  // 获取数组最大值
        for (const auto& val : arr) {
            int height = val * scale / maxElement;  // 根据最大值缩放高度
            for (int i = 0; i < height; ++i) {
                std::cout << "#";
            }
            std::cout << std::endl;
        }
        std::cout << std::string(20, '-') << std::endl;  // 分隔线
    }

    // 执行排序
    void executeSort(int speed = 0, bool gui = false) {
        resetMetrics();
        auto start = std::chrono::high_resolution_clock::now();

        functionCalls++;
        sort(speed, gui);

        auto end = std::chrono::high_resolution_clock::now();
        runTime = end - start;

        std::cout << "Sorted Array: ";
        display();
        displayMetrics();
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
     *
     * @param speed 延时速度（控制排序过程的动画速度）
     * @param gui 是否启用图形化输出
     */
    virtual void sort(int speed = 0, bool gui = false) = 0;

    virtual ~Sort() = default;
};

#endif
