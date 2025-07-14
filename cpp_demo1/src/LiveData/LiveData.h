//
// Created by eriche on 2025/3/19.
//

#pragma once

#include <atomic>
#include <memory>
#include <functional>
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <optional>
#include <string>
#include <iostream>
#include "SharedPtrEnable.h"

template<class Value>
using FINLiveDataObserver = std::function<void(const Value&)>;


template<class Value>
class CFINLiveData {
public:
    typedef Value value_type;

    CFINLiveData() = delete;

    virtual ~CFINLiveData() noexcept = default;

    /**
     * 获取当前值
     * @return 当前存储的值
     * @note 线程安全，但返回的是值的副本
     */
    virtual Value GetValue() const noexcept {
        std::shared_lock<std::shared_mutex> lock(m_valueMutex);
        return m_value;
    }

    /**
     * 添加观察者
     * @param observer 观察者函数
     * @param notifyImmediately 是否立即通知当前值
     * @note 线程安全
     */
    void AddObserver(std::shared_ptr<FINLiveDataObserver<Value>> observer, bool notifyImmediately) {
        // 1. 添加观察者（写锁保护）
        {
            std::unique_lock<std::shared_mutex> observerLock(m_observerMutex);
            m_observers.emplace_back(std::move(observer));
        }

        // 2. 立即通知观察者（读锁保护）
        if (notifyImmediately) {
            std::optional<Value> tempValue; // 延迟初始化
            {
                std::shared_lock<std::shared_mutex> valueLock(m_valueMutex);
                tempValue.emplace(m_value); // 调用拷贝构造函数
            }
            (*observer)(*tempValue); // 传递值副本
        }
    }

    /**
     * 移除观察者
     * @param observer 要移除的观察者
     * @note 线程安全
     */
    void RemoveObserver(std::shared_ptr<FINLiveDataObserver<Value>> observer) noexcept {
        std::unique_lock<std::shared_mutex> lock(m_observerMutex);
        m_observers.erase(
            std::remove_if(
                m_observers.begin(), m_observers.end(),
                [&observer](const std::weak_ptr<FINLiveDataObserver<Value>>& weakObs) {
                    auto sharedObs = weakObs.lock();
                    return !sharedObs || sharedObs == observer;
                }),
            m_observers.end()
        );
    }

protected:
    explicit CFINLiveData(Value value) : m_value(std::move(value)) {
    }

    /**
     * 内部设置值的方法
     * @param value 新值
     * @param force 是否强制更新
     * @return 如果值被更新返回true
     * @note 线程安全
     */
    bool SetValueInternal(const Value& value, bool force) {
        bool updated = false; {
            std::unique_lock<std::shared_mutex> lock(m_valueMutex);
            if (force || m_value != value) {
                m_value = value;
                updated = true;
            }
        }

        if (updated) {
            NotifyObservers(value);
        }
        return updated;
    }

private:
    Value m_value;
    mutable std::shared_mutex m_valueMutex;

    std::vector<std::weak_ptr<FINLiveDataObserver<Value>>> m_observers;
    mutable std::shared_mutex m_observerMutex;

    void NotifyObservers(const Value& newValue) noexcept {
        std::vector<std::shared_ptr<FINLiveDataObserver<Value>>> activeObservers; {
            std::shared_lock<std::shared_mutex> lock(m_observerMutex);
            for (const auto& weakObs: m_observers) {
                if (auto observer = weakObs.lock()) {
                    activeObservers.push_back(observer);
                }
            }
        }

        for (const auto& observer: activeObservers) {
            (*observer)(newValue);
        }

        // Clean up expired observers
        std::unique_lock<std::shared_mutex> lock(m_observerMutex);
        m_observers.erase(
            std::remove_if(m_observers.begin(), m_observers.end(),
                           [](const std::weak_ptr<FINLiveDataObserver<Value>>& weakObs) {
                               return weakObs.expired();
                           }),
            m_observers.end()
        );
    }
};


template<class Value>
class CFINMutableLiveData : public CFINLiveData<Value>,
                            public std::enable_shared_from_this<CFINMutableLiveData<Value>> {
    /**
     * 使用初始值创建可变LiveData
     * @param value 初始值
     */
    explicit CFINMutableLiveData(Value value) : CFINLiveData<Value>(std::move(value)) {
    }

    static void AfterCreate() {
    }

    DECLARE_PTR_CREATOR(CFINMutableLiveData)

    /**
     * 设置新值
     * @param value 新值
     * @param force 是否强制更新
     * @return 如果值被更新返回true
     */
    bool SetValue(const Value& value, bool force = false) {
        return CFINLiveData<Value>::SetValueInternal(value, force);
    }
};


template<typename Source, typename Target>
class CFINLiveDataMapper : public CFINLiveData<Target>,
                           public std::enable_shared_from_this<CFINLiveDataMapper<Source, Target>> {
    CFINLiveDataMapper(
        std::shared_ptr<CFINLiveData<Source>> source,
        std::function<Target(const Source&)> mapper
    ) : CFINLiveData<Target>(Target{}), // 初始化基类（需提供初始值）
        m_source(std::move(source)),
        m_mapper(std::move(mapper)) {
        m_observer = std::make_shared<FINLiveDataObserver<Source>>(
            [weak_this = this->weak_from_this()](const Source& sourceValue) {
                if (auto self = weak_this.lock()) {
                    // 应用映射函数并更新目标值
                    auto mappedValue = self->m_mapper(sourceValue);
                    self->SetValueInternal(mappedValue, false);
                }
            }
        );

        // 注册观察者，并立即触发一次映射
        m_source->AddObserver(m_observer, true);
    }

    void AfterCreate() {
        // 创建观察者并注册到源LiveData
        m_observer = std::make_shared<FINLiveDataObserver<Source>>(
            [weak_this = this->weak_from_this()](const Source& sourceValue) {
                if (auto self = weak_this.lock()) {
                    // 应用映射函数并更新目标值
                    auto mappedValue = self->m_mapper(sourceValue);
                    self->SetValueInternal(mappedValue, false);
                }
            }
        );

        // 注册观察者，并立即触发一次映射
        m_source->AddObserver(m_observer, true);
    }

    DECLARE_PTR_CREATOR(CFINLiveDataMapper)

private:
    std::shared_ptr<CFINLiveData<Source>> m_source;
    std::function<Target(const Source&)> m_mapper;
    std::shared_ptr<FINLiveDataObserver<Source>> m_observer;
};


class LiveDataDispose {



};


class CFINLiveDataObserverContainer {
private:
    struct IFINObserverWrapper {
        virtual ~IFINObserverWrapper() = default;
    };

    template<class Value>
    struct FINObserverWrapper : IFINObserverWrapper {
        std::weak_ptr<CFINLiveData<Value>> liveData;

        std::shared_ptr<FINLiveDataObserver<Value>> observer;

        FINObserverWrapper() = delete;

        FINObserverWrapper(const std::shared_ptr<CFINLiveData<Value>>& liveData,
                           const std::shared_ptr<FINLiveDataObserver<Value>>& observer,
                           bool notifyImmediately): liveData(liveData), observer(observer) {
            liveData->AddObserver(observer, notifyImmediately);
        }

        ~FINObserverWrapper() override {
            if (auto shared = liveData.lock()) {
                shared->RemoveObserver(observer);
            }
        }
    };

public:
    virtual ~CFINLiveDataObserverContainer() = default;

    template<class Value>
    void SetLiveDataObserver(
        const std::shared_ptr<CFINLiveData<Value>>& liveData,
        FINLiveDataObserver<Value> observer,
        bool notifyImmediately = false) {
        auto observer_ptr = std::make_shared<FINLiveDataObserver<Value>>(std::move(observer));
        m_observers.emplace_back(std::make_shared<FINObserverWrapper<Value>>(
                liveData,
                observer_ptr,
                notifyImmediately)
        );
    }

private:
    std::vector<std::shared_ptr<IFINObserverWrapper>> m_observers;
};

namespace live_data {
    inline void test1() {
        CFINLiveDataObserverContainer container;

        // auto source = std::make_shared<CFINMutableLiveData<int>>(10);
        auto source = CFINMutableLiveData<int>::Create(10);
        const auto mapper = CFINLiveDataMapper<int, std::string>::Create(source, [](const int& num) {
            return std::to_string(num + 100);
        });

        container.SetLiveDataObserver<int>(source, [](const int& value) {
            std::cout << "test1:" << value << std::endl;
        }, false);
        container.SetLiveDataObserver<std::string>(mapper, [](const std::string& value) {
            std::cout << "test2:" << value << std::endl;
        }, false);


        source->SetValue(11);
        source->SetValue(100);
    }
}
