//
// Created by eriche on 2025/6/12.
//

#pragma once

#include <set>
#include <functional>
#include <unordered_map>


/**
 * 基于std::set实现的有序集合：
 * 1. 默认按照 std::less<T> 比较器进行排序。
 * 2. 当元素值相等时，按照插入顺序进行排序。
 */
template<typename T, typename Compare = std::less<T>>
class CFINOrderedSet {
private:
    struct ElementComparator {
        mutable Compare comp;
        mutable std::function<size_t(const T& item)> insertIdGetter;

        bool operator()(const T& a, const T& b) const {
            if (comp(a, b)) { return true; }
            if (comp(b, a)) { return false; }
            // 次排序：值相等时按插入顺序（插入ID小者在前）
            bool result = insertIdGetter(a) < insertIdGetter(b);
            return result;
        }

        ElementComparator() = delete;

        ElementComparator(Compare comp, std::function<size_t(const T& item)> func) : comp(std::move(comp)), insertIdGetter(std::move(func)) {}

    };

    size_t m_idGenerator = 0;                       // 插入ID计数器
    std::unordered_map<T, size_t> m_insertId;
    std::set<T, ElementComparator> m_data;

public:
    // 类型别名
    using iterator = typename std::set<T, ElementComparator>::iterator;
    using const_iterator = typename std::set<T, ElementComparator>::const_iterator;
    using size_type = typename std::set<T, ElementComparator>::size_type;

    CFINOrderedSet() :
            m_idGenerator(0),
            m_insertId(),
            m_data(ElementComparator(Compare(), [this](const T& item) -> size_t {
                auto it = this->m_insertId.find(item);
                if (it == this->m_insertId.end()) {
                    return 0;
                }
                return it->second;
            })) {
//        m_data = std::set<T, ElementComparator>(ElementComparator(Compare(), [this](const T& item) -> size_t {
//            int a = 10;
//            auto it = this->m_insertId.find(item);
//            if (it == this->m_insertId.end()) {
//                return 0;
//            }
//            return it->second;
//        }));
    }

    explicit CFINOrderedSet(Compare compare) :
            m_idGenerator(0),
            m_insertId(),
            m_data(ElementComparator(compare, [this](const T& item) -> size_t {
                int a = 10;
                auto it = this->m_insertId.find(item);
                if (it == this->m_insertId.end()) {
                    return 0;
                }
            })) {
//        std::unordered_map<T, size_t>& insertId = m_insertId;
//        m_data = std::set<T, ElementComparator>(ElementComparator(compare, [&insertId](const T& item) -> size_t {
//            int a = 10;
//            auto it = insertId.find(item);
//            if (it == insertId.end()) {
//                return 0;
//            }
//            return it->second;
//            return 0;
//        }));
    }

    std::pair<iterator, bool> insert(const T& t) {
        if (m_insertId.find(t) == m_insertId.end()) {
            m_insertId[t] = ++m_idGenerator;
        }
        return m_data.insert(t);
    }

    std::pair<iterator, bool> insert(T&& t) {
        if (m_insertId.find(t) == m_insertId.end()) {
            m_insertId[t] = ++m_idGenerator;
        }
        return m_data.insert(std::move(t));
    }

    iterator erase(iterator pos) noexcept {
        auto& temp = *pos;
        const iterator& it = m_data.erase(pos);
        m_insertId.erase(temp);
        return it;
    }

    size_type erase(const T& t) {
        size_type size = m_data.erase(t);
        m_insertId.erase(t);
        return size;
    }

    iterator find(const T& t) {
        return m_data.find(t);
    }

    iterator find(T&& t) {
        return m_data.find(std::move(t));
    }

    const_iterator find(const T& t) const {
        return m_data.find(t);
    }

    const_iterator find(T&& t) const {
        return m_data.find(std::move(t));
    }

    size_type size() const { return m_data.size(); }

    bool empty() const { return m_data.empty(); }

    void clear() { m_data.clear(); }

    iterator begin() { return m_data.begin(); }

    iterator end() { return m_data.end(); }

    const_iterator cbegin() const { return m_data.cbegin(); }

    const_iterator cend() const { return m_data.cend(); }
};
