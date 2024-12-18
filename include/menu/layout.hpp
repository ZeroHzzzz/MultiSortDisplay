#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <ftxui/component/component.hpp>           // for Component
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <ftxui/dom/elements.hpp>                  // for Elements
#include <functional>                              // for std::function
#include <string>

using namespace ftxui;

class Layout {
   public:
    // 构造函数：允许用户传入不同组件
    Layout(std::function<Component()> algorithm_list,
           std::function<Component()> process_output,
           std::function<Component()> input_array,
           std::function<Component()> metrics_output,
           std::function<Component()> settings)
        : algorithm_list_(algorithm_list),
          process_output_(process_output),
          input_array_(input_array),
          metrics_output_(metrics_output),
          settings_(settings) {}

    // 渲染界面
    void Run() {
        auto screen = ScreenInteractive::Fullscreen();
        screen.Loop(Render());
    }

   private:
    // 模块接口，允许用户自定义组件
    std::function<Component()> algorithm_list_;
    std::function<Component()> process_output_;
    std::function<Component()> input_array_;
    std::function<Component()> metrics_output_;
    std::function<Component()> settings_;

    // 布局实现
    Component Render() {
        return Renderer([&] {
            return vbox({
                hbox({
                    // 左侧 algorithm list
                    window(text(" algorithm list "),
                           algorithm_list_()->Render()) |
                        size(WIDTH, EQUAL, 20),

                    // 中部 算法过程输出
                    window(text(" 算法过程输出（后续实现） "),
                           process_output_()->Render()) |
                        flex,

                    // 右侧 需要排序的数组 & 指标输出
                    vbox({
                        window(text(" 需要排序的数组输入 "),
                               input_array_()->Render()),
                        window(text(" 指标输出，后续实现 "),
                               metrics_output_()->Render()),
                    }) | size(WIDTH, EQUAL, 30),
                }) | flex,

                // 底部 Settings
                window(text(" Settings "), settings_()->Render()) |
                    size(HEIGHT, EQUAL, 3),
            });
        });
    }
};

#endif  // LAYOUT_HPP
