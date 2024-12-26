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
                           (win.mode_selection && win.graphics_selection),
                           win.order_selection);
        sorter->resetMetrics(win.metrics);
        win.metrics_Info_text = "The algorithm is running...";
        win.algorithm_Info_text = "Running for " + win.algorithm_selected;
        screen.PostEvent(ftxui::Event::Custom);

        sorter->executeSort();

        sorter->stability = StableTest(win.data) ? "Stable" : "Unstable";

        win.algorithm_Info_text = "Completed!";
        win.metrics_Info_text = "Metrics of " + win.algorithm_selected;
        sorter->updateMetrics(win.metrics);
        screen.PostEvent(ftxui::Event::Custom);
    } catch (...) {
        win.debug_text = "Invalid algorithm selected";
    }
}

void Machine::AutoTest(ftxui::ScreenInteractive& screen, int size) {
    try {
        this->size = size;
        std::vector<Arr<int>> test_data;

        auto it =
            options_map.find(win.data_type_options[win.data_type_selected]);
        if (it != options_map.end()) {
            // 使用成员函数指针调用相应的函数，并传递 vector 参数
            (this->*(it->second))(test_data);
        }

        // win.debug_text = std::to_string(test_data.size());
        // return;
        auto sorter =
            factory.create(win.algorithm_selected, test_data, screen,
                           speed[win.speed_options[win.playback_speed]],
                           (win.mode_selection && win.graphics_selection),
                           win.order_selection);

        sorter->resetMetrics(win.metrics);
        win.metrics_Info_text = "The algorithm is running...";
        win.algorithm_Info_text = "Running for " + win.algorithm_selected;
        screen.PostEvent(ftxui::Event::Custom);

        sorter->executeSort();

        sorter->stability = StableTest(test_data) ? "Stable" : "Unstable";

        win.algorithm_Info_text = "Completed!";
        win.metrics_Info_text = "Metrics of " + win.algorithm_selected;
        sorter->updateMetrics(win.metrics);
        screen.PostEvent(ftxui::Event::Custom);
    } catch (...) {
    }
}

void Machine::Random(std::vector<Arr<int>>& arr) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        arr.push_back(
            Arr<int>(std::rand() % 10000, i));  // 随机数范围：0 到 9999
    }
}

void Machine::Sorted(std::vector<Arr<int>>& arr) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        if (win.order_selection == 0) {
            arr.push_back(Arr<int>(i, i));
        } else {
            arr.push_back(Arr<int>(size - i - 1, i));
        }
    }
}

void Machine::ReverseSorted(std::vector<Arr<int>>& arr) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        if (win.order_selection == 0) {
            arr.push_back(Arr<int>(size - i - 1, i));
        } else {
            arr.push_back(Arr<int>(i, i));
        }
    }
}

void Machine::PartiallySorted(std::vector<Arr<int>>& arr) {
    // 先生成升序数组，然后随机打乱一部分元素
    Sorted(arr);
    for (int i = 0; i < size / 10; ++i) {  // 打乱大约10%的元素
        arr[std::rand() % size] = Arr<int>(std::rand() % 10000, i);
    }
}

void Machine::Duplicates(std::vector<Arr<int>>& arr) {
    arr.clear();
    for (int i = 0; i < size; ++i) {
        arr.push_back(Arr<int>(std::rand() % 5000, i));
    }
}

void Machine::Same(std::vector<Arr<int>>& arr) {
    arr.clear();
    int value = std::rand();
    for (int i = 0; i < size; ++i) {
        arr.push_back(Arr<int>(value, i));
    }
}

bool Machine::StableTest(std::vector<Arr<int>>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i].value == arr[i - 1].value) {
            if (arr[i].index < arr[i - 1].index) {
                // 如果索引顺序发生了变化，说明排序不稳定
                return false;
            }
        }
    }

    // 如果没有发现稳定性问题，返回true
    return true;
}