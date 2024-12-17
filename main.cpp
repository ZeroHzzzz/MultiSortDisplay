#include <iostream>
#include "./include/BubbleSort.hpp"
#include "./include/HeapSort.hpp"
#include "./include/InsertionSort.hpp"
#include "./include/IntroSort.hpp"
#include "./include/MergeSort.hpp"
#include "./include/QuickSort.hpp"
#include "./include/SelectionSort.hpp"
#include "./include/ShellSort.hpp"
#include "./include/TimSort.hpp"
int main() {
    TimSort<int, DisplayPic<int>> sorter;
    std::vector<int> data = {10, 7, 8, 9, 1, 5, 2, 6, 3, 4};
    sorter.setData(data);

    std::cout << "Original Array: ";
    sorter.display();

    system("pause");
    std::cout << "Sorting with Optimized QuickSort...\n";
    sorter.executeSort(2000, true);  // 200ms 延时显示排序过程

    return 0;
}
