//
// Created by eriche on 2025/10/21.
//

#pragma once

#include <set>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stdexcept>
#include <climits>
#include <algorithm>

/**
 * 基于std::set实现的有序映射：
 * 1. 默认按照 std::less<Key> 比较器对键进行排序。
 * 2. 当对比值相等时，按照插入顺序进行排序。
 * 3. 插入已存在的键时，会替换对应的值，但保持原有的插入顺序位置。
 */
template<typename Key, typename Value, typename Compare = std::less<Key>>
class CFINOrderedMap {
private:
    struct Element {
        mutable Key key;
        mutable Value value;
        size_t insertionId;

        Element(Key k, Value v, size_t id)
                : key(std::move(k)), value(std::move(v)), insertionId(id) {}
    };

    struct ElementComparator {
    private:
        Compare comp;

    public:
        ElementComparator() = default;

        explicit ElementComparator(Compare comp) : comp(std::move(comp)) {}

        bool operator()(const Element& a, const Element& b) const {
            // 主排序：使用 Compare 比较键
            if (comp(a.key, b.key)) return true;
            if (comp(b.key, a.key)) return false;

            // 次排序：键相等时按插入顺序（插入ID小者在前）
            return a.insertionId < b.insertionId;
        }
    };

    using SetType = std::set<Element, ElementComparator>;
    using IteratorType = typename SetType::iterator;
    using ConstIteratorType = typename SetType::const_iterator;

    std::unordered_map<Key, IteratorType> lookupMap;
    SetType real;
    size_t insertionIdGenerator = 1;

public:
    template<bool IsConst>
    class IteratorImpl {
    private:
        using IterVariant = std::conditional_t<IsConst, ConstIteratorType, IteratorType>;
        IterVariant iter;

        // 键值对代理类，直接引用原始数据，避免复制
        struct KeyValueProxy {
            using key_type = Key;
            using mapped_type = Value;
            using key_reference = std::conditional_t<IsConst, const Key&, Key&>;
            using value_reference = std::conditional_t<IsConst, const Value&, Value&>;

            key_reference first;
            value_reference second;

            // 直接引用，不复制数据
            KeyValueProxy(IterVariant it) 
                : first((*it).key), second((*it).value) {}
        };

        // 代理指针类，用于支持 -> 操作符的链式调用
        struct ArrowProxy {
            using proxy_type = KeyValueProxy;
            mutable proxy_type proxy;

            explicit ArrowProxy(IterVariant it) : proxy(it) {}

            proxy_type* operator->() { return &proxy; }
        };

    public:
        using value_type = std::pair<const Key, Value>;
        using reference = KeyValueProxy;
        using pointer = ArrowProxy;

        explicit IteratorImpl(IterVariant it) : iter(std::move(it)) {}

        // 解引用返回键值对代理 - 不复制数据
        reference operator*() const {
            return KeyValueProxy(iter);
        }

        // 返回代理指针，支持 -> 操作符 - 不复制数据
        pointer operator->() const {
            return ArrowProxy(iter);
        }

        // 迭代器移动操作
        IteratorImpl& operator++() {
            ++iter;
            return *this;
        }

        IteratorImpl operator++(int) {
            auto tmp = *this;
            ++iter;
            return tmp;
        }

        // 双向迭代器支持
        IteratorImpl& operator--() {
            --iter;
            return *this;
        }

        IteratorImpl operator--(int) {
            auto tmp = *this;
            --iter;
            return tmp;
        }

        IterVariant base() const { return iter; }

        bool operator!=(const IteratorImpl& other) const { return iter != other.iter; }
        bool operator==(const IteratorImpl& other) const { return iter == other.iter; }
    };

    // 公开迭代器类型别名
    using iterator = IteratorImpl<false>;
    using const_iterator = IteratorImpl<true>;
    using size_type = typename SetType::size_type;
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const Key, Value>;

    CFINOrderedMap() = default;

    explicit CFINOrderedMap(Compare compare) : real(ElementComparator(compare)) {}

    // 插入键值对 - 如果键已存在，则替换值
    std::pair<iterator, bool> insert(const Key& key, const Value& value) {
        return insertImpl(key, value);
    }

    std::pair<iterator, bool> insert(Key&& key, Value&& value) {
        return insertImpl(std::move(key), std::move(value));
    }

    // 插入pair的版本 - 如果键已存在，则替换值
    std::pair<iterator, bool> insert(const value_type& pair) {
        return insert(pair.first, pair.second);
    }

    std::pair<iterator, bool> insert(value_type&& pair) {
        // 避免const_cast，直接使用pair的成员
        Key key = std::move(const_cast<Key&>(pair.first));
        return insertImpl(std::move(key), std::move(pair.second));
    }

    // emplace 方法 - 如果键已存在，则替换值
    template<typename K, typename V>
    std::pair<iterator, bool> emplace(K&& key, V&& value) {
        return insertImpl(std::forward<K>(key), std::forward<V>(value));
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
        // 构造临时的pair来获取key和value
        auto temp_pair = value_type(std::forward<Args>(args)...);
        Key key = std::move(const_cast<Key&>(temp_pair.first));
        return insertImpl(std::move(key), std::move(temp_pair.second));
    }

    // try_emplace 方法
    template<typename... Args>
    std::pair<iterator, bool> try_emplace(const Key& key, Args&&... args) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            return {iterator(it->second), false};
        }
        return insertImpl(key, Value(std::forward<Args>(args)...));
    }

    template<typename... Args>
    std::pair<iterator, bool> try_emplace(Key&& key, Args&&... args) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            return {iterator(it->second), false};
        }
        return insertImpl(std::move(key), Value(std::forward<Args>(args)...));
    }

    // insert_or_assign 方法
    template<typename V>
    std::pair<iterator, bool> insert_or_assign(const Key& key, V&& value) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            it->second->value = std::forward<V>(value);
            return {iterator(it->second), false};
        }
        return insertImpl(key, std::forward<V>(value));
    }

    template<typename V>
    std::pair<iterator, bool> insert_or_assign(Key&& key, V&& value) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            it->second->value = std::forward<V>(value);
            return {iterator(it->second), false};
        }
        return insertImpl(std::move(key), std::forward<V>(value));
    }

    // 插入或赋值（类似std::map的operator[]）
    Value& operator[](const Key& key) {
        auto it = lookupMap.find(key);
        if (it != lookupMap.end()) {
            return it->second->value;
        }

        // 键不存在，插入默认构造的值
        auto result = insertImpl(key, Value{});
        return result.first->second;
    }

    Value& operator[](Key&& key) {
        auto it = lookupMap.find(key);
        if (it != lookupMap.end()) {
            return it->second->value;
        }

        // 键不存在，插入默认构造的值，使用移动语义
        auto result = insertImpl(std::move(key), Value{});
        return result.first->second;
    }

    // 删除操作
    iterator erase(iterator pos) {
        if (pos == end()) return end();

        Key key = pos->first;  // 保存key用于查找
        auto next_iter = pos.base();
        ++next_iter;
        real.erase(pos.base());
        lookupMap.erase(key);
        return iterator(next_iter);
    }

    iterator erase(const_iterator pos) {
        if (pos == cend()) return end();

        Key key = pos->first;  // 保存key用于查找
        auto next_iter = pos.base();
        ++next_iter;
        real.erase(pos.base());
        lookupMap.erase(key);
        return iterator(next_iter);
    }

    // 批量删除优化
    iterator erase(const_iterator first, const_iterator last) {
        if (first == last) return iterator(last);

        // 批量从lookupMap中删除
        for (auto it = first; it != last; ++it) {
            lookupMap.erase(it->first);
        }

        // 一次性从set中删除区间
        return iterator(real.erase(first.base(), last.base()));
    }

    size_type erase(const Key& key) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            real.erase(it->second);
            lookupMap.erase(it);
            return 1;
        }
        return 0;
    }

    // 查找操作
    iterator find(const Key& key) {
        auto map_it = lookupMap.find(key);
        return map_it != lookupMap.end() ? iterator(map_it->second) : end();
    }

    const_iterator find(const Key& key) const {
        auto map_it = lookupMap.find(key);
        return map_it != lookupMap.end() ? const_iterator(map_it->second) : end();
    }

    // 访问元素（带边界检查）
    Value& at(const Key& key) {
        auto it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found in CFINOrderedMap");
        }
        return it->second;
    }

    const Value& at(const Key& key) const {
        auto it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found in CFINOrderedMap");
        }
        return it->second;
    }

    // 容量相关
    size_type size() const noexcept {
        return real.size();
    }

    [[nodiscard]] bool empty() const noexcept {
        return real.empty();
    }

    void clear() noexcept {
        real.clear();
        lookupMap.clear();
        insertionIdGenerator = 1;
    }

    // 预留容量以优化性能
    void reserve(size_type count) {
        lookupMap.reserve(count);
    }

    // 迭代器
    iterator begin() noexcept { return iterator(real.begin()); }
    iterator end() noexcept { return iterator(real.end()); }
    const_iterator begin() const noexcept { return const_iterator(real.begin()); }
    const_iterator end() const noexcept { return const_iterator(real.end()); }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    // 判断键是否存在
    bool contains(const Key& key) const {
        return lookupMap.find(key) != lookupMap.end();
    }

    // 获取元素数量
    size_type count(const Key& key) const {
        return contains(key) ? 1 : 0;
    }

    // 边界查找方法
    iterator lower_bound(const Key& key) {
        Element dummy{key, Value{}, 0};
        auto it = real.lower_bound(dummy);
        return iterator(it);
    }

    const_iterator lower_bound(const Key& key) const {
        Element dummy{key, Value{}, 0};
        auto it = real.lower_bound(dummy);
        return const_iterator(it);
    }

    iterator upper_bound(const Key& key) {
        Element dummy{key, Value{}, SIZE_MAX};  // 使用最大插入ID确保在所有相同key之后
        auto it = real.upper_bound(dummy);
        return iterator(it);
    }

    const_iterator upper_bound(const Key& key) const {
        Element dummy{key, Value{}, SIZE_MAX};
        auto it = real.upper_bound(dummy);
        return const_iterator(it);
    }

    std::pair<iterator, iterator> equal_range(const Key& key) {
        return {lower_bound(key), upper_bound(key)};
    }

    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
        return {lower_bound(key), upper_bound(key)};
    }

    // 交换操作
    void swap(CFINOrderedMap& other) noexcept {
        using std::swap;
        swap(lookupMap, other.lookupMap);
        swap(real, other.real);
        swap(insertionIdGenerator, other.insertionIdGenerator);
    }

    // 获取比较器
    Compare key_comp() const {
        return real.key_comp().comp;
    }

    // 最大容量
    size_type max_size() const noexcept {
        return real.max_size();
    }

private:
    // 统一的插入实现 - 支持值替换
    template<typename K, typename V>
    std::pair<iterator, bool> insertImpl(K&& key, V&& value) {
        if (auto it = lookupMap.find(key); it != lookupMap.end()) {
            // 键已存在，替换值但保持原有的插入顺序
            it->second->value = std::forward<V>(value);
            return {iterator(it->second), false};
        }

        auto [it, inserted] = real.emplace(
                std::forward<K>(key), std::forward<V>(value), insertionIdGenerator++
        );

        if (inserted) {
            lookupMap.try_emplace(it->key, it);
        }

        return {iterator(it), inserted};
    }
};

// 全局 swap 函数
template<typename Key, typename Value, typename Compare>
void swap(CFINOrderedMap<Key, Value, Compare>& lhs, CFINOrderedMap<Key, Value, Compare>& rhs) noexcept {
    lhs.swap(rhs);
}

// 比较操作符
template<typename Key, typename Value, typename Compare>
bool operator==(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename Key, typename Value, typename Compare>
bool operator!=(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    return !(lhs == rhs);
}

template<typename Key, typename Value, typename Compare>
bool operator<(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename Key, typename Value, typename Compare>
bool operator<=(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    return !(rhs < lhs);
}

template<typename Key, typename Value, typename Compare>
bool operator>(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    return rhs < lhs;
}

template<typename Key, typename Value, typename Compare>
bool operator>=(const CFINOrderedMap<Key, Value, Compare>& lhs, const CFINOrderedMap<Key, Value, Compare>& rhs) {
    return !(lhs < rhs);
}