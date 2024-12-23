// Windows.cpp
#include "windows/windows.hpp"
#include "headfile.hpp"

void Windows::Show() {
    auto algorithm_list_container = Container::Vertical({});
    // for (auto it = algorithms.begin(); it != algorithms.end(); ++it) {
    //     // TODO: Add a separator
    //     algorithm_list_container->Add(Button(*it, [&] {
    //         algorithm_selected = *it;
    //         algorithm_Info_text = "selected for " + algorithm_selected;
    //         screen.PostEvent(ftxui::Event::Custom);
    //     }));
    // }

    for (const auto& name : algorithms) {
        algorithm_list_container->Add(Button(name, [&] {
            algorithm_selected = name;
            algorithm_Info_text = "selected for " + algorithm_selected;
            screen.PostEvent(ftxui::Event::Custom);
        }));
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
                      vbox(text(algorithm_Info_text),
                           std::move(bars))  // vbox 应该放入 bars
                      ) |
               flex;
    });

    // 右上角 需要排序的数组输入
    // ftxui::Component array_input_renderer;
    // auto array_input_component = Input(&array_input, "Enter array here...");
    // auto data_type_component =
    //     Radiobox(&data_type_options, &data_type_selected);

    // if (mode_selection == 0) {
    //     array_input_renderer = Renderer([&] {
    //         // 根据 mode_selection 渲染相应的组件
    //         auto current_component = array_input_component->Render();

    //         return window({text("需要排序的数组输入")}, current_component) |
    //                size(HEIGHT, EQUAL, 8);
    //     });
    // } else {
    //     array_input_renderer = Renderer(data_type_component, [&] {
    //         return window({text("Data Type")}, data_type_component->Render())
    //         |
    //                size(HEIGHT, EQUAL, 8);
    //     });
    // }
    auto data_type_component =
        Radiobox(&data_type_options, &data_type_selected);
    auto array_input_component = Input(&array_input, "Enter array here...");
    auto array_input_renderer = Renderer([&] {
        // 根据 mode_selection 渲染相应的组件
        auto current_component = (mode_selection == 1)
                                     ? array_input_component->Render()
                                     : data_type_component->Render();

        return window({text("需要排序的数组输入")}, current_component) |
               size(HEIGHT, EQUAL, 8);
    });

    // 右中 指标输出
    auto metrics_output_renderer = Renderer([&] {
        return window(text(" 指标输出 "),
                      vbox({//   text("a:"),
                            text(metrics_Info_text) | center,
                            separator() | size(WIDTH, EQUAL, 15) | center,
                            hbox({vbox({
                                      text("Stablity:"),
                                      text("Comparisons:"),
                                      text("Swaps:"),
                                      text("Function Calls:"),
                                      text("Loop Iterations:"),
                                      text("Max Recursion Depth:"),
                                      text("Memory Usage:"),
                                      text("Run Time:"),
                                  }),
                                  vbox({
                                      text(metrics["Stability"]),
                                      text(metrics["Comparisons"]),
                                      text(metrics["Swaps"]),
                                      text(metrics["FunctionCall"]),
                                      text(metrics["LoopIterations"]),
                                      text(metrics["Depth"]),
                                      text(metrics["Memory"]),
                                      text(metrics["RunTime"]),
                                  })})})) |
               flex;
    });

    // 底部按钮和设置
    // Run 按钮
    auto run_button = Button("Run", [&] {
        // handle input
        data.clear();

        if (array_input.empty()) {
            algorithm_Info_text = "Please enter a valid array";
        } else {
            std::stringstream ss(array_input);
            int value;
            while (ss >> value) {
                if (value > 0) {  // 过滤负数
                    data.push_back(value);
                }
            }

            if (!sort_running.load()) {
                sort_running.store(true);
                std::thread sort_thread([&]() {
                    Testmachine.ManualTest(screen);
                    sort_running.store(false);
                });
                sort_thread.detach();
            }
        }
    });

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
            separator() | size(HEIGHT, EQUAL, 3) | center,
            exit_button_renderer->Render(),
        });
    });

    // 设置项
    auto graphics_toggle =
        Toggle(&graphics_toggle_options, &graphics_selection);
    auto speed_toggle = Toggle(&speed_options, &playback_speed);
    auto mode_toggle = Toggle(&mode_toggle_options, &mode_selection);
    auto order_toggle = Toggle(&order_toggle_options, &order_selection);

    auto settings_container = Container::Vertical({
        graphics_toggle,
        speed_toggle,
        mode_toggle,
        order_toggle,
    });

    auto settings_renderer = Renderer(settings_container, [&] {
        return window(
            text(" Settings "),
            hbox({
                vbox({
                    hbox({text("Graphics: "),
                          text(graphics_toggle_options[graphics_selection])}),
                    hbox({text("Playback Speed: "),
                          text(speed_options[playback_speed])}),
                    hbox({text("Mode: "),
                          text(mode_toggle_options[mode_selection])}),
                    hbox({text("Order: "),
                          text(order_toggle_options[order_selection])}),
                }) | size(WIDTH, GREATER_THAN, 30),
                vbox({
                    graphics_toggle->Render(),
                    speed_toggle->Render(),
                    mode_toggle->Render(),
                    order_toggle->Render(),
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
    if (sort_thread_ptr && sort_thread_ptr->joinable()) {
        sort_thread_ptr->join();
    }
}