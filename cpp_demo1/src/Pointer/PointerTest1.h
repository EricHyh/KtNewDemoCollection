// 作者: eriche
// 创建时间: 2025-04-13 20:01

#pragma once

#include <stdio.h>
#include <functional>
#include <thread>
#include <unistd.h>
#include <memory>
#include <mutex>
#include <string>
#include <utility> // std::move
#include <vector> // std::move
#include <algorithm> // std::remove_if



class PointerData {
public:
    explicit PointerData(int data) : m_data(data) {
        printf("Default constructor called\n");
    }

    int GetData() const {
        return m_data; // 返回成员变量的值
    }

    void SetData(int data) {
        m_data = data; // 修改成员变量
    }

private:
    int m_data = 0; // 成员变量
};



class PointerTest {
public:
    PointerTest() : m_data(new PointerData(1)) {}
    
    ~PointerTest() {
        delete m_data; // delete nullptr 是安全的
    }

    PointerTest(const PointerTest& other) : 
        m_data(other.m_data ? new PointerData(*other.m_data) : nullptr) {}

    PointerTest& operator=(const PointerTest& other) {
        if (this != &other) {
            PointerTest temp(other); 
            std::swap(m_data, temp.m_data); // 交换指针
        }
        return *this;
    }

    // 移动构造函数（提升性能）
    PointerTest(PointerTest&& other) noexcept : m_data(std::exchange(other.m_data, nullptr)) {}    
    
    
    // 移动赋值运算符
    PointerTest& operator=(PointerTest&& other) noexcept {
        if (this != &other) {
            delete m_data;
            m_data = std::exchange(other.m_data, nullptr);
        }
        return *this;
    }

private:
    PointerData* m_data;
};

class PointerTest2 {
public:
    PointerTest2() : m_data(std::make_unique<PointerData>(1)) {}

private:
    std::unique_ptr<PointerData> m_data;
};


void test(){
    PointerTest2 test2;
    PointerTest2 test3 = std::move(test2); // 调用移动构造函数
}


class PointerTest1 {
public:
    PointerTest1():m_data(std::make_shared<PointerData>(1)) {}

    void SetData(PointerData data) {
        *m_data = std::move(data); 
    }

    std::shared_ptr<PointerData> GetData() const {
        return m_data;
    }

private:
    std::shared_ptr<PointerData> m_data; 
};



class TaskTest {

public:
    TaskTest() : m_isAlive(true) {}
    ~TaskTest() {
        std::lock_guard<std::mutex> lock(m_mutex); // 上锁
        m_isAlive = false; // 设置标志位为false
    }

    void TryStartTask() {
        std::thread([this](){
            std::this_thread::sleep_for(std::chrono::seconds(3)); 
            std::lock_guard<std::mutex> lock(m_mutex); // 上锁
            if (!m_isAlive) {
                return; // 如果标志位为false，直接返回
            }
            OnTask(); // 调用成员函数
        }).detach(); 
    }

private:
    void OnTask(){}

    bool m_isAlive;
    std::mutex m_mutex;
};


class TaskTest2 : std::enable_shared_from_this<TaskTest2> {

public:
    static std::shared_ptr<TaskTest2> Create() {
        return std::shared_ptr<TaskTest2>(new TaskTest2()); // 创建实例
    }

    // 拷贝构造函数和赋值运算符删除，防止拷贝
    TaskTest2(const TaskTest2&) = delete;
    TaskTest2& operator=(const TaskTest2&) = delete;
    // 移动构造函数和赋值运算符删除，防止移动
    TaskTest2(TaskTest2&&) = delete;
    TaskTest2& operator=(TaskTest2&&) = delete;

    void TryStartTask() {
        std::thread([weak = weak_from_this()](){
            std::this_thread::sleep_for(std::chrono::seconds(3)); 
            if (auto shared = weak.lock(); shared) {
                shared->OnTask(); // 调用成员函数
            } 
        }).detach(); 
    }

private:
    // 私有化构造函数
    TaskTest2() = default;
    
    void OnTask(){}

};


class ValueTypeData {};

class ValueTypeTest {
public:
    ValueTypeTest(const ValueTypeData& data) : m_data(std::move(data)) {} 

private:
    ValueTypeData m_data; // 成员变量
};

void Test(){
    ValueTypeData data;
    ValueTypeTest test(std::move(data));
}


using TestObserver = std::function<void(int)>; // 定义观察者类型

class WeakPointerTest {

public:
    WeakPointerTest() = default; // 默认构造函数

    void RegisterObserver(std::shared_ptr<TestObserver> observer) {
        m_observers.push_back(observer); // 注册观察者
    }

    void UnregisterObserver(std::shared_ptr<TestObserver> observer) {
        auto it = std::remove_if(m_observers.begin(), m_observers.end(),
            [&observer](const std::weak_ptr<TestObserver>& obs) {
                return obs.lock() == observer; // 移除观察者
            });
        m_observers.erase(it, m_observers.end()); // 删除无效观察者
    }

private:
    std::vector<std::weak_ptr<TestObserver>> m_observers; // 存储弱指针的容器

};

class WeakPointerTest {

public:
    WeakPointerTest() = default; // 默认构造函数

    void RegisterObserver(std::shared_ptr<TestObserver> observer) {
        m_observers.push_back(observer); // 注册观察者
    }

    void UnregisterObserver(std::shared_ptr<TestObserver> observer) {
        auto it = std::remove_if(m_observers.begin(), m_observers.end(),
            [&observer](const std::shared_ptr<TestObserver>& obs) {
                return obs == observer; // 移除观察者
            });
        m_observers.erase(it, m_observers.end()); // 删除无效观察者
    }

private:
    std::vector<std::shared_ptr<TestObserver>> m_observers; // 存储弱指针的容器

};

namespace pointer {
    inline void TestPointer(PointerTest1 test){
        std::shared_ptr<PointerData> data = test.GetData(); 
        data->SetData(2); // 修改成员变量的值
    }

    void Test() {
        PointerData* data = new PointerData(100);
        auto func = [data](){
            if (data) {
                printf("Value: %d\n", data->GetData());
            }
        };
    }

    void Test() {
        std::shared_ptr<PointerData> data = std::make_shared<PointerData>(100);
        auto func1 = [data](){
            if (data) {
                printf("Value: %d\n", data->GetData());
            }
        };
        auto func2 = [weakData = std::weak_ptr<PointerData>(data)](){
            if (auto data = weakData.lock()) {
                printf("Value: %d\n", data->GetData());
            } else {
                printf("Pointer is expired\n");
            }
        };
    }
   
} // namespace pointer