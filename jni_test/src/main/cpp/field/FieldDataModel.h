//
// Created by eriche on 2025/2/17.
//

#pragma once

#include <string>
#include <map>
#include <any>
#include <variant>

template<class Value>
class FiledKey {
public:
    virtual std::string getKey() = 0;

    virtual Value getDefaultValue() = 0;
};

template<class Value>
class FiledValue {
public:

    Value getValue();

    void AddObserver(std::shared_ptr<std::function<void(Value)>> observer);

    void RemoveObserver(std::shared_ptr<std::function<void(Value)>> observer);

};


class FieldDataModel {

public:
    template<class Value>
    FiledValue<Value> getFiledValue(FiledKey<Value> key) {

    }

private:
    std::map<std::string, std::any> m_valueMap;

};


