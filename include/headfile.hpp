#ifndef _HEADFILE_HPP_
#define _HEADFILE_HPP_
#include "common/factory.hpp"
#include "common/machine.hpp"
#include "sortAlgorithm/BubbleSort.hpp"
#include "sortAlgorithm/HeapSort.hpp"
#include "sortAlgorithm/InsertionSort.hpp"
#include "sortAlgorithm/IntroSort.hpp"
#include "sortAlgorithm/MergeSort.hpp"
#include "sortAlgorithm/QuickSort.hpp"
#include "sortAlgorithm/SelectionSort.hpp"
#include "sortAlgorithm/ShellSort.hpp"
#include "sortAlgorithm/TimSort.hpp"
#include "windows/windows.hpp"

extern Machine Testmachine;
extern SortFactory<int> factory;
extern Windows win;  // 窗口

template class SortFactory<int>;
// Explicit instantiation for BubbleSort
template class BubbleSort<int>;

// Explicit instantiation for HeapSort
template class HeapSort<int>;

// Explicit instantiation for InsertionSort
template class InsertionSort<int>;

// Explicit instantiation for IntroSort
template class IntroSort<int>;

// Explicit instantiation for MergeSort
template class MergeSort<int>;

// Explicit instantiation for QuickSort
template class QuickSort<int>;

// Explicit instantiation for SelectionSort
template class SelectionSort<int>;

// Explicit instantiation for ShellSort
template class ShellSort<int>;

// Explicit instantiation for TimSort
template class TimSort<int>;

#endif  // _HEADFILE_HPP_