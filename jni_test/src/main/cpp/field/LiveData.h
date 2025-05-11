//
// Created by eriche on 2025/3/16.
//

#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <shared_mutex>
#include <optional>
#include <any>
#include <iostream>
#include <tuple>

template<class Value>
using LiveDataObserver = std::function<void(const Value &)>;


//class AnyLiveDataObserver : public std::function<void()> {
//public:
//    AnyLiveDataObserver() : m_binding(nullptr) {}
//
//    void SetBinding(const std::shared_ptr<void> &observer) {
//        this->m_binding = observer;
//    }
//
//    std::any GetBinding() const {
//        return m_binding;
//    }
//
//private:
//    std::any m_binding;
//};


//class IBaseLiveData {
//public:
//    virtual ~IBaseLiveData() = default;
//
//private:
//    template<class T>
//    friend
//    class MediatorLiveData;
//
//    virtual std::any GetValueAsAny() = 0;
//
//    virtual void AddAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) = 0;
//
//    virtual void RemoveAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) = 0;
//};

template<class Value>
class LiveData {
public:

    typedef Value value_type;

    LiveData() = delete;

    virtual ~LiveData() = default;

    explicit LiveData(Value value) : m_value(std::move(value)) {}

    virtual Value GetValue() const {
        std::shared_lock<std::shared_mutex> lock(m_valueMutex);
        return m_value;
    }

    virtual void AddObserver(std::shared_ptr<LiveDataObserver<Value>> observer, bool immediately) {
        // 1. 添加观察者（写锁保护）
        {
            std::unique_lock<std::shared_mutex> observerLock(m_observerMutex);
            m_observers.emplace_back(std::move(observer));
        }

        // 2. 立即通知观察者（读锁保护）
        if (immediately) {
            std::optional<Value> tempValue; // 延迟初始化
            {
                std::shared_lock<std::shared_mutex> valueLock(m_valueMutex);
                tempValue.emplace(m_value); // 调用拷贝构造函数
            }
            (*observer)(*tempValue); // 传递值副本
        }
    }

    virtual void RemoveObserver(std::shared_ptr<LiveDataObserver<Value>> observer) {
        std::unique_lock<std::shared_mutex> lock(m_observerMutex);
        m_observers.erase(
                std::remove_if(m_observers.begin(), m_observers.end(),
                               [&observer](const auto &weakObs) {
                                   auto sharedObs = weakObs.lock();
                                   return !sharedObs || sharedObs.get() == observer.get(); // 比较原始指针
                               }),
                m_observers.end()
        );
    }

protected:
    void SetValueInternal(const Value &value, bool force = false) {
        bool updated = false;
        {
            std::unique_lock<std::shared_mutex> lock(m_valueMutex);
            if (force || m_value != value) {
                m_value = value;
                updated = true;
            }
        }

        if (updated) {
            NotifyObservers(value);
        }
    }

private:
    Value m_value;
    mutable std::shared_mutex m_valueMutex;
    std::vector<std::weak_ptr<LiveDataObserver<Value>>> m_observers;
    mutable std::shared_mutex m_observerMutex;

    void NotifyObservers(const Value &newValue) {
        std::vector<std::shared_ptr<LiveDataObserver<Value>>> activeObservers;
        {
            std::shared_lock<std::shared_mutex> lock(m_observerMutex);
            for (const auto &weakObs: m_observers) {
                if (auto observer = weakObs.lock()) {
                    activeObservers.push_back(observer);
                }
            }
        }

        for (const auto &observer: activeObservers) {
            (*observer)(newValue);
        }

        // Clean up expired observers
        std::unique_lock<std::shared_mutex> lock(m_observerMutex);
        m_observers.erase(
                std::remove_if(m_observers.begin(), m_observers.end(),
                               [](const std::weak_ptr<LiveDataObserver<Value>> &weakObs) {
                                   return weakObs.expired();
                               }),
                m_observers.end()
        );
    }
//
//    std::any GetValueAsAny() override {
//        return m_value;
//    }

//    void AddAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) override{
//        std::shared_ptr<LiveDataObserver<Value>> binding = std::make_shared<LiveDataObserver<Value>>(
//                [weak = std::weak_ptr<AnyLiveDataObserver>(observer)](const Value &value) {
//                    if(auto observer = weak.lock()){
//                        observer->operator()();
//                    }
//                });
//        observer->SetBinding(binding);
//        AddObserver(binding, false);
//    }
//
//    void RemoveAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) override {
//        if (!observer) return;
//        auto binding = std::any_cast<std::shared_ptr<LiveDataObserver<Value>>>(observer->GetBinding());
//        RemoveObserver(binding);
//    }
};


template<class Value>
class MutableLiveData : public LiveData<Value> {
public:
    using value_type = Value; // 添加 value_type 类型别名

    MutableLiveData() = delete;

    explicit MutableLiveData(Value value) : LiveData<Value>(value) {}

    void SetValue(const Value &value) {
        LiveData<Value>::SetValueInternal(value);
    }
};

//
//
//template<class Value>
//class MediatorLiveData : public LiveData<Value>,
//                         std::enable_shared_from_this<MediatorLiveData<Value>> {
//
//private:
//    static std::vector<std::any> GetValues(
//            const std::vector<std::shared_ptr<IBaseLiveData>> &sources
//    ) {
//        std::vector<std::any> values;
//        for (const auto &source: sources) {
//            values.push_back(source->GetValueAsAny());
//        }
//        return values;
//    }
//
//
//public:
//    MediatorLiveData(
//            std::vector<std::shared_ptr<IBaseLiveData>> sources,
//            std::function<Value(const std::vector<std::any> &)> calculate
//    ) : LiveData<Value>(calculate(GetValues(sources))),
//        m_sources(std::move(sources)),
//        m_calculate(std::move(calculate)),
//        m_observer(nullptr) {}
//
//    ~MediatorLiveData() override {
//        TryRemoveAnyValueObserver();
//    }
//
//    Value GetValue() const override {
//        return m_calculate(GetValues(m_sources));
//    }
//
//    void AddObserver(std::shared_ptr<LiveDataObserver<Value>> observer, bool immediately) override {
//        TryAddAnyValueObserver();
//        LiveData<Value>::AddObserver(observer, immediately);
//    }
//
//    void RemoveObserver(std::shared_ptr<LiveDataObserver<Value>> observer) override {
//        LiveData<Value>::RemoveObserver(observer);
//        TryRemoveAnyValueObserver();
//    }
//
//private:
//    std::vector<std::shared_ptr<IBaseLiveData>> m_sources;
//    std::function<Value(const std::vector<std::any> &)> m_calculate;
//    std::shared_ptr<AnyLiveDataObserver> m_observer;
//
//    void TryAddAnyValueObserver() {
//        if (m_observer) return;
//        std::weak_ptr<MediatorLiveData<Value>> self = this->weak_from_this();
//        m_observer = std::make_shared<AnyLiveDataObserver>([weak = self] {
//            if (auto shared = weak.lock()) {
//                shared->UpdateValue();
//            }
//        });
//        this->AddAnyValueObserver(m_observer);
//    }
//
//    void TryRemoveAnyValueObserver() {
//        if (!m_observer) return;
//        this->RemoveAnyValueObserver(m_observer);
//    }
//
//    void UpdateValue() {
//        auto values = GetValues(m_sources);
//        auto newValue = m_calculate(values);
//
//        auto oldValue = LiveData<Value>::GetValue();
//        if (oldValue == newValue) {
//            return;
//        }
//        this->SetValueInternal(newValue);
//    }
//};
//
//
