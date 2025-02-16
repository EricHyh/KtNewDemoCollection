//
// Created by eriche on 2025/2/17.
//

#pragma once

#include <string>
#include <map>
#include <any>

template<class Value>
class FiledKey {
public:
    virtual std::string getKey();

    virtual Value getDefaultValue();
};


class FieldDataModel {


public:
    template<class Value>
    Value getFiledValue(FiledKey<Value> key) {

    }

private:
    std::map<std::string, std::any> m_valueMap;

};


