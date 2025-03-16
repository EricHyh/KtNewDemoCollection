//
// Created by eriche on 2025/3/16.
//

#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <shared_mutex>

template<class Value>
using LiveDataObserver = std::function<void(const Value &)>;


template<class Value>
class LiveData {
public:
    LiveData() = delete;

    virtual ~LiveData() = default;

    explicit LiveData(Value value) : m_value(std::move(value)) {}

    virtual Value GetValue() const {
        std::shared_lock<std::shared_mutex> lock(m_valueMutex);
        return m_value;
    }

    void AddObserver(std::shared_ptr<LiveDataObserver<Value>> observer, bool immediately) {
        Value currentValue;
        {
            std::unique_lock<std::shared_mutex> lock(m_observerMutex);
            m_observers.push_back(observer);
            if (immediately) {
                std::shared_lock<std::shared_mutex> valueLock(m_valueMutex);
                currentValue = m_value;
            }
        }

        if (immediately) {
            // 在锁外调用观察者，避免死锁
            (*observer)(currentValue);
        }
    }

    void RemoveObserver(std::shared_ptr<LiveDataObserver<Value>> observer) {
        std::unique_lock<std::shared_mutex> lock(m_observerMutex);
        m_observers.erase(
                std::remove_if(m_observers.begin(), m_observers.end(),
                               [&observer](const std::weak_ptr<LiveDataObserver<Value>> &weakObs) {
                                   auto sharedObs = weakObs.lock();
                                   return !sharedObs || sharedObs == observer;
                               }),
                m_observers.end()
        );
    }

protected:
    void SetValueInternal(Value value, bool force = false) {
        Value oldValue;
        bool updated = false;
        {
            std::unique_lock<std::shared_mutex> lock(m_valueMutex);
            oldValue = m_value;
            if (force || oldValue != value) {
                m_value = std::move(value);
                updated = true;
            }
        }

        if (updated) {
            NotifyObservers(oldValue, m_value);
        }
    }

private:
    Value m_value;
    mutable std::shared_mutex m_valueMutex;
    std::vector<std::weak_ptr<LiveDataObserver<Value>>> m_observers;
    mutable std::shared_mutex m_observerMutex;

    void NotifyObservers(const Value &oldValue, const Value &newValue) {
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
};


template<class Value>
class MutableLiveData : public LiveData<Value> {
public:
    MutableLiveData() = delete;

    explicit MutableLiveData(Value value) : LiveData<Value>(value) {}

    void SetValue(Value value) {
        LiveData<Value>::SetValueInternal(value);
    }
};