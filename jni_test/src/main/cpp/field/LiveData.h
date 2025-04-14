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


class IBaseLiveData {
public:
    virtual ~IBaseLiveData() = default;

private:
    template<class T>
    friend class MediatorLiveData;

    virtual std::any GetValueAsAny() = 0;

//    virtual void AddAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) = 0;
//
//    virtual void RemoveAnyValueObserver(std::shared_ptr<AnyLiveDataObserver> observer) = 0;
};

template<class Value>
class LiveData : public IBaseLiveData
        {
public:
    LiveData() = delete;

    virtual ~LiveData() override = default;

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
                               [&observer](const auto& weakObs) {
                                   auto sharedObs = weakObs.lock();
                                   return !sharedObs || sharedObs.get() == observer.get(); // 比较原始指针
                               }),
                m_observers.end()
        );
    }

protected:
    void SetValueInternal(const Value& value, bool force = false) {
        bool updated = false;
        {
            std::unique_lock<std::shared_mutex> lock(m_valueMutex);
            if (force || m_value != value) {
                m_value = value;
                updated = true;
            }
        }

        if (updated) {
            NotifyObservers( value);
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

    std::any GetValueAsAny() override {
        return m_value;
    }

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

    void SetValue(const Value& value) {
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
//template<class T, class... Sources>
//class NullSafetyMediatorLiveData : public LiveData<T> {
//public:
//    NullSafetyMediatorLiveData(
//            std::tuple<std::shared_ptr<Sources>...> sources, // 接受智能指针
//            std::function<T(const std::tuple<typename Sources::value_type...> &)> calculate,
//            bool updateOnlyChanged = true,
//            std::function<bool(const T &, const T &)> isValueEquals = [](const T &a, const T &b) { return a == b; }
//    ) : LiveData<T>(calculate(GetValueTupleImpl(sources, std::make_index_sequence<sizeof...(Sources)>{}))),
//        m_sources(sources),
//        m_calculate(calculate),
//        m_updateOnlyChanged(updateOnlyChanged),
//        m_isValueEquals(isValueEquals) {
//        AddSourcesImpl(sources, std::make_index_sequence<sizeof...(Sources)>{});
//    }
//
//private:
//    using SourcesTuple = std::tuple<std::shared_ptr<Sources>...>;
//    SourcesTuple m_sources;
//    std::function<T(const std::tuple<typename Sources::value_type...> &)> m_calculate;
//    bool m_updateOnlyChanged;
//    std::function<bool(const T &, const T &)> m_isValueEquals;
//
//    void UpdateValue() {
//        auto values = GetValueTuple();
//        auto newValue = m_calculate(values);
//
//        if (m_updateOnlyChanged) {
//            auto oldValue = this->GetValue();
//            if (m_isValueEquals(oldValue, newValue)) {
//                return;
//            }
//        }
//
//        this->SetValueInternal(newValue);
//    }
//
//    template<size_t... I>
//    auto GetValueTupleImpl(const SourcesTuple &sources, std::index_sequence<I...>) {
//        return std::make_tuple(std::get<I>(sources)->GetValue()...);
//    }
//
//    auto GetValueTuple() {
//        return GetValueTupleImpl(m_sources, std::make_index_sequence<sizeof...(Sources)>{});
//    }
//
//    template<size_t... I>
//    void AddSourcesImpl(const SourcesTuple &sources, std::index_sequence<I...>) {
//        (std::get<I>(sources)->AddObserver(
//                std::make_shared<LiveDataObserver<
//                        typename std::tuple_element_t<I, SourcesTuple>::element_type::value_type
//                >>([this](const auto &value) { UpdateValue(); }), false
//        ), ...);
//    }
//};
//
//
//void test() {
//    auto source1 = std::make_shared<MutableLiveData<int>>(1);
//    auto source2 = std::make_shared<MutableLiveData<double>>(2.0);
//
//    auto mediator = std::shared_ptr<NullSafetyMediatorLiveData<int, MutableLiveData<int>, MutableLiveData<double>>>(
//            new NullSafetyMediatorLiveData<int, MutableLiveData<int>, MutableLiveData<double>>(
//                    std::make_tuple(source1, source2), // 直接传递智能指针
//                    [](const std::tuple<int, double> &values) {
//                        return static_cast<int>(std::get<0>(values) + std::get<1>(values));
//                    }
//            )
//    );
//
//    mediator->AddObserver(std::make_shared<LiveDataObserver<int>>([](const int &value) {
//        std::cout << "Value updated: " << value << std::endl;
//    }), true);
//
//    source1->SetValue(3);
//    source2->SetValue(4.0);
//}