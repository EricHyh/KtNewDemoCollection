//
// Created by eriche on 2025/3/15.
//

#pragma once

#include <string>
#include <variant>
#include <optional>
#include "FieldDataModel.h"

namespace FieldKeys {


    const FiledKey<int> price = makeFiledKey(1, 10);

    const FiledKey<std::string> name = makeFiledKey(2, std::string("a"));

    const FiledKey<std::optional<std::string>> description = makeFiledKey(3, (std::optional<std::string>) std::nullopt);

};


