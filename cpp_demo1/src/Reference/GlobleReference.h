// 作者: eriche
// 创建时间: 2025-04-13 13:41

#pragma once

#include <mutex>

class GlobleReference {
public:
    GlobleReference();
};


class CReferenceTest {
public:
    mutable std::mutex m_mutex; // 互斥锁，用于线程安全
    std::string m_name;

    CReferenceTest(std::string name) : m_name(std::move(name)) {} // 构造函数初始化num

    void SetName(const std::string name) {
        std::lock_guard<std::mutex> lock(m_mutex); 
        m_name = std::move(name); // 修改成员变量
    }

    const std::string& GetName() const {
        std::lock_guard<std::mutex> lock(m_mutex); 
        return m_name; // 返回成员变量的值
    }

};
