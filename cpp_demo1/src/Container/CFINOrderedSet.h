//
// Created by eriche on 2025/6/12.
//

#pragma once

#include <set>
#include <vector>
#include <unordered_map>

/**
 * 基于std::set实现的有序集合：
 * 1. 默认按照 std::less<T> 比较器进行排序。
 * 2. 当对比值相等时，按照插入顺序进行排序。
 */
template<typename T, typename Compare = std::less<T>>
class CFINOrderedSet {
private:
    struct Element {
        mutable T value;
        size_t insertionId;

        Element(T v, size_t id) : value(std::move(v)), insertionId(id) {}
    };

    struct ElementComparator {

    private:
        Compare comp;

    public:
        ElementComparator() = default;

        explicit ElementComparator(Compare comp) : comp(std::move(comp)) {}

        bool operator()(const Element& a, const Element& b) const {
            // 主排序：使用 Compare 比较元素值
            if (comp(a.value, b.value)) return true;
            if (comp(b.value, a.value)) return false;

            // 次排序：值相等时按插入顺序（插入ID小者在前）
            return a.insertionId < b.insertionId;
        }
    };

    using SetType = std::set<Element, ElementComparator>;
    using IteratorType = typename SetType::iterator;
    using ConstIteratorType = typename SetType::const_iterator;


    std::unordered_map<T, IteratorType> lookupMap;
    SetType real;
    size_t insertionIdGenerator = 1;

public:
    template<bool IsConst>
    class IteratorImpl {
    private:
        using IterVariant = std::conditional_t<IsConst, ConstIteratorType, IteratorType>;
        IterVariant iter;
    public:
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using pointer = std::conditional_t<IsConst, const T*, T*>;

        explicit IteratorImpl(IterVariant it) : iter(std::move(it)) {}

        // 解引用返回原始值（非 Element 结构体）
        reference operator*() const {
            return (*iter).value;
        };

        pointer operator->() const {
            return &((*iter).value);
        };

        // 迭代器移动操作
        IteratorImpl& operator++() {
            ++iter;
            return *this;
        };

        IteratorImpl operator++(int) {
            auto tmp = *this;
            iter++;
            return tmp;
        };

        IterVariant base() const { return iter; }

        bool operator!=(const IteratorImpl& other) const { return iter != other.iter; };

        bool operator==(const IteratorImpl& other) const { return iter == other.iter; };
    };

    // 公开迭代器类型别名
    using iterator = IteratorImpl<false>;
    using const_iterator = IteratorImpl<true>;
    using size_type = typename SetType::size_type;

    CFINOrderedSet() = default;

    explicit CFINOrderedSet(Compare compare) : real(ElementComparator(compare)) {}

    std::pair<iterator, bool> insert(const T& t) {
        if (auto it = lookupMap.find(t); it != lookupMap.end()) {
            return std::pair<iterator, bool>(iterator(it->second), false);
        }
        const auto& [it, inserted] = real.insert(Element(t, insertionIdGenerator++));
        if (inserted) {
            lookupMap[t] = it;
        }
        return std::pair<iterator, bool>(iterator(it), inserted);
    }

    std::pair<iterator, bool> insert(T&& t) {
        if (auto it = lookupMap.find(t); it != lookupMap.end()) {
            return std::pair<iterator, bool>(iterator(it->second), false);
        }
        const auto& [it, inserted] = real.insert(Element(std::move(t), insertionIdGenerator++));
        if (inserted) {
            lookupMap[(*it).value] = it;
        }
        return std::pair<iterator, bool>(iterator(it), inserted);
    }

    iterator erase(iterator pos) noexcept {
        lookupMap.erase(*pos);
        return iterator(real.erase(pos.iter));
    }

    iterator erase(const_iterator pos) noexcept {
        lookupMap.erase(*pos);
        return iterator(real.erase(pos.iter));
    }

    iterator erase(const_iterator first, const_iterator last) noexcept {
        auto current = first;
        while (current != last) {
            auto next = std::next(current);
            erase(current); // 调用单元素 erase
            current = next;
        }
        return iterator(current);
    }

    size_type erase(const T& t) {
        if (auto it = lookupMap.find(t); it != lookupMap.end()) {
            real.erase(it->second);
            lookupMap.erase(it);
            return 1;
        }
        return 0;
    }

    iterator find(const T& t) {
        auto map_it = lookupMap.find(t);
        if (map_it != lookupMap.end()) {
            return iterator(map_it->second); // 直接返回迭代器
        }
        return end();
    }

    iterator find(T&& t) {
        auto map_it = lookupMap.find(t);
        if (map_it != lookupMap.end()) {
            return iterator(map_it->second); // 直接返回迭代器
        }
        return end();
    }

    const_iterator find(const T& t) const {
        auto map_it = lookupMap.find(t);
        if (map_it != lookupMap.end()) {
            return iterator(map_it->second); // 直接返回迭代器
        }
        return const_iterator(real.end());
    }

    const_iterator find(T&& t) const {
        if (auto it = lookupMap.find(std::move(t)); it != lookupMap.end()) {
            return const_iterator(it->second);
        }
        return const_iterator(real.end());
    }

    size_type size() const noexcept {
        return real.size();
    }

    bool empty() const noexcept {   // NOLINT
        return real.empty();
    }

    void clear() noexcept {
        real.clear();
        lookupMap.clear();
        insertionIdGenerator = 1;
    }

    iterator begin() {
        return iterator(real.begin());
    }

    iterator end() {
        return iterator(real.end());
    }

    const_iterator begin() const {
        return const_iterator(real.begin());
    }

    const_iterator end() const {
        return const_iterator(real.end());
    }

    const_iterator cbegin() const { return begin(); }

    const_iterator cend() const { return end(); }

};
