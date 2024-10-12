
#pragma once


#include "SwigCallback.h"
#include <memory>
#include <functional>

using SwigCallbackFunction = std::function<void(const SwigCallbackData &)>;

using SwigCallbackFunction1 = std::function<void(const SwigCallbackData &)>;


class TestSwigCallback{


public:
    void setCallback1(SwigCallback* swigCallback);

    void setCallback2(std::shared_ptr<SwigCallback> swigCallback);

    void setCallback3(int num, std::shared_ptr<SwigCallback> swigCallback);

    void setCallback4(SwigCallbackFunction swigCallback);

    void setCallback5(SwigCallbackFunction1 swigCallback);
};