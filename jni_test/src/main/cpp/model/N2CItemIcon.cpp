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


//#include <string>
//#include <map>
//#include <any>
//#include <utility>
//
//template<class Value>
//class FiledKey {
//public:
//    virtual std::string getKey() = 0;
//
//    virtual Value getDefaultValue() = 0;
//};
//
//template<class Value>
//class MutableLiveData {
//
//public:
//    Value getValue() {
//        return m_value;
//    }
//
//    void setValue(const Value &value) {
//        m_value = value;
//    }
//
//private:
//    Value m_value;
//
//};
//
//class FieldDataModel {
//
//
//public:
//    template<class Value>
//    std::shared_ptr<MutableLiveData<Value>> getFiledValue(FiledKey<Value> key) {
//
//    }
//
//private:
//    std::map<std::string, std::shared_ptr<MutableLiveData<void>>> m_valueMap;
//
//};
//
//// 辅助函数，用于创建匿名 FiledKey
//template<class Value>
//auto makeFiledKey(std::string key, Value defaultValue) {
//    return [key, defaultValue]() -> FiledKey<Value>* {
//        struct AnonymousFiledKey : FiledKey<Value> {
//            std::string m_key;
//            Value m_defaultValue;
//            AnonymousFiledKey(std::string  k, Value  v) : m_key(std::move(k)), m_defaultValue(std::move(v)) {}
//            std::string getKey() override { return m_key; }
//            Value getDefaultValue() override { return m_defaultValue; }
//        };
//        return new AnonymousFiledKey(key, defaultValue);
//    }();
//}
//
//class Data;
//
//namespace TradeOrderFiledKey {
//
//    const static FiledKey<std::string>& code = *makeFiledKey<std::string>("", "");
//
//    const static FiledKey<std::shared_ptr<Data>>& data = *makeFiledKey<std::shared_ptr<Data>>("", nullptr);
//
//}


// 前向声明
//template<class Value>
//class FiledKey;
//
//template<class Value>
//FiledKey<Value> makeFiledKey(const std::string &key, const Value &defaultValue);

// FiledKey 结构体定义
//template<class Value>
//struct FiledKey {
//public:
//    static FiledKey<Value> makeFiledKey(const std::string &key, const Value &defaultValue) {
//        return FiledKey<Value>(key, defaultValue);
//    }
//
//    FiledKey() = delete;
//
//    std::string getKey() const {
//        return this->m_key;
//    }
//
//    Value getDefaultValue() const {
//        return this->m_defaultValue;
//    }
//
//    // 声明特定实例化的 makeFiledKey 为友元
//    //friend FiledKey<Value> makeFiledKey<Value>(const std::string&, const Value&);
//
//private:
//    FiledKey(std::string key, Value value) : m_key(std::move(key)), m_defaultValue(std::move(value)) {}
//
//    std::string m_key;
//    Value m_defaultValue;
//
//};
//
//template<class Value>
//using FieldValueObserver = std::function<void(const Value &)>;
//
//template<class Value>
//class MutableLiveData {
//public:
//    MutableLiveData() = delete;
//
//    explicit MutableLiveData(Value value) : m_value(std::move(value)) {}
//
//    Value GetValue() {
//        return m_value;
//    }
//
//    void SetValue(Value value) {
//        if (m_value != value) {
//            Value oldValue = m_value;
//            m_value = std::move(value);
//            NotifyObservers(oldValue, m_value);
//        }
//    }
//
//    void AddObserver(std::shared_ptr<FieldValueObserver<Value>> observer);
//
//    void RemoveObserver(std::shared_ptr<FieldValueObserver<Value>> observer);
//
//
//private:
//    Value m_value;
//    std::vector<std::shared_ptr<FieldValueObserver<Value>>> m_observers;
//
//    void NotifyObservers(const Value &oldValue, const Value &newValue) {
//        for (const auto &observer: m_observers) {
//            observer(newValue);
//        }
//    }
//};
//
//template<class Value>
//void MutableLiveData<Value>::RemoveObserver(std::shared_ptr<FieldValueObserver<Value>> observer) {
//    auto it = std::find(m_observers.begin(), m_observers.end(), observer);
//    if (it != m_observers.end()) {
//        m_observers.erase(it);
//    }
//}
//
//template<class Value>
//void MutableLiveData<Value>::AddObserver(std::shared_ptr<FieldValueObserver<Value>> observer) {
//    if (observer) {
//        auto it = std::find(m_observers.begin(), m_observers.end(), observer);
//        if (it == m_observers.end()) {
//            m_observers.push_back(observer);
//        }
//    }
//}