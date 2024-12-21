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
        // IntroSort<int> sorter(win.data, screen,
        //                       speed[win.speed_options[win.playback_speed]],
        //                       (win.mode_selection &&
        //                       win.graphics_selection));

        sorter->sort();
    } catch (...) {
        win.debug_text = "Invalid algorithm selected";
        win.refresh();
    }
}
