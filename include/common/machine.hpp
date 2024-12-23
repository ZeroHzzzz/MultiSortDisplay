#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <map>
#include <string>
#include <thread>
#include <vector>
class Machine {
   public:
    std::vector<int> sort_array;  // Use to store the array to be sorted
    std::map<std::string, int> speed = {{"0.5x", 2000},
                                        {"1x", 1000},
                                        {"1.5x", 750},
                                        {"2x", 500},
                                        {"4x", 250}};

    void AutoTest(ftxui::ScreenInteractive& screen);
    void ManualTest(ftxui::ScreenInteractive& screen);
};
extern std::unique_ptr<std::thread> sort_thread_ptr;