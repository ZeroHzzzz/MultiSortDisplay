// Windows.cpp
#include "windows/windows.hpp"
#include "headfile.hpp"
void Windows::Show() {
    auto algorithm_list_container = Container::Vertical({});
    for (const auto& name : algorithms) {
        algorithm_list_container->Add(
            Button(name, [&] { algorithm_selected = name; }));
    }

    auto algorithm_list = Renderer(algorithm_list_container, [&] {
        return window(text(" algorithm list "),
                      algorithm_list_container->Render()) |
               size(WIDTH, EQUAL, 20);
    });

    // 中间 算法过程输出
    auto process_output_renderer = Renderer([&] {
        std::vector<Element> bars;
        int max_height = 10;  // 最大显示高度
        if (!data.empty()) {
            int max_value = *std::max_element(data.begin(), data.end());
            for (int& value : data) {
                value = max_value > max_height ? value * max_height / max_value
                                               : value;
            }
        }
        for (int value : data) {
            std::string result(value, '#');
            bars.push_back(hbox({
                text(std::to_string(value)),  // 显示数值
                text(result),
            }));
        }

        // 修正 window 的调用
        return window(text(" 算法过程输出 "),
                      vbox(std::move(bars))  // vbox 应该放入 bars
                      ) |
               flex;
    });

    // 右上角 需要排序的数组输入
    auto array_input_component = Input(&array_input, "Enter array here...");
    auto array_input_renderer = Renderer(array_input_component, [&] {
        return window(text(" 需要排序的数组输入 "),
                      array_input_component->Render()) |
               size(HEIGHT, EQUAL, 8);
    });

    // 右中 指标输出
    auto metrics_output_renderer = Renderer([&] {
        return window(text(" 指标输出 "), vbox({
                                              text("a:"),
                                              text(debug_text),
                                          })) |
               flex;
    });

    // 底部按钮和设置
    // Run 按钮
    auto run_button = Button("Run", [&] { Testmachine.ManualTest(); });

    // Exit 按钮
    auto exit_button = Button("Exit", [&] {
        screen.Exit();  // 捕获 screen 以退出程序
    });

    // 自定义按钮渲染器
    auto run_button_renderer = Renderer(run_button, [&] {
        return run_button->Render() | center | border |
               size(WIDTH, GREATER_THAN, 15) | size(HEIGHT, GREATER_THAN, 5);
    });

    auto exit_button_renderer = Renderer(exit_button, [&] {
        return exit_button->Render() | center | border |
               size(WIDTH, GREATER_THAN, 15) | size(HEIGHT, GREATER_THAN, 5);
    });

    // 按钮布局
    auto buttons_container = Container::Horizontal({
        run_button,
        exit_button,
    });

    auto buttons_renderer = Renderer(buttons_container, [&] {
        return hbox({
            run_button_renderer->Render(),
            separator(),
            exit_button_renderer->Render(),
        });
    });

    // 设置项
    auto graphics_toggle =
        Toggle(&graphics_toggle_options, &graphics_selection);
    auto speed_toggle = Toggle(&speed_options, &playback_speed);
    auto mode_toggle = Toggle(&mode_toggle_options, &mode_selection);

    auto settings_container = Container::Vertical({
        graphics_toggle,
        speed_toggle,
        mode_toggle,
    });

    auto settings_renderer = Renderer(settings_container, [&] {
        return window(
            text(" Settings "),
            hbox({
                vbox({hbox({text("Graphics: "),
                            text(graphics_toggle_options[graphics_selection])}),
                      hbox({text("Playback Speed: "),
                            text(speed_options[playback_speed])}),
                      hbox({text("Mode: "),
                            text(mode_toggle_options[mode_selection])})}) |
                    size(WIDTH, GREATER_THAN, 30),
                vbox({
                    graphics_toggle->Render(),
                    speed_toggle->Render(),
                    mode_toggle->Render(),
                }),
            }));
    });

    // 底部布局（Settings 在左，按钮在右）
    auto bottom_renderer = Renderer([&] {
        return hbox({
            settings_renderer->Render() | flex,  // Settings 靠左，占据剩余空间
            buttons_renderer->Render(),          // 按钮靠右
        });
    });

    // 右侧布局（右上角数组输入 + 右中指标输出）
    auto right_panel = Renderer([&] {
        return vbox({
                   array_input_renderer->Render(),
                   metrics_output_renderer->Render() |
                       flex,  // 指标输出填充剩余空间
               }) |
               size(WIDTH, EQUAL, 30);
    });

    // 主布局
    auto main_container = Container::Vertical({
        algorithm_list_container,
        array_input_component,
        buttons_container,
        settings_container,
    });

    auto main_renderer = Renderer(main_container, [&] {
        return vbox({
            hbox({
                algorithm_list->Render(),
                process_output_renderer->Render(),
                right_panel->Render(),
            }) | flex,
            bottom_renderer->Render(),  // 底部区域，包括 Settings 和按钮
        });
    });

    // 启动界面
    screen.Loop(main_renderer);
}

void Windows::refresh() {
    screen.Post([&] {});
}

void Windows::update(std::vector<int>& update_vector) {
    // data.clear();
    data = update_vector;
    refresh();
}
