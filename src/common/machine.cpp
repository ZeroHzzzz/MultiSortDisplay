#include "common/machine.hpp"
#include <map>
#include <string>
#include <vector>
#include "headfile.hpp"

void Machine::ManualTest() {
    std::stringstream ss(win.array_input);
    sort_array.clear();
    sort_array = {3, 2, 1, 3, 5};
    // int value;
    // while (ss >> value) {
    //     if (value > 0) {  // 过滤负数
    //         sort_array.push_back(value);
    //     }
    // }
    // win.debug_text = win.algorithm_selected;
    // win.refresh();
    try {
        // auto sorter = factory.create(win.algorithm_selected);
        BubbleSort<int> sorter;
        sorter.setData(sort_array);
        win.update(sort_array);
        sorter.executeSort(speed[win.speed_options[win.playback_speed]],
                           win.mode_selection);  // mode_selection is 0 for Auto

        // win.debug_text = win.algorithm_selected;
        // win.refresh();
    } catch (...) {
        win.debug_text = "Invalid algorithm selected";
        win.refresh();
    }
}
