#include "common/machine.hpp"
#include <map>
#include <string>
#include <vector>
#include "headfile.hpp"

void Machine::ManualTest() {
    std::stringstream ss(win.array_input);
    sort_array.clear();
    int value;
    while (ss >> value) {
        if (value > 0) {  // 过滤负数
            sort_array.push_back(value);
        }
    }
    auto sorter = factory.create(win.algorithm_selected);
    sorter->executeSort(speed[win.speed_options[win.playback_speed]],
                        win.mode_selection);  // mode_selection is 0 for auto
}
