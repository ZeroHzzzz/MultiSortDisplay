// Windows.cpp
#include "windows/windows.hpp"

void Windows::Show() {
    // 左侧 Algorithm List
    auto algorithm_list_container = Container::Vertical({});
    for (const auto& name : algorithms) {
        algorithm_list_container->Add(
            Button(name, [&] { algorithm_selected = name; }));
    }

    auto algorithm_list = Renderer(algorithm_list_container, [&] {
        return window(text(" Algorithm List "),
                      algorithm_list_container->Render()) |
               size(WIDTH, EQUAL, 20);
    });

    // 中间 算法过程输出
    auto process_output_renderer = Renderer([&] {
        std::vector<Element> bars;
        int max_height = 10;
        if (!data.empty()) {
            int max_value = *std::max_element(data.begin(), data.end());
            for (int& value : data) {
                value = max_value > max_height ? value * max_height / max_value
                                               : value;
            }
        }
        for (int value : data) {
            bars.push_back(hbox({
                text(std::to_string(value)),
                text(std::string(value, '#')),
            }));
        }
        return window(text(" Algorithm Process Output "),
                      vbox(std::move(bars))) |
               flex;
    });

    // 右上角 需要排序的数组输入
    auto array_input_component = Input(&array_input, "Enter array here...");
    auto array_input_renderer = Renderer(array_input_component, [&] {
        return window(text(" Array Input "), array_input_component->Render()) |
               size(HEIGHT, EQUAL, 8);
    });

    // 右中 指标输出
    auto metrics_output_renderer = Renderer([&] {
        return window(text(" Metrics Output "), vbox({
                                                    text("Comparisons: 0"),
                                                    text("Swaps: 0"),
                                                })) |
               flex;
    });

    // 底部按钮和设置
    auto run_button = Button("Run", [&] { /* Your sorting execution logic */ });
    auto exit_button = Button("Exit", [&] { this->screen.Exit(); });

    auto buttons_renderer = Renderer(Container::Horizontal({
                                         run_button,
                                         exit_button,
                                     }),
                                     [&] {
                                         return hbox({
                                             run_button->Render(),
                                             separator(),
                                             exit_button->Render(),
                                         });
                                     });

    // 设置项
    auto graphics_toggle =
        Toggle(&graphics_toggle_options, &graphics_selection);
    auto speed_toggle = Toggle(&speed_options, &playback_speed);
    auto mode_toggle = Toggle(&mode_toggle_options, &mode_selection);

    auto settings_renderer = Renderer(
        Container::Vertical({
            graphics_toggle,
            speed_toggle,
            mode_toggle,
        }),
        [&] {
            return window(text(" Settings "), hbox({
                                                  vbox({
                                                      text("Graphics: "),
                                                      text("Playback Speed: "),
                                                      text("Mode: "),
                                                  }),
                                                  separator(),
                                                  vbox({
                                                      graphics_toggle->Render(),
                                                      speed_toggle->Render(),
                                                      mode_toggle->Render(),
                                                  }),
                                              }));
        });

    // 主布局
    auto main_container = Container::Vertical({
        algorithm_list_container,
        array_input_component,
        run_button,
        exit_button,
        graphics_toggle,
        speed_toggle,
        mode_toggle,
    });

    auto main_renderer = Renderer(main_container, [&] {
        return vbox({
            hbox({
                algorithm_list->Render(),
                process_output_renderer->Render(),
                vbox({
                    array_input_renderer->Render(),
                    metrics_output_renderer->Render(),
                }),
            }),
            buttons_renderer->Render(),
        });
    });

    // 启动界面
    screen.Loop(main_renderer);
}

void Windows::refresh() {
    screen.Post([&] {});
}

void Windows::update(std::vector<int>& update_vector) {
    data = update_vector;
    refresh();
}
