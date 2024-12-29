//
// Created by eriche on 2024/12/21.
//

#include "N2CItemIcon.h"
#include "TestUtil.h"

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
