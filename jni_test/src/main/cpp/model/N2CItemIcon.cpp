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