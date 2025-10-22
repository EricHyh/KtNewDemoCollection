//
// Created by eriche on 2025/6/13.
//

#pragma once

#include <variant>
#include <type_traits>

/**
 * 容器变体类，支持多种容器类型的统一迭代器接口。
 * @tparam T 
 * @tparam Containers 
 */
template<typename T, typename... Containers>
class CFINCollectionVariant {
private:
    std::variant<Containers...> real;

    // 萃取容器迭代器类型
    template<typename Container>
    using IteratorType = typename Container::iterator;
    template<typename Container>
    using ConstIteratorType = typename Container::const_iterator;

public:
    explicit CFINCollectionVariant(std::variant<Containers...> real)
            : real(std::move(real)) {}

    // 迭代器类（支持常量与非常量）
    template<bool IsConst>
    class IteratorImpl {
    private:
        using IterVariant = std::variant<std::conditional_t<IsConst, ConstIteratorType<Containers>, IteratorType<Containers>>...>;
        IterVariant iter;

    public:
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using pointer = std::conditional_t<IsConst, const T*, T*>;

        explicit IteratorImpl(IterVariant it) : iter(std::move(it)) {}

        // 解引用
        reference operator*() const {
            return std::visit([](auto&& it) -> reference {
                return *it;
            }, iter);
        }

        // 成员访问
        pointer operator->() const {
            return std::visit([](auto&& it) -> pointer {
                return &(*it);
            }, iter);
        }

        // 自增操作
        IteratorImpl& operator++() {
            std::visit([](auto&& it) { ++it; }, iter);
            return *this;
        }

        IteratorImpl operator++(int) {
            auto tmp = *this;
            std::visit([](auto&& it) { it++; }, iter);
            return tmp;
        }

        bool operator==(const IteratorImpl& other) const {
            return iter == other.iter;
        }

        bool operator!=(const IteratorImpl& other) const {
            return this->iter != other.iter;
        }
    };

    // 公开迭代器类型别名
    using iterator = IteratorImpl<false>;
    using const_iterator = IteratorImpl<true>;
    using size_type = size_t;

    template<typename Visitor,
            typename = std::enable_if_t<std::is_invocable_v<Visitor, std::variant<Containers...>&>>>
    auto visit(Visitor&& visitor) -> decltype(visitor(real)) {
        return visitor(real);
    }

    size_type size() const noexcept {    // NOLINT
        return std::visit([](auto& c) -> size_type {
            return c.size();
        }, real);
    }

    bool empty() const noexcept {   // NOLINT
        return std::visit([](auto& c) -> bool {
            return c.empty();
        }, real);
    }

    void clear() const noexcept {
        return std::visit([](auto& c) -> void {
            c.clear();
        }, real);
    }

    // 迭代器获取函数
    iterator begin() {
        return std::visit([](auto& c) -> iterator {
            return iterator(c.begin());
        }, real);
    }

    iterator end() {
        return std::visit([](auto& c) -> iterator {
            return iterator(c.end());
        }, real);
    }

    const_iterator begin() const {
        return std::visit([](const auto& c) -> const_iterator {
            return const_iterator(c.begin());
        }, real);
    }

    const_iterator end() const {
        return std::visit([](const auto& c) -> const_iterator {
            return const_iterator(c.end());
        }, real);
    }

    // C++11 风格常量迭代器接口
    const_iterator cbegin() const { return begin(); }

    const_iterator cend() const { return end(); }
};
