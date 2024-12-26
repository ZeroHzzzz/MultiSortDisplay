#include "headfile.hpp"
// #include "menu/windows.hpp"
Windows win;
SortFactory<Arr<int>> factory;
Machine Testmachine;
template struct Arr<int>;

int main() {
    // 调用菜单函数

    // 工厂
    factory.registerType(
        "BubbleSort",
        [](std::vector<Arr<int>>& input, ftxui::ScreenInteractive& screen,
           size_t speed, bool GUI,
           int order) -> std::unique_ptr<Sort<Arr<int>>> {
            return std::make_unique<BubbleSort<Arr<int>>>(input, screen, speed,
                                                          GUI, order);
        });

    factory.registerType(
        "SelectionSort",
        [](std::vector<Arr<int>>& input, ftxui::ScreenInteractive& screen,
           size_t speed, bool GUI, int order) {
            return std::make_unique<SelectionSort<Arr<int>>>(input, screen,
                                                             speed, GUI, order);
        });

    factory.registerType("HeapSort", [](std::vector<Arr<int>>& input,
                                        ftxui::ScreenInteractive& screen,
                                        size_t speed, bool GUI, int order) {
        return std::make_unique<HeapSort<Arr<int>>>(input, screen, speed, GUI,
                                                    order);
    });

    factory.registerType(
        "InsertionSort",
        [](std::vector<Arr<int>>& input, ftxui::ScreenInteractive& screen,
           size_t speed, bool GUI, int order) {
            return std::make_unique<InsertionSort<Arr<int>>>(input, screen,
                                                             speed, GUI, order);
        });

    factory.registerType("IntroSort", [](std::vector<Arr<int>>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI, int order) {
        return std::make_unique<IntroSort<Arr<int>>>(input, screen, speed, GUI,
                                                     order);
    });

    factory.registerType("MergeSort", [](std::vector<Arr<int>>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI, int order) {
        return std::make_unique<MergeSort<Arr<int>>>(input, screen, speed, GUI,
                                                     order);
    });

    factory.registerType("QuickSort", [](std::vector<Arr<int>>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI, int order) {
        return std::make_unique<QuickSort<Arr<int>>>(input, screen, speed, GUI,
                                                     order);
    });

    factory.registerType("ShellSort", [](std::vector<Arr<int>>& input,
                                         ftxui::ScreenInteractive& screen,
                                         size_t speed, bool GUI, int order) {
        return std::make_unique<ShellSort<Arr<int>>>(input, screen, speed, GUI,
                                                     order);
    });

    factory.registerType("TimSort", [](std::vector<Arr<int>>& input,
                                       ftxui::ScreenInteractive& screen,
                                       size_t speed, bool GUI, int order) {
        return std::make_unique<TimSort<Arr<int>>>(input, screen, speed, GUI,
                                                   order);
    });

    win.Show();
    return 0;
}
