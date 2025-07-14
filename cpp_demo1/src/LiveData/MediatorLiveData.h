//
// Created by eriche on 2025/5/11.
//

#pragma once

#include "LiveData.h"
#include <tuple>
#include <memory>
#include <utility>
#include <functional>

template<class T, class... Sources>
class NullSafetyMediatorLiveData final : public CFINLiveData<T> {
public:
    NullSafetyMediatorLiveData(
        std::tuple<std::shared_ptr<CFINLiveData<Sources>>...> sources,
        std::function<T(const std::tuple<Sources...>&)> calculate,
        const bool updateOnlyChanged = true
    ) : CFINLiveData<T>(calculate(GetValueTupleImpl(sources, std::make_index_sequence<sizeof...(Sources)>{}))),
        m_sources(std::move(sources)),
        m_calculate(std::move(calculate)),
        m_updateOnlyChanged(updateOnlyChanged) {
        AddSourcesImpl(m_sources, std::make_index_sequence<sizeof...(Sources)>{});
    }

    ~NullSafetyMediatorLiveData() override = default;

    T GetValue() const noexcept override {
        return m_calculate(GetValueTuple());
    }

private:
    using SourcesTuple = std::tuple<std::shared_ptr<CFINLiveData<Sources>>...>;
    SourcesTuple m_sources;
    std::function<T(const std::tuple<Sources...>&)> m_calculate;
    bool m_updateOnlyChanged;

    std::vector<std::shared_ptr<void>> m_source_observers;

    void UpdateValue() {
        CFINLiveData<T>::SetValueInternal(m_calculate(GetValueTuple()), !m_updateOnlyChanged);
    }

    template<size_t... I>
    auto GetValueTupleImpl(const SourcesTuple& sources, std::index_sequence<I...>) const {
        return std::make_tuple(std::get<I>(sources)->GetValue()...);
    }

    auto GetValueTuple() const {
        return GetValueTupleImpl(m_sources, std::make_index_sequence<sizeof...(Sources)>{});
    }

    template<size_t... I>
    void AddSourcesImpl(const SourcesTuple& sources, std::index_sequence<I...>) {
        // 使用折叠表达式展开参数包
        (([&] {
            // 推导具体类型
            using SourceType = typename std::tuple_element_t<I, SourcesTuple>::element_type;
            using ValueType = typename SourceType::value_type;

            // 创建观察者并保存
            auto observer = std::make_shared<FINLiveDataObserver<ValueType>>(
                [this](const auto&) { UpdateValue(); }
            );
            m_source_observers.emplace_back(observer); // 存入容器

            // 注册到数据源
            std::get<I>(sources)->AddObserver(observer, false);
        })(), ...);
    }
};


inline void testMutableLiveData() {
    CFINLiveDataObserverContainer container;


    // std::shared_ptr<CFINMutableLiveData<int>> source1 = std::make_shared<CFINMutableLiveData<int>>(1);
    std::shared_ptr<CFINMutableLiveData<int>> source1 = CFINMutableLiveData<int>::Create(1);
    // std::shared_ptr<CFINMutableLiveData<double>> source2 = std::make_shared<CFINMutableLiveData<double>>(2.0);
    std::shared_ptr<CFINMutableLiveData<double>> source2 = CFINMutableLiveData<double>::Create(2.0);


    const auto mediator = std::make_shared<NullSafetyMediatorLiveData<int, int, double>>(
        std::make_tuple(source1, source2),
        [](const std::tuple<int, double>& value) {
            return static_cast<int>(std::get<0>(value) + std::get<1>(value));
        }
    );

    auto mapper = CFINLiveDataMapper<int, std::string>::Create(mediator, [](const int& num) {
        return std::to_string(num + 100);
    });

    container.SetLiveDataObserver<int>(source1, [mediator](const int& num) {
        std::cout << "source1:" << num << std::endl;
        std::cout << "source1 mediator:" << mediator->GetValue() << std::endl;
    });

    container.SetLiveDataObserver<std::string>(mapper, [](const std::string& str) {
        std::cout << "mapper:" << str << std::endl;
    });

    const auto observer = std::make_shared<FINLiveDataObserver<int>>(
        [](const int& value) {
            //LOGI("testMutableLiveData %s", std::to_string(value).c_str());
            std::cout << "mediator:" << value << std::endl;
        });

    mediator->AddObserver(observer, true);

    source1->SetValue(3);
    source2->SetValue(4.0);
}
