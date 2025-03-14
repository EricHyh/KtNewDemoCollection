//
// Created by eriche on 2025/2/16.
//

#pragma once

#include <string>
#include <functional>
#include <memory>
#include <cstdint>
#include <optional>
#include <vector>
#include <jni.h>
#include <map>
#include <variant>

using TestObserver = std::function<void(const int &data)>;

struct TestObserver2Data {
    const int a;

    TestObserver2Data(int a) : a(a) {}
};

typedef std::function<void(const TestObserver2Data &data)> TestObserver2;


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


struct TestOptional {

    std::optional<TestEnum1> enum1;

    TestEnum1 enum11;

};

class ITestObserver2 {
public:
    virtual ~ITestObserver2() = default;

    virtual void onCall(const int &data) = 0;
};


class IObserverManager {

public:
    virtual ~IObserverManager() = default;

    virtual void addObserver(std::shared_ptr<const TestObserver> observer) = 0;

    virtual void removeObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void addObserver2(std::shared_ptr<ITestObserver2> observer) = 0;

    virtual void removeObserver2(std::shared_ptr<ITestObserver2> observer) = 0;

    virtual int64_t add1(int64_t a, int64_t b) = 0;

    virtual long long add11(long long a, long long b) = 0;

    virtual int64_t add2(const int64_t &a, const int64_t &b) = 0;

    virtual long long add22(const long long &a, const long long &b) = 0;

    virtual std::optional<int64_t> add3(std::optional<int64_t> a, std::optional<int64_t> b) = 0;

    virtual std::optional<int64_t> add33(const std::optional<int64_t> &a, const std::optional<int64_t> &b) = 0;

    virtual void byteTest1(std::vector<uint8_t> byteArray) = 0;

    virtual void byteTest2(const std::vector<uint8_t> &byteArray) = 0;

    virtual std::vector<uint8_t> byteTest3() = 0;

    virtual void setTestObserver2List(std::vector<TestObserver2>) = 0;

    virtual TestEnum1 optionalEnum33() = 0;

    virtual std::optional<TestEnum1> &optionalEnum4() = 0;

    virtual TestEnum1 &optionalEnum44() = 0;
};

virtual void optionalTest1(std::optional<TestOptional> option) = 0;

virtual void optionalTest2(const std::optional<TestOptional> &option) = 0;

virtual std::optional<TestOptional> optionalTest3() = 0;

virtual std::optional<TestOptional> &optionalTest4() = 0;

virtual TestOptional optionalTest33() = 0;

virtual TestOptional &optionalTest44() = 0;

virtual void optionalEnum1(std::optional<TestEnum1> option) = 0;

virtual void optionalEnum11(TestEnum1 option) = 0;

virtual void optionalEnum2(const std::optional<TestEnum1> &option) = 0;

virtual void optionalEnum22(const TestEnum1 &option) = 0;

virtual std::optional<TestEnum1> optionalEnum3() = 0;

class ObserverManager {

public:
    static void init(IObserverManager *manager);

    static void addObserver(std::shared_ptr<TestObserver> observer);

    static void removeObserver(std::shared_ptr<TestObserver> observer);

    static void addObserver2(std::shared_ptr<ITestObserver2> observer);

    static void removeObserver2(std::shared_ptr<ITestObserver2> observer);

    static int64_t add1(int64_t a, int64_t b);

    static long long add11(long long a, long long b);

    static int64_t add2(int64_t &a, int64_t &b);

    static long long add22(const long long &a, const long long &b);

    static std::optional<int64_t> add3(std::optional<int64_t> a, std::optional<int64_t> b);

    static std::optional<int64_t> add33(const std::optional<int64_t> &a, const std::optional<int64_t> &b);

    static void byteTest1(std::vector<uint8_t> byteArray);

    static void byteTest2(const std::vector<uint8_t> &byteArray);

    static std::vector<uint8_t> byteTest3();

private:
    static IObserverManager *s_manager;

};

