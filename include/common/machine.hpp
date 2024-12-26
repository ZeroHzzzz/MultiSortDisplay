#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include "common/Arr.hpp"

class Machine {
   public:
    std::vector<Arr<int>> sort_array;  // Use to store the array to be sorted
    std::map<std::string, int> speed = {{"0.5x", 2000},
                                        {"1x", 1000},
                                        {"1.5x", 750},
                                        {"2x", 500},
                                        {"4x", 250}};
    // std::unordered_map<std::string,
    //                    std::function<void(Machine*, std::vector<int>&)>>
    //     options_map = {{"Random", &Machine::Random},
    //                    {"Sorted", &Machine::Sorted},
    //                    {"Reversed", &Machine::ReverseSorted},
    //                    {"PartiallySorted", &Machine::PartiallySorted},
    //                    {"Duplicates", &Machine::Duplicates},
    //                    {"Same", &Machine::Same}};
    std::unordered_map<std::string, void (Machine::*)(std::vector<Arr<int>>&)>
        options_map = {{"Random", &Machine::Random},
                       {"Sorted", &Machine::Sorted},
                       {"Reversed", &Machine::ReverseSorted},
                       {"PartiallySorted", &Machine::PartiallySorted},
                       {"Duplicates", &Machine::Duplicates},
                       {"Same", &Machine::Same}};
    ;

    void AutoTest(ftxui::ScreenInteractive& screen, int size);
    void ManualTest(ftxui::ScreenInteractive& screen);

    void Random(std::vector<Arr<int>>& arr);
    void Sorted(std::vector<Arr<int>>& arr);
    void ReverseSorted(std::vector<Arr<int>>& arr);
    void PartiallySorted(std::vector<Arr<int>>& arr);
    void Duplicates(std::vector<Arr<int>>& arr);
    void Same(std::vector<Arr<int>>& arr);

    size_t size = 10001;
};
extern std::unique_ptr<std::thread> sort_thread_ptr;