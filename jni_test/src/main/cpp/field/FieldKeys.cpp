//
// Created by eriche on 2025/3/15.
//

#include "FieldKeys.h"


namespace FieldKeys {

    extern const FiledKey<int> price = makeFiledKey(1, 10);

    extern const FiledKey<std::string> name = makeFiledKey(2, std::string("a"));

    extern const FiledKey<std::optional<std::string>> description = makeFiledKey(3,(std::optional<std::string>)std::nullopt);

};