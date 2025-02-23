//
// Created by eriche on 2025/2/16.
//

#pragma once

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <jni.h>
#include <map>
#include <variant>

using TestObserver = std::function<void(const int &data)>;

enum class TestEnum1 {
    AllTradingTime = 0,   // 全时段
    UsPreMarketAfter = 1  // 美股盘前盘后
};

enum class TestEnum2 {
    AllTradingTime = 0,   // 全时段
    UsPreMarketAfter = 1  // 美股盘前盘后
};

struct TestStruct {
    std::string groupName;  // 分组名称
};

class ITestObserver2 {
public:
    virtual ~ITestObserver2() = default;

    virtual void onCall(const int &data) = 0;
};


class IObserverManager {

public:
    virtual ~IObserverManager() = default;

    virtual void addObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void removeObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void addObserver2(std::shared_ptr<ITestObserver2> observer) = 0;

    virtual void removeObserver2(std::shared_ptr<ITestObserver2> observer) = 0;

//    virtual void byteTest1(std::vector<uint8_t> byteArray) = 0;
//
//    virtual std::vector<uint8_t> byteTest2() = 0;
//
//    virtual void byteTest3(jbyteArray byteArray) = 0;
//
//    virtual jbyteArray byteTest4() = 0;

};


class ObserverManager {

public:
    static void init(IObserverManager *manager);

    static void addObserver(std::shared_ptr<TestObserver> observer);

    static void removeObserver(std::shared_ptr<TestObserver> observer);

    static void addObserver2(std::shared_ptr<ITestObserver2> observer);

    static void removeObserver2(std::shared_ptr<ITestObserver2> observer);


private:
    static IObserverManager *s_manager;

};

