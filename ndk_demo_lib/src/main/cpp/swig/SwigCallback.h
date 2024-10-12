
#pragma once


#include "SwigCallbackData.h"
#include <memory>
#include <android/log.h>
#include <sstream>
#include <iomanip>

class InnerObserver {

public:
    virtual ~InnerObserver() = default;
    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;

};


class SwigCallback {

public:

    virtual void onTest1(std::shared_ptr<SwigCallbackData> data1) = 0;

    virtual void onTest2(SwigCallbackData data2) = 0;

    virtual void onTest3(std::shared_ptr<InnerObserver> innerCallback) = 0;

    virtual std::shared_ptr<SwigCallbackData> onTest4(int gg) = 0;

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