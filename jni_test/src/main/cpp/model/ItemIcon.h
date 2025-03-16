//
// Created by eriche on 2024/12/21.
//

#pragma once
#include <string>

class IItemIcon {
public:
    virtual ~IItemIcon() = default;

    virtual std::string getName() = 0;

    virtual std::string getIcon() = 0;

};


