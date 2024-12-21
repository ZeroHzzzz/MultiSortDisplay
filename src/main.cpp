#include "headfile.hpp"
// #include "menu/windows.hpp"
Windows win;
SortFactory<int> factory;
Machine Testmachine;

int main() {
    // 调用菜单函数

    // 工厂
    factory.registerType("BubbleSort", [](std::vector<int>& input,
                                          ftxui::ScreenInteractive& screen,
                                          size_t speed, bool GUI) {
        return std::make_unique<BubbleSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("SelectionSort", [](std::vector<int>& input,
                                             ftxui::ScreenInteractive& screen,
                                             size_t speed, bool GUI) {
        return std::make_unique<SelectionSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("HeapSort", [](std::vector<int>& input,
                                        ftxui::ScreenInteractive& screen,
                                        size_t speed, bool GUI) {
        return std::make_unique<HeapSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("InsertionSort", [](std::vector<int>& input,
                                             ftxui::ScreenInteractive& screen,
                                             size_t speed, bool GUI) {
        return std::make_unique<InsertionSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("IntroSort", [](std::vector<int>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI) {
        return std::make_unique<IntroSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("MergeSort", [](std::vector<int>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI) {
        return std::make_unique<MergeSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("QuickSort", [](std::vector<int>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI) {
        return std::make_unique<QuickSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType("ShellSort", [](std::vector<int>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI) {
        return std::make_unique<ShellSort<int>>(input, screen, speed, GUI);
    });

    factory.registerType(
        "TimSort", [](std::vector<int>& input, ftxui::ScreenInteractive& screen,
                      size_t speed, bool GUI) {
            return std::make_unique<TimSort<int>>(input, screen, speed, GUI);
        });

    win.Show();
    return 0;
}
