#include "headfile.hpp"
// #include "menu/windows.hpp"
Windows win;
SortFactory<int> factory;
Machine Testmachine;

int main() {
    // 调用菜单函数

    // 工厂
    // factory.registerType("BubbleSort",
    //                      []() { return std::make_unique<BubbleSort<int>>();
    //                      });
    // factory.registerType("SelectionSort", []() {
    //     return std::make_unique<SelectionSort<int>>();
    // });
    // factory.registerType("HeapSort",
    //                      []() { return std::make_unique<HeapSort<int>>(); });
    // factory.registerType("InsertionSort", []() {
    //     return std::make_unique<InsertionSort<int>>();
    // });
    // factory.registerType("IntroSort",
    //                      []() { return std::make_unique<IntroSort<int>>();
    //                      });
    // factory.registerType("MergeSort",
    //                      []() { return std::make_unique<MergeSort<int>>();
    //                      });
    // factory.registerType("QuickSort",
    //                      []() { return std::make_unique<QuickSort<int>>();
    //                      });
    // factory.registerType("ShellSort",
    //                      []() { return std::make_unique<ShellSort<int>>();
    //                      });
    // factory.registerType("TimSort",
    //                      []() { return std::make_unique<TimSort<int>>(); });

    win.Show();
    return 0;
}
