//
// Created by eriche on 2025/6/5.
//

#pragma once

#include <memory>
#include "FieldBizModel.h"
#include <optional>
#include <functional>
#include <cstdint>
#include <utility>

class ITradeOrderBizEngine {

public:
    virtual ~ITradeOrderBizEngine() = default;

    virtual void Init() = 0;

    virtual void Apply(std::shared_ptr<IModify> modify) = 0;

    virtual FieldDataModel GetFieldDataModel() const = 0;

};


class DataInitScope {

public:
    template<class Value>
    Value GetDependentField(FiledKey<Value> key);


};


template<class Value>
struct FieldValueInitConfig {

    std::function<bool(const DataInitScope&)> enable;

    std::function<std::optional<Value>(const DataInitScope&)> valueProvider;

    std::function<bool(const DataInitScope&)> ignoreCheck;

    std::function<bool(const DataInitScope&, const Value&)> isValidValue;

    std::function<void(const DataInitScope&, Value&)> optimizeValue;

    std::function<void(const DataInitScope&)> defaultValue;
};

template<class Value>
using FieldValueInitResult = std::pair<Value, uint8_t>;


void xxx(const DataInitScope& scope) {
    FieldValueInitConfig<int> config{
            [](const DataInitScope& scope) { return false; },
            [](const DataInitScope& scope) { return std::nullopt; },
            [](const DataInitScope& scope) { return false; },
            [](const DataInitScope& scope, const int& value) { return false; },
            [](const DataInitScope& scope, int& value) {}
    };
}


class RestDataModifyBuilder {

public:

    template<class Value>
    void SpecifyField(const FiledKey<Value> key, Value value);

    void SpecifyFields(const FieldDataModel& dataModel);

};

struct RestDataModify {

    int resetScene = 0;

    FieldDataModel specifyFields;

};


struct LaunchModify {

    int launchScene = 0;

    FieldDataModel specifyFields;

};

void test2(std::shared_ptr<BaseFiledKey> key){

}

void test1(){
    test2(std::make_shared<FiledKey<std::string>>(FieldKeys::name));
}

