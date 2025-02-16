
#pragma once


#include "SwigCallbackData.h"
#include <memory>
#include <android/log.h>
#include <sstream>
#include <variant>
#include <iomanip>
#include <functional>
#include <any>
#include <optional>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>


struct FINFeatureFlagVariant {
    std::string name;                                                // 变体名称
    std::string payload;                                             // 变体载荷
    std::optional<std::string> str;
};

struct FINFeatureFlagModel {
    std::string id;                                                  // feature的id
    FINFeatureFlagVariant variant1;
    std::shared_ptr<FINFeatureFlagVariant> variant2 = nullptr;       // 变体（可以为空）
    std::optional<FINFeatureFlagVariant> variant3 = std::nullopt;       // 变体（可以为空）
};



class InnerObserver {

public:

    virtual ~InnerObserver() = default;

    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;

    virtual void setOptional(std::optional<FINFeatureFlagVariant> opt) = 0;

    virtual void setOptional2(std::optional<FINFeatureFlagVariant>& opt) = 0;

    virtual std::optional<FINFeatureFlagVariant> getOptional() = 0;

    virtual std::optional<FINFeatureFlagVariant> getOptional2() = 0;

};

using InnerObserver2 = std::function<void(const SwigCallbackData &data)>;

using InnerObserver3 = std::function<int(const SwigCallbackData &data)>;


using TestVariant = std::variant<int, double, std::string, bool, int64_t>;


class SwigCallback {

public:
    virtual ~SwigCallback() = default;

    virtual void onTestLong1(long long value) = 0;

    virtual long long onTestLong11(const long long &value) = 0;

    virtual void onTestLong2(int64_t value) = 0;

    virtual int64_t onTestLong22(const int64_t &value) = 0;

    virtual void onTestLong3(uint64_t value) = 0;

    virtual int64_t onTestLong33(const uint64_t &value) = 0;

//    virtual void onTestVariant1(TestVariant variant) = 0;
//
//    virtual void onTestVariant2(const TestVariant& variant) = 0;
//
//    virtual TestVariant onTestVariant3() = 0;
//
//    void testMap(const std::map<std::string, TestVariant, std::less<std::string>>::iterator itr) {
//
//    }
//
//    virtual void onTestVariant4(std::map<std::string, TestVariant> variants) = 0;
//
//    virtual ~SwigCallback() = default;
//
//    virtual void onTest2(InnerObserver2 &observer2) = 0;
//
//    virtual void onTest22(std::shared_ptr<InnerObserver2> observer2) = 0;


//    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;
//
//    virtual void onTest2(SwigCallbackData data2) = 0;
//
//    virtual void onTest3(std::shared_ptr<InnerObserver> innerCallback) = 0;
//
//    virtual std::shared_ptr<SwigCallbackData> onTest4(int gg) = 0;
//
//    virtual void onTest5(int a, std::string b, InnerObserver2 innerCallback, int c) = 0;
//
//    virtual void onTest6(int a, std::string b, InnerObserver2 innerCallback2, InnerObserver3 innerCallback3, int c) = 0;
//
//    virtual void onTest7(std::string str) = 0;
//    virtual std::string onTest8() = 0;
//
//    virtual void onTest9(std::optional<std::string>& str) = 0;
//    virtual std::optional<std::string>& onTest10() = 0;
//    virtual void onTest11(std::shared_ptr<std::string>& str) = 0;
//
//
//    virtual void onTest12(std::map<std::string, std::string> str) = 0;
//    virtual void onTest13(std::unordered_map<std::string, std::string> str) = 0;
//
//    virtual void onTest14(std::unordered_map<std::shared_ptr<FINFeatureFlagVariant>, std::string> str) = 0;
//
//
//    virtual std::shared_ptr<std::string> onTest12() = 0;
//
//    virtual ~SwigCallback() {
//        std::stringstream ss;
//        ss << std::hex << std::setfill('0') << std::setw(sizeof(void*) * 2)
//           << reinterpret_cast<uintptr_t>(this);
//
//        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "~SwigCallback() - Object address: 0x%s", ss.str().c_str());
//    };

};

using InnerObserver4 = std::function<void(const SwigCallbackData &data)>;

class AddRemoveObserverTest {

public:
    virtual ~AddRemoveObserverTest() = default;

    virtual void addObserver(std::shared_ptr<InnerObserver4> observer) = 0;

    virtual void removeObserver(std::shared_ptr<InnerObserver4> observer) = 0;

};