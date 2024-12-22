// Windows.hpp
#ifndef _WINDOWS_HPP_
#define _WINDOWS_HPP_
#include <algorithm>  // for std::swap
#include <atomic>
#include <chrono>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace ftxui;

/**
 * @brief Windows 类，用于管理和显示排序算法的可视化界面
 */
class Windows {
   public:
    ftxui::ScreenInteractive screen =
        ScreenInteractive::Fullscreen();  // 提前定义 screen

    // 状态变量
    std::string debug_text = "";
    std::string metrics_Info_text = "";
    std::string algorithm_Info_text =
        "Please select an algorithm. Default : BubbleSort";  // 算法信息
    std::string algorithm_selected = "BubbleSort";           // 用户选择的算法
    std::string array_input = "";                            // 用户输入的数组
    std::vector<int> data = {1, 5, 3, 3, 6, 4, 7, 1};  // 用于显示的数组数据
    std::atomic<bool> sort_running{false};

    // 设置项状态变量
    int graphics_selection = 1;  // Graphics 选项索引
    int playback_speed = 1;      // Playback Speed 选项索引
    int mode_selection = 1;      // Mode 选项索引

    std::vector<std::string> graphics_toggle_options = {"Disabled", "Enabled"};
    std::vector<std::string> speed_options = {"0.5x", "1x", "2x", "4x"};
    std::vector<std::string> mode_toggle_options = {"Automatic", "Manual"};
    std::vector<std::string> algorithms = {
        "BubbleSort",    "HeapSort",  "InsertionSort",
        "Introsort",     "MergeSort", "QuickSort",
        "SelectionSort", "ShellSort", "TimSort"};
    std::map<std::string, std::string> metrics = {
        {"Comparisons", ""},    {"Swaps", ""},    {"FunctionCall", ""},
        {"LoopIterations", ""}, {"Depth", ""},    {"Memory", ""},
        {"RunTime", ""},        {"Stability", ""}};
    /**
     * @brief 显示主界面Depth
     */
    void Show();
};

#endif
