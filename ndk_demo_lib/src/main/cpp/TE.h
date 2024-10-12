//
// Created by eriche on 2024/8/28.
//

#pragma once


#include <iostream>

// step1. 定义一个宏来包含需要用到的枚举值
#define MY_ENUM_VALUES \
    X(SPRING) \
    X(SUMMER) \
    X(AUTUMN) \
    X(WINTER)

// step2. 利用宏展开获取并定义枚举
#ifdef X
#undef X
#endif
#define X(x) x,
enum {
    MY_ENUM_VALUES
};

// step3. 重新定义宏函数X(),并获取新的展开形式，以获取枚举值对应的字符串；
#ifdef X
#undef X
#endif
#define X(x) case (x): { return #x; }
#define MAKE_ENUM_CASES \
    MY_ENUM_VALUES \
    default: { return "unknown enum string."; }

// step4. 定义获取枚举对应的字符串函数
const char * myenumToString(int n) {
    switch (n) {
        MAKE_ENUM_CASES
    }
}

int main() {
    int n = 0;
    for (n = SPRING; n <= WINTER; ++n) {
        // step5. 调用函数，得到定义的枚举值对应的字符串
        std::cout << "enum: " << n << "-" << myenumToString(n) << std::endl;
    }
    return 0;
}
