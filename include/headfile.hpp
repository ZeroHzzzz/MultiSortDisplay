#pragma once
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
