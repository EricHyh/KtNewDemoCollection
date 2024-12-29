//
// Created by eriche on 2024/12/29.
//

#include "TestColor.h"

int N2CTestColor::getRandomColor() {
    int r = dist(rd);
    int g = dist(rd);
    int b = dist(rd);
    return (0xff << 24) | (r << 16) | (g << 8) | b;
}

std::string N2CTestColor::add(std::string a, std::string b) {
    int a_num = stoi(a);
    int b_num = stoi(b);
    return std::to_string(a_num + b_num);
}


ITestColor *TestColorFactory::m_color = nullptr;

void TestColorFactory::init(ITestColor *color) {
    m_color = color;
}

ITestColor *TestColorFactory::create() {
    return m_color;
}
