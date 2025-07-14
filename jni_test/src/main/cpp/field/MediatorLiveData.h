//
// Created by eriche on 2025/5/11.
//

#pragma once

#include "LiveData.h"
#include <thread>
#include <tuple>
#include <memory>
#include <utility>
#include "TestUtil.h"

template<class T, class... Sources>
class NullSafetyMediatorLiveData : public LiveData<T> {
public:
    NullSafetyMediatorLiveData(
            std::tuple<std::shared_ptr<Sources>...> sources, // 接受智能指针
            std::function<T(const std::tuple<typename Sources::value_type...> &)> calculate,
            bool updateOnlyChanged = true,
            std::function<bool(const T &, const T &)> isValueEquals = [](const T &a, const T &b) { return a == b; }
    ) : LiveData<T>(calculate(GetValueTupleImpl(sources, std::make_index_sequence<sizeof...(Sources)>{}))),
        m_sources(std::move(sources)),
        m_calculate(std::move(calculate)),
        m_updateOnlyChanged(updateOnlyChanged),
        m_isValueEquals(std::move(isValueEquals)) {
        AddSourcesImpl(sources, std::make_index_sequence<sizeof...(Sources)>{});
    }

    ~NullSafetyMediatorLiveData() override = default;

private:
    using SourcesTuple = std::tuple<std::shared_ptr<Sources>...>;
    SourcesTuple m_sources;
    std::function<T(const std::tuple<typename Sources::value_type...> &)> m_calculate;
    bool m_updateOnlyChanged;
    std::function<bool(const T &, const T &)> m_isValueEquals;

    std::vector<std::shared_ptr<void>> m_source_observers;

    void UpdateValue() {
        auto values = GetValueTuple();
        auto newValue = m_calculate(values);

        if (m_updateOnlyChanged) {
            auto oldValue = this->GetValue();
            if (m_isValueEquals(oldValue, newValue)) {
                return;
            }
        }

        this->SetValueInternal(newValue);
    }

    template<size_t... I>
    auto GetValueTupleImpl(const SourcesTuple &sources, std::index_sequence<I...>) {
        return std::make_tuple(std::get<I>(sources)->GetValue()...);
    }

    auto GetValueTuple() {
        return GetValueTupleImpl(m_sources, std::make_index_sequence<sizeof...(Sources)>{});
    }

    template<size_t... I>
    void AddSourcesImpl(const SourcesTuple &sources, std::index_sequence<I...>) {
        // 使用折叠表达式展开参数包
        (([&] {
            // 推导具体类型
            using SourceType = typename std::tuple_element_t<I, SourcesTuple>::element_type;
            using ValueType = typename SourceType::value_type;

            // 创建观察者并保存
            auto observer = std::make_shared<LiveDataObserver<ValueType>>(
                    [this](const auto& value) { UpdateValue(); }
            );
            m_source_observers.emplace_back(observer);  // 存入容器

            // 注册到数据源
            std::get<I>(sources)->AddObserver(observer, false);
        })(), ...);
    }
};


inline void testMutableLiveData() {
    auto source1 = std::make_shared<MutableLiveData<int>>(1);
    auto source2 = std::make_shared<MutableLiveData<double>>(2.0);

//    auto mediator = std::shared_ptr<NullSafetyMediatorLiveData<int, MutableLiveData<int>, MutableLiveData<double>>>(
//            new NullSafetyMediatorLiveData<int, MutableLiveData<int>, MutableLiveData<double>>(
//                    std::make_tuple(source1, source2), // 直接传递智能指针
//                    [](const std::tuple<int, double> &values) {
//                        return static_cast<int>(std::get<0>(values) + std::get<1>(values));
//                    }
//            )
//    );

    auto mediator = std::make_shared<NullSafetyMediatorLiveData<int, MutableLiveData<int>, MutableLiveData<double>>>(
            std::make_tuple(source1, source2),
            [](const std::tuple<int, double> &values) {
                return static_cast<int>(std::get<0>(values) + std::get<1>(values));
            }
    );

    std::shared_ptr<LiveDataObserver<int>> observer = std::make_shared<LiveDataObserver<int>>(
            [](const int &value) {
                LOGI("testMutableLiveData %s", std::to_string(value).c_str());
            });

    mediator->AddObserver(observer, true);

    source1->SetValue(3);
    source2->SetValue(4.0);
}


inline void testGetJavaObj(){
    ObserverManager::optionalEnum33();
    std::thread([]{
        ObserverManager::optionalEnum33();
        const std::shared_ptr<ITestObserver2> &ptr = ObserverManager::getObserver2();
        if(ptr){
            ptr->onCall(1);
        }

    }).detach();
}

