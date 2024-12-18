#include <ftxui/component/screen_interactive.hpp>
#include "menu/layout.hpp"

using namespace ftxui;

int main() {
    // 创建布局模块
    Layout layout(
        // algorithm_list
        [] {
            return Renderer([] { return text("选择算法：排序算法1, 2..."); });
        },

        // process_output
        [] { return Renderer([] { return text("算法过程将在此显示..."); }); },

        // input_array
        [] { return Renderer([] { return text("输入数组：如 1,2,3,4"); }); },

        // metrics_output
        [] { return Renderer([] { return text("指标输出：运行时间等..."); }); },

        // settings
        [] { return Renderer([] { return text("设置区域：后续实现"); }); });

    layout.Run();
    return 0;
}