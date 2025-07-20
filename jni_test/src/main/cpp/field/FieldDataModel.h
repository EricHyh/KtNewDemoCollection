//
// Created by eriche on 2025/2/17.
//

#pragma once

#include "LiveData.h"
#include <string>
#include <optional>
#include <map>
#include <any>
#include <variant>
#include <vector>


class FieldDataModel;

class BaseFiledKey {

public:
    virtual ~BaseFiledKey() = default;

    virtual int32_t getKey() const = 0;

    friend FieldDataModel;

private:
    [[nodiscard]] virtual std::shared_ptr<ILiveData> CreateFieldValue(const FieldDataModel& dataModel) const = 0;
};


template<class Value>
class FiledKey;

template<class Value>
FiledKey<Value> makeFiledKey(int32_t, const Value &);


template<class Value>
class FiledKey : public BaseFiledKey {
public:

    FiledKey() = delete;

    int32_t getKey() const override {
        return this->m_key;
    }

    Value getDefaultValue() const {
        return this->m_defaultValue;
    }

    // 声明特定实例化的 makeFiledKey 为友元
    friend FiledKey<Value> makeFiledKey<Value>(int32_t, const Value &);

private:
    friend FieldDataModel;
    FiledKey(int32_t key, Value value) : m_key(key), m_defaultValue(std::move(value)) {}
    [[nodiscard]] std::shared_ptr<ILiveData> CreateFieldValue(const FieldDataModel& dataModel) const override {
        return std::make_shared<MutableLiveData<Value>>(m_defaultValue);
    }
    int32_t m_key;
    Value m_defaultValue;

};

template<class Value>
FiledKey<Value> makeFiledKey(int32_t key, const Value &value) {
    return FiledKey<Value>(key, value);
}


class FieldDataModel {

public:
    explicit FieldDataModel(const std::vector<std::shared_ptr<BaseFiledKey>> &keys) {
        for (const auto& baseKey: keys) {
            if (!baseKey) {
                continue;  // 跳过空指针
            }

            // 直接使用 BaseFiledKey 的 createFiledValue 方法
            m_valueMap[baseKey->getKey()] = baseKey->CreateFieldValue(*this);
        }
    }

    template<class Value>
    std::shared_ptr<LiveData<Value>> getFiledValue(const FiledKey<Value> &key) {
        auto it = m_valueMap.find(key.getKey());
        if (it != m_valueMap.end()) {
            auto ptr = std::dynamic_pointer_cast<MutableLiveData<Value>>(it->second);
            return ptr;
        }
        return std::dynamic_pointer_cast<MutableLiveData<Value>>(key.CreateFieldValue(*this));
    }

    std::shared_ptr<ILiveData> getBaseFiledValue(const BaseFiledKey &key) {
        auto it = m_valueMap.find(key.getKey());
        return it->second;
    }

private:
    std::map<int32_t, std::shared_ptr<ILiveData>> m_valueMap;
};

class MutableFieldDataModel : public FieldDataModel {
public:
    MutableFieldDataModel(const std::vector<std::shared_ptr<BaseFiledKey>> &keys) : FieldDataModel(keys) {}

    template<class Value>
    std::shared_ptr<MutableLiveData<Value>> getMutableFiledValue(const FiledKey<Value> &key) {
        auto baseValue = FieldDataModel::getFiledValue(key);
        return std::dynamic_pointer_cast<MutableLiveData<Value>>(baseValue);
    }

    // 引入基类的 getFiledValue，但设为 private
private:
    using FieldDataModel::getFiledValue;
};