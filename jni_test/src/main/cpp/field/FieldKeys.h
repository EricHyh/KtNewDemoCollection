//
// Created by eriche on 2025/3/15.
//

#pragma once

#include <string>
#include <variant>
#include <optional>
#include "FieldDataModel.h"

namespace FieldKeys {

    extern const FiledKey<int> price;

    extern const FiledKey<std::string> name;

    extern const FiledKey<std::optional<std::string>> description;
};


