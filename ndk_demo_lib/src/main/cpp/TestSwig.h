//
// Created by eriche on 2024/8/24.
//

#pragma once

#include "memory"
#include <string>
#include <functional>
#include "TestSwigData.h"

//class TestCallback {
//public:
//    static TestCallback* newCallback();
//    TestCallback() {} // 添加空构造函数
//    virtual void onTest(const double & msg) = 0;
//    virtual ~TestCallback() {}
//};

using TestCallback = std::function<void(const TestSwigData &)>;

using TestCallback3 = std::function<void(const TestSwigData &)>;

template <typename T>
using TestCallback4 = std::function<void(const T &)>;

class TestSwig {

private:
    double r{}; // 半径
public:
    TestSwig();         // 构造函数
    TestSwig(double R); // 构造函数
    double Area() const;    // 求面积函数

    void test1(const TestSwigData &data) const;

    void test2(const TestCallback &callback) const;

    void test3(const TestCallback3 &callback) const;

    void test4(const TestCallback4<int> &callback) const;

    //void test44(const TestCallback4<double> &callback) const;

};

// 添加这个声明
class TestCallbackWrapper {
public:
    virtual ~TestCallbackWrapper() {}
    virtual void call(const TestSwigData& value) = 0;
};


class TestCallback3Wrapper {
public:
    virtual ~TestCallback3Wrapper() {}
    virtual void call(const TestSwigData& value) = 0;
};

template <typename T>
class TestCallback4Wrapper {
public:
    virtual ~TestCallback4Wrapper() {}
    virtual void call(const T& value) = 0;
};


//class IntTestCallback4Wrapper : public TestCallback4Wrapper<int> {};

//void testCallbackAdapter(TestSwig* self, TestCallbackWrapper* wrapper);