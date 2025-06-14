//
// Created by eriche on 2025/6/13.
//

#pragma once

#include "OrderedSet.h"
#include <variant>
#include <type_traits>

template<typename T, typename Compare = std::less<T>>
class OrderedCollection {
private:
    std::variant<std::vector<T>, OrderedSet<T, Compare>> real;
    using vector_iterator = typename std::vector<T>::iterator;
    using set_iterator = typename OrderedSet<T, Compare>::iterator;

public:

    OrderedCollection() : real(std::vector<T>()) {}

    class iterator {
    private:
        std::variant<vector_iterator, set_iterator> inner_iterator;
    public:
        iterator() = delete;

        explicit iterator(vector_iterator it) : inner_iterator(std::move(it)) {}

        explicit iterator(set_iterator it) : inner_iterator(std::move(it)) {}

        // 解引用返回原始值（非 Element 结构体）
        const T &operator*() const {
            if (std::holds_alternative<vector_iterator>(inner_iterator)) {
                return std::get<vector_iterator>(inner_iterator).operator*();
            } else {
                return std::get<set_iterator>(inner_iterator).operator*();
            }
        };

        const T *operator->() const {
            if (std::holds_alternative<vector_iterator>(inner_iterator)) {
                return std::get<vector_iterator>(inner_iterator).operator->();
            } else {
                return std::get<set_iterator>(inner_iterator).operator->();
            }
        };

        // 迭代器移动操作
        iterator &operator++() {
            if (std::holds_alternative<vector_iterator>(inner_iterator)) {
                ++std::get<vector_iterator>(inner_iterator);
            } else {
                ++std::get<set_iterator>(inner_iterator);
            }
            return *this;
        };

        iterator operator++(int) {
            iterator tmp = *this;
            if (std::holds_alternative<vector_iterator>(inner_iterator)) {
                ++std::get<vector_iterator>(inner_iterator);
            } else {
                ++std::get<set_iterator>(inner_iterator);
            }
            return tmp;
        };

        bool operator!=(const iterator &other) const {
            return inner_iterator != other.inner_iterator;
        };

        bool operator==(const iterator &other) const {
            return inner_iterator == other.inner_iterator;
        };
    };


    iterator begin() {
        if (std::holds_alternative<std::vector<T>>(real)) {
            return iterator(std::get<std::vector<T>>(real).begin());
        } else {
            return iterator(std::get<OrderedSet<T, Compare>>(real).begin());
        }
    };

    iterator end() {
        if (std::holds_alternative<std::vector<T>>(real)) {
            return iterator(std::get<std::vector<T>>(real).end());
        } else {
            return iterator(std::get<OrderedSet<T, Compare>>(real).end());
        }
    };

    void add(const T &item) {
        if (std::holds_alternative<std::vector<T>>(real)) {
            std::vector<T> &v = std::get<std::vector<T>>(real);
            v.emplace_back(item);
        } else {
            OrderedSet<T, Compare> &set = std::get<OrderedSet<T, Compare>>(real);
            set.insert(item);
        }
    }

    void remove(const T &t) {
        if (std::holds_alternative<std::vector<T>>(real)) {
            std::vector<T> &v = std::get<std::vector<T>>(real);
            auto &iterator = std::find(v.begin(), v.end(), t);
            if (iterator != v.end()) {
                v.erase(iterator);
            }
        } else {
            OrderedSet<T, Compare> &set = std::get<OrderedSet<T, Compare>>(real);
            set.erase(t);
        }
    }
};


template<typename Value, typename T1, typename T2>
class CollectionVariant2 {
private:
    std::variant<T1, T2> real;
    using t1_iterator = typename T1::iterator;
    using t2_iterator = typename T2::iterator;

public:

    explicit CollectionVariant2(std::variant<T1, T2> real) : real((std::move(real))) {}

    class iterator {
    private:
        std::variant<t1_iterator, t2_iterator> inner_iterator;
    public:
        iterator() = delete;

        explicit iterator(t1_iterator it) : inner_iterator(std::move(it)) {}

        explicit iterator(t2_iterator it) : inner_iterator(std::move(it)) {}

        // 解引用返回原始值（非 Element 结构体）
        const Value &operator*() const {
            if (std::holds_alternative<t1_iterator>(inner_iterator)) {
                return std::get<t1_iterator>(inner_iterator).operator*();
            } else {
                return std::get<t2_iterator>(inner_iterator).operator*();
            }
        };

        const Value *operator->() const {
            if (std::holds_alternative<t1_iterator>(inner_iterator)) {
                return std::get<t1_iterator>(inner_iterator).operator->();
            } else {
                return std::get<t2_iterator>(inner_iterator).operator->();
            }
        };

        // 迭代器移动操作
        iterator &operator++() {
            if (std::holds_alternative<t1_iterator>(inner_iterator)) {
                ++std::get<t1_iterator>(inner_iterator);
            } else {
                ++std::get<t2_iterator>(inner_iterator);
            }
            return *this;
        };

        iterator operator++(int) {
            iterator tmp = *this;
            if (std::holds_alternative<t1_iterator>(inner_iterator)) {
                ++std::get<t1_iterator>(inner_iterator);
            } else {
                ++std::get<t2_iterator>(inner_iterator);
            }
            return tmp;
        };

        bool operator!=(const iterator &other) const {
            return inner_iterator != other.inner_iterator;
        };

        bool operator==(const iterator &other) const {
            return inner_iterator == other.inner_iterator;
        };
    };


    iterator begin() {
        if (std::holds_alternative<T1>(real)) {
            return iterator(std::get<T1>(real).begin());
        } else {
            return iterator(std::get<T2>(real).begin());
        }
    };

    iterator end() {
        if (std::holds_alternative<T1>(real)) {
            return iterator(std::get<T1>(real).end());
        } else {
            return iterator(std::get<T2>(real).end());
        }
    };
};


//template<typename Value, typename... Containers>
//class CollectionVariant {
//private:
//    std::variant<Containers...> real;  // 存储任意类型的容器
//
//    // 提取所有容器的迭代器类型
//    template<typename T>
//    using iterator_type = typename T::iterator;
//    template<typename T>
//    using const_iterator_type = typename T::const_iterator;
//
//public:
//
//    explicit CollectionVariant(std::variant<Containers...> real) : real(std::move(real)) {}
//
//    // 迭代器类定义
//    class iterator;
//    class const_iterator;
//
//    iterator begin();
//
//    iterator end();
//
//    const_iterator cbegin();
//
//    const_iterator cend();
//};
//
//template<typename Value, typename... Containers>
//class CollectionVariant<Value, Containers...>::iterator {
//private:
//    using IterVariant = std::variant<iterator_type<Containers>...>;  // 迭代器变体
//    IterVariant iter;
//
//public:
//    explicit iterator(IterVariant it) : iter(std::move(it)) {}
//
//    // 解引用操作（返回Value类型）
//    const Value &operator*() const {
//        return std::visit([](auto &&it) -> const Value & {
//            return *it;
//        }, iter);
//    }
//
//    // 成员访问操作
//    const Value *operator->() const {
//        return std::visit([](auto &&it) -> const Value * {
//            return &(*it);
//        }, iter);
//    }
//
//    // 前缀自增
//    iterator &operator++() {
//        std::visit([](auto &&it) { ++it; }, iter);
//        return *this;
//    }
//
//    // 后缀自增
//    iterator operator++(int) {
//        iterator tmp = *this;
//        std::visit([](auto &&it) { it++; }, iter);
//        return tmp;
//    }
//
//    // 比较操作
//    bool operator==(const iterator &other) const {
//        return iter == other.iter;
//    }
//
//    bool operator!=(const iterator &other) const {
//        return !(*this == other);
//    }
//};

//template<typename Value, typename... Containers>
//class CollectionVariant<Value, Containers...>::const_iterator {
//private:
//    using IterVariant = std::variant<const_iterator_type<Containers>...>;  // 迭代器变体
//    IterVariant iter;
//
//public:
//    explicit const_iterator(IterVariant it) : iter(std::move(it)) {}
//
//    // 解引用操作（返回Value类型）
//    const Value &operator*() const {
//        return std::visit([](auto &&it) -> const Value & {
//            return *it;
//        }, iter);
//    }
//
//    // 成员访问操作
//    const Value *operator->() const {
//        return std::visit([](auto &&it) -> const Value * {
//            return &(*it);
//        }, iter);
//    }
//
//    // 前缀自增
//    const_iterator &operator++() {
//        std::visit([](auto &&it) { ++it; }, iter);
//        return *this;
//    }
//
//    // 后缀自增
//    const_iterator operator++(int) {
//        iterator tmp = *this;
//        std::visit([](auto &&it) { it++; }, iter);
//        return tmp;
//    }
//
//    // 比较操作
//    bool operator==(const const_iterator &other) const {
//        return iter == other.iter;
//    }
//
//    bool operator!=(const const_iterator &other) const {
//        return !(*this == other);
//    }
//};


//template<typename Value, typename... Containers>
//typename CollectionVariant<Value, Containers...>::iterator
//CollectionVariant<Value, Containers...>::begin() {
//    return std::visit([](auto &container) -> iterator {
//        return iterator(container.begin());
//    }, real);
//}
//
//template<typename Value, typename... Containers>
//typename CollectionVariant<Value, Containers...>::iterator
//CollectionVariant<Value, Containers...>::end() {
//    return std::visit([](auto &container) -> iterator {
//        return iterator(container.end());
//    }, real);
//}