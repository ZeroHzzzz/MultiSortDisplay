#include "common/machine.hpp"
#include <map>
#include <string>
#include <vector>
#include "headfile.hpp"
std::unique_ptr<std::thread> sort_thread_ptr = nullptr;
void Machine::ManualTest(ftxui::ScreenInteractive& screen) {
    try {
        // auto sorter = factory.create(win.algorithm_selected);
        BubbleSort<int> sorter(win.data, screen,
                               speed[win.speed_options[win.playback_speed]]);

        sorter.sort();
    } catch (...) {
        win.debug_text = "Invalid algorithm selected";
        win.refresh();
    }
}
