// 作者: eriche
// 创建时间: 2025-04-13 17:24

#pragma once
#include <stdio.h>
#include <functional>
#include <thread>

class ReferenceData{

public:
    explicit ReferenceData(int data) : m_int_data(data) {
        printf("Default constructor called\n");
    }
    ReferenceData(const ReferenceData& other) : m_int_data(other.m_int_data) {
        printf("Copy constructor called\n");
    }
    ReferenceData(ReferenceData&& other) noexcept : m_int_data(other.m_int_data) {
        printf("Move constructor called\n");
    }

    int GetData() const {
        // 返回成员变量的值
        return m_int_data; // 返回成员变量的值
    }   

private:
    int m_int_data = 0; // 成员变量
    
};


class ReferenceTest2 {
public:
    ReferenceTest2():m_data(ReferenceData(1)){} // 默认构造函数

    ReferenceData GetData() const {
        // 返回成员变量的引用
        return m_data; // 返回成员变量的引用
    }

private:
    ReferenceData m_data; // 成员变量
};


namespace reference {

    inline void TestReference() {
        ReferenceTest2 test;
        ReferenceData data = test.GetData(); 
        printf("ReferenceTest2::GetData() called\n");
    }


    void TestReference(ReferenceData&& data) {
    }

    void TestReference(const ReferenceData& data) {
        auto func = [data = std::move(data)](){
            printf("Value: %d\n", data.GetData()); 
        };
    }

}
