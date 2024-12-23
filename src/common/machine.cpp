#include "common/machine.hpp"
#include <map>
#include <string>
#include <vector>
#include "headfile.hpp"
std::unique_ptr<std::thread> sort_thread_ptr = nullptr;
void Machine::ManualTest(ftxui::ScreenInteractive& screen) {
    try {
        auto sorter =
            factory.create(win.algorithm_selected, win.data, screen,
                           speed[win.speed_options[win.playback_speed]],
                           (win.mode_selection && win.graphics_selection));
        sorter->resetMetrics(win.metrics);
        win.metrics_Info_text = "The algorithm is running...";
        win.algorithm_Info_text = "Running for " + win.algorithm_selected;
        screen.PostEvent(ftxui::Event::Custom);

        sorter->sort();

        win.algorithm_Info_text = "Comp    arr.clear();leted!";
        win.metrics_Info_text = "Metrics of " + win.algorithm_selected;
        sorter->updateMetrics(win.metrics);
        screen.PostEvent(ftxui::Event::Custom);
    } catch (...) {
        win.debug_text = "Invalid algorithm selected";
    }
}

void Machine::AutoTest(ftxui::ScreenInteractive& screen) {
    try {
        auto sorter =
            factory.create(win.algorithm_selected, win.data, screen,
                           speed[win.speed_options[win.playback_speed]],
                           (win.mode_selection && win.graphics_selection));
        sorter->resetMetrics(win.metrics);
        win.metrics_Info_text = "The algorithm is running...";
        win.algorithm_Info_text = "Running for " + win.algorithm_selected;
        screen.PostEvent(ftxui::Event::Custom);

        sorter->sort();

        win.algorithm_Info_text = "Comp    arr.clear();leted!";
        win.metrics_Info_text = "Metrics of " + win.algorithm_selected;
        sorter->updateMetrics(win.metrics);
        screen.PostEvent(ftxui::Event::Custom);
    } catch (...) {
    }
}

void Random(std::vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 10000;  // 随机数范围：0 到 9999
    }
}

void Sorted(std::vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = i;  // 生成升序排列的数组
    }
}

void ReverseSorted(std::vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i - 1;  // 生成降序排列的数组
    }
}

void PartiallySorted(std::vector<int>& arr, int size) {
    // 先生成升序数组，然后随机打乱一部分元素
    Sorted(arr, size);
    for (int i = 0; i < size / 10; ++i) {  // 打乱大约10%的元素
        arr[std::rand() % size] = std::rand() % 10000;
    }
}

void Duplicates(std::vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 5000;  // 生成 0 到 4999 的重复元素
    }
}

void Same(std::vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = 42;  // 所有元素都是 42
    }
}
