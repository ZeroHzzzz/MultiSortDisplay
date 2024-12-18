#ifndef MENU_HPP
#define MENU_HPP

#include <ftxui/component/component.hpp>  // For Menu, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <iostream>
#include <string>
#include <vector>

using namespace ftxui;

// 运行菜单的实现
void RunMenu() {
    auto screen = ScreenInteractive::Fullscreen();

    // 页面选项
    std::vector<std::string> main_pages = {"Home Page", "Sorting Algorithms",
                                           "Settings", "Exit"};
    std::vector<std::string> sorting_submenu = {
        "Bubble Sort", "Quick Sort", "Merge Sort", "Back to Main Menu"};

    int current_page = 0;            // 当前选中的页面索引
    int sorting_page_selection = 0;  // 当前排序算法子菜单的选项索引

    // 主菜单
    auto menu = Menu(&main_pages, &current_page);

    // 排序算法子菜单
    auto sorting_menu = Menu(&sorting_submenu, &sorting_page_selection);

    // 定义各个页面的 Renderer
    auto home_page = Renderer([] {
        return vbox({
            text("=== Home Page ===") | bold | center,
            text("Welcome to the Sorting Algorithm Visualizer!") | center,
        });
    });

    auto sorting_page = Renderer([&] {
        return vbox({
            text("=== Sorting Algorithms ===") | bold | center,
            text("Here you can visualize sorting algorithms.") | center,
            sorting_menu->Render()  // 渲染排序算法子菜单
        });
    });

    auto settings_page = Renderer([] {
        return vbox({
            text("=== Settings ===") | bold | center,
            text("Adjust your preferences here.") | center,
        });
    });

    auto exit_page = Renderer([&] {
        return vbox({
            text("=== Exit ===") | bold | center,
            text("Press Enter to exit.") | center,
        });
    });

    // 主 Renderer，根据 current_page 渲染不同页面
    auto main_renderer = Renderer(menu, [&] {
        if (current_page == 0)
            return home_page->Render();
        else if (current_page == 1)
            return sorting_page->Render();
        else if (current_page == 2)
            return settings_page->Render();
        else if (current_page == 3)
            return exit_page->Render();
        return text("Unknown Page") | center;
    });

    // 整体布局
    auto layout = Container::Horizontal({menu, main_renderer});

    // 事件循环
    screen.Loop(Renderer(layout, [&] {
        return hbox({
            vbox({
                text("=== Navigation Menu ===") | bold | center,
                menu->Render(),  // 渲染菜单
            }) | border,
            separator(),
            main_renderer->Render() | flex  // 渲染当前页面
        });
    }));
}

#endif  // MENU_HPP
