#pragma once

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "sortAlgorithm/Sort.hpp"  // 假设 Sort<T> 是排序算法基类

/**
 * @brief 模板化的排序算法工厂类
 * @tparam T 数据类型
 */
template <typename T>
class SortFactory {
   public:
    /**
     * @brief 动态创建排序算法实例
     * @param type 排序算法类型名称
     * @param input 待排序的数据容器
     * @param screen 图形界面屏幕
     * @param speed 排序速度
     * @param GUI 是否启用图形界面
     * @return 返回创建的排序算法实例
     */
    static std::unique_ptr<Sort<T>> create(const std::string& type,
                                           std::vector<T>& input,
                                           ftxui::ScreenInteractive& screen,
                                           size_t speed,
                                           bool GUI);

    /**
     * @brief 注册排序算法类型及其构造逻辑
     * @param name 排序算法类型名称
     * @param factory 用于创建排序算法实例的函数对象
     */
    static void registerType(
        const std::string& name,
        std::function<std::unique_ptr<
            Sort<T>>(std::vector<T>&, ftxui::ScreenInteractive&, size_t, bool)>
            factory);

   private:
    // 保存排序算法类型名称和其对应的构造逻辑
    static std::map<
        std::string,
        std::function<std::unique_ptr<
            Sort<T>>(std::vector<T>&, ftxui::ScreenInteractive&, size_t, bool)>>
        factoryMap;
};

// 静态成员变量定义
template <typename T>
std::map<std::string,
         std::function<std::unique_ptr<Sort<
             T>>(std::vector<T>&, ftxui::ScreenInteractive&, size_t, bool)>>
    SortFactory<T>::factoryMap;

// 实现 create 方法
template <typename T>
std::unique_ptr<Sort<T>> SortFactory<T>::create(
    const std::string& type,
    std::vector<T>& input,
    ftxui::ScreenInteractive& screen,
    size_t speed,
    bool GUI) {
    auto it = factoryMap.find(type);
    if (it != factoryMap.end()) {
        return it->second(input, screen, speed, GUI);  // 调用注册的构造逻辑
    }
    throw std::runtime_error("Sort type not registered");
}

// 实现 registerType 方法
template <typename T>
void SortFactory<T>::registerType(
    const std::string& name,
    std::function<std::unique_ptr<
        Sort<T>>(std::vector<T>&, ftxui::ScreenInteractive&, size_t, bool)>
        factory) {
    factoryMap[name] = std::move(factory);
}
