#ifndef SORT_FACTORY_HPP
#define SORT_FACTORY_HPP

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "sortAlgorithm/Sort.hpp"  // 假设 Sort<T> 已定义
template <typename T>
class SortFactory {
   public:
    static std::unique_ptr<Sort<T>> create(const std::string& type);
    static void registerType(
        const std::string& name,
        std::function<std::unique_ptr<Sort<T>>()>&& factory);

   private:
    static std::map<std::string, std::function<std::unique_ptr<Sort<T>>()>>
        factoryMap;
};

// 模板方法的实现必须在头文件中
template <typename T>
std::map<std::string, std::function<std::unique_ptr<Sort<T>>()>>
    SortFactory<T>::factoryMap;

template <typename T>
std::unique_ptr<Sort<T>> SortFactory<T>::create(const std::string& type) {
    auto it = factoryMap.find(type);
    if (it != factoryMap.end()) {
        return it->second();
    }
    throw std::runtime_error("Sort type not registered");
}

template <typename T>
void SortFactory<T>::registerType(
    const std::string& name,
    std::function<std::unique_ptr<Sort<T>>()>&& factory) {
    factoryMap[name] = std::move(factory);
}

#endif  // SORT_FACTORY_HPP
