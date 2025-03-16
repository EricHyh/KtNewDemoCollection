//
// Created by eriche on 2025/3/16.
//

#include "LiveData.h"

#include <string>
#include <optional>
#include "JNIContext.h"

class OptionalStringLiveDataObserver {

public:
    OptionalStringLiveDataObserver() : m_func(nullptr) {}

    virtual ~OptionalStringLiveDataObserver() = default;

    virtual void onCall(const std::optional<std::string> &value) = 0;

    virtual int calculateHash() {
        return static_cast<int>(std::hash<const OptionalStringLiveDataObserver *>{}(this));
    }

    virtual bool isEquals(const OptionalStringLiveDataObserver &other) {
        return this == &other;
    }


    static LiveDataObserver<std::optional<std::string>> obtainOriginal(JNIEnv *jenv, std::shared_ptr<OptionalStringLiveDataObserver> *function_bridge, jobject j_function_bridge) {
        using ReturnType = typename LiveDataObserver<std::optional<std::string>>::result_type;
        std::weak_ptr<OptionalStringLiveDataObserver> weak_function_bridge = *function_bridge;
        LiveDataObserver<std::optional<std::string>> observer = [weak_function_bridge, ref = JNIGlobalRef(jenv,j_function_bridge)](
                const std::optional<std::string> &value) -> ReturnType {
            std::shared_ptr<OptionalStringLiveDataObserver> function_bridge_ptr = weak_function_bridge.lock();

            if (function_bridge_ptr) {
                return function_bridge_ptr->onCall(value);
            } else if (std::is_same_v<void, void>) {
                return;
            } else {
                return ReturnType();
            }
        };
        return observer;
    }

    static std::shared_ptr<LiveDataObserver<std::optional<std::string>>> obtainOriginal(std::shared_ptr<OptionalStringLiveDataObserver> *function_bridge) {
        if (auto func_ptr = (*function_bridge)->m_func) {
            return func_ptr;
        }

        std::weak_ptr<OptionalStringLiveDataObserver> weak_function_bridge = *function_bridge;
        std::shared_ptr<LiveDataObserver<std::optional<std::string>>> func_ptr = std::make_shared<LiveDataObserver<std::optional<std::string>>>([weak_function_bridge](const std::optional<std::string> &value) -> void {
            std::shared_ptr<OptionalStringLiveDataObserver> function_bridge_ptr = weak_function_bridge.lock();
            using ReturnType = typename LiveDataObserver<std::optional<std::string>>::result_type;
            if (function_bridge_ptr) {
                return function_bridge_ptr->onCall(value);
            } else if (std::is_same_v<ReturnType, void>) {
                return;
            } else {
                return ReturnType();
            }
        });

        (*function_bridge)->m_func = func_ptr;

        return func_ptr;
    }

private:

    std::shared_ptr<LiveDataObserver<std::optional<std::string>>> m_func;

};