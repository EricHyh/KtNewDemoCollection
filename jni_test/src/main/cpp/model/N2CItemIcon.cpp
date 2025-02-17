//
// Created by eriche on 2024/12/21.
//

#include "N2CItemIcon.h"
#include "../TestUtil.h"

N2CItemIcon::N2CItemIcon(int index) {
    const std::pair<std::string, std::string> &pair = test_util::createIcon(index);
    this->name = pair.first;
    this->icon = pair.second;
}

std::string N2CItemIcon::getName() {
    return this->name;
}

std::string N2CItemIcon::getIcon() {
    return this->icon;
}


#include <string>
#include <map>
#include <any>
#include <utility>

template<class Value>
class FiledKey {
public:
    virtual std::string getKey() = 0;

    virtual Value getDefaultValue() = 0;
};

template<class Value>
class FiledValue {

public:
    Value getValue() {
        return m_value;
    }

    void setValue(const Value &value) {
        m_value = value;
    }

private:
    Value m_value;

};

class FieldDataModel {


public:
    template<class Value>
    std::shared_ptr<FiledValue<Value>> getFiledValue(FiledKey<Value> key) {

    }

private:
    std::map<std::string, std::shared_ptr<FiledValue<void>>> m_valueMap;

};

// 辅助函数，用于创建匿名 FiledKey
template<class Value>
auto makeFiledKey(std::string key, Value defaultValue) {
    return [key, defaultValue]() -> FiledKey<Value>* {
        struct AnonymousFiledKey : FiledKey<Value> {
            std::string m_key;
            Value m_defaultValue;
            AnonymousFiledKey(std::string  k, Value  v) : m_key(std::move(k)), m_defaultValue(std::move(v)) {}
            std::string getKey() override { return m_key; }
            Value getDefaultValue() override { return m_defaultValue; }
        };
        return new AnonymousFiledKey(key, defaultValue);
    }();
}

class Data;

namespace TradeOrderFiledKey {

    const static FiledKey<std::string>& code = *makeFiledKey<std::string>("", "");

    const static FiledKey<std::shared_ptr<Data>>& data = *makeFiledKey<std::shared_ptr<Data>>("", nullptr);

}