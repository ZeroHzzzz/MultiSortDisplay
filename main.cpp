#include <iostream>
#include "./include/QuickSort.hpp"

int main() {
    QuickSort<int> sorter;

    std::vector<int> data = {10, 7, 8, 9, 1, 5, 2, 6, 3, 4};
    sorter.setData(data);

    std::cout << "Original Array: ";
    sorter.display();

    system("pause");
    std::cout << "Sorting with Optimized QuickSort...\n";
    sorter.executeSort(200, true);  // 200ms 延时显示排序过程

    return 0;
}
