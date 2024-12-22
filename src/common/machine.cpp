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
