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


//using TestVariant = std::variant<std::string, int>;
using TestVariant = std::variant<std::monostate, TestEnum2, TestStruct>;

class IObserverManager {

public:
    virtual ~IObserverManager() = default;

    virtual void addObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void removeObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void byteTest1(std::vector<uint8_t> byteArray) = 0;

    virtual std::vector<uint8_t> byteTest2() = 0;

    virtual void byteTest3(jbyteArray byteArray) = 0;

    virtual jbyteArray byteTest4() = 0;

    virtual void testVariant1(const std::map<TestEnum1, TestVariant> params) = 0;
    virtual void testMap1(std::map<int, int> params) = 0;

    virtual void testVariant2(const std::map<TestEnum1, TestVariant>& params) = 0;
    virtual void testMap2(const std::map<int, int>& params) = 0;

    virtual std::map<TestEnum1, TestVariant> testVariant3() = 0;
    virtual std::map<int, int> testMap3() = 0;

    virtual std::map<TestEnum1, TestVariant>& testVariant4() = 0;
    virtual std::map<int, int>& testMap4() = 0;

    //std::map<int, TestVariant, std::less<int> >::iterator;
};


class ObserverManager {

public:
    static void init(IObserverManager *manager);

    static void addObserver(std::shared_ptr<TestObserver> observer);

    static void removeObserver(std::shared_ptr<TestObserver> observer);


private:
    static IObserverManager* s_manager;

};

