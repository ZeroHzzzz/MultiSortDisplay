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
    TimSort<int, DisplayPic<int>> timsort;
    BubbleSort<int, DisplayPic<int>> bubblesort;
    HeapSort<int, DisplayPic<int>> heapsort;
    InsertionSort<int, DisplayPic<int>> insertionsort;
    IntroSort<int, DisplayPic<int>> introsort;
    MergeSort<int, DisplayPic<int>> mergesort;
    QuickSort<int, DisplayPic<int>> quicksort;
    SelectionSort<int, DisplayPic<int>> selectionsort;
    ShellSort<int, DisplayPic<int>> shellsort;

    std::vector<int> data = {10, 7, 8, 9, 1, 5, 2, 6, 3, 4};
    bubblesort.setData(data);

    std::cout << "Original Array: ";
    bubblesort.display();

    system("pause");
    std::cout << "Sorting with Optimized QuickSort...\n";
    bubblesort.executeSort(2000, false);  // 200ms 延时显示排序过程

    return 0;
}
