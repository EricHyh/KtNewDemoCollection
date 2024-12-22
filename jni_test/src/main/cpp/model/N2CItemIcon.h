//
// Created by eriche on 2024/12/21.
//

#pragma once

#include <string>
#include "ItemIcon.h"

class N2CItemIcon : public IItemIcon {

public:
    N2CItemIcon(int index);

    std::string getName() override;

    std::string getIcon() override;

private:
    std::string name;
    std::string icon;
};


