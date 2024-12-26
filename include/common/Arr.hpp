#pragma once
#include <type_traits>

template <typename T>
struct Arr {
    T value;
    int index;

    // 默认构造函数
    Arr() : value(T()), index(0) {}

    // 带参数的构造函数
    Arr(T value, int index) : value(value), index(index) {}

    bool operator>(const Arr& other) const { return this->value > other.value; }
    bool operator<(const Arr& other) const { return this->value < other.value; }
    bool operator==(const Arr& other) const {
        return this->value == other.value;
    }

    // 重载与基础类型（如 int, float 等）的比较
    template <typename U,
              typename = typename std::enable_if<
                  !std::is_same<U, Arr<T>>::value>::type>
    bool operator>(const U& other) const {
        return this->value > other;
    }

    template <typename U,
              typename = typename std::enable_if<
                  !std::is_same<U, Arr<T>>::value>::type>
    bool operator<(const U& other) const {
        return this->value < other;
    }

    template <typename U,
              typename = typename std::enable_if<
                  !std::is_same<U, Arr<T>>::value>::type>
    bool operator==(const U& other) const {
        return this->value == other;
    }

    // 重载 <= 和 >= 运算符
    bool operator<=(const Arr& other) const { return !(*this > other); }
    bool operator>=(const Arr& other) const { return !(*this < other); }

    template <typename U,
              typename = typename std::enable_if<
                  !std::is_same<U, Arr<T>>::value>::type>
    bool operator<=(const U& other) const {
        return !(*this > other);
    }

    template <typename U,
              typename = typename std::enable_if<
                  !std::is_same<U, Arr<T>>::value>::type>
    bool operator>=(const U& other) const {
        return !(*this < other);
    }
};
