
#pragma once


#include "SwigCallbackData.h"
#include <memory>
#include <android/log.h>
#include <sstream>
#include <iomanip>
#include <functional>
#include <any>

class InnerObserver {

public:
    virtual ~InnerObserver() = default;
    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;

};

using InnerObserver2 = std::function<void(const SwigCallbackData &data)>;

using InnerObserver3 = std::function<void(const SwigCallbackData &data)>;

class SwigCallback {

public:

    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;

    virtual void onTest2(SwigCallbackData data2) = 0;

    virtual void onTest3(std::shared_ptr<InnerObserver> innerCallback) = 0;

    virtual std::shared_ptr<SwigCallbackData> onTest4(int gg) = 0;

    virtual void onTest5(int a, std::string b, InnerObserver2 innerCallback, int c) = 0;

    virtual void onTest6(int a, std::string b, InnerObserver2 innerCallback2, InnerObserver3 innerCallback3, int c) = 0;

    virtual ~SwigCallback() {
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(sizeof(void*) * 2)
           << reinterpret_cast<uintptr_t>(this);

        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "~SwigCallback() - Object address: 0x%s", ss.str().c_str());
    };

};

struct FINFeatureFlagVariant {
    std::string name;                                                // 变体名称
    std::string payload;                                             // 变体载荷
};

struct FINFeatureFlagModel {
    std::string id;                                                  // feature的id
    std::shared_ptr<FINFeatureFlagVariant> variant = nullptr;       // 变体（可以为空）
};