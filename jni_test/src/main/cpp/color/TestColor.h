//
// Created by eriche on 2024/12/29.
//

#pragma once

#include <random>
#include <memory>
#include <string>

class ITestColor {

public:
    virtual ~ITestColor() = default;

    virtual int getRandomColor() = 0;

    virtual std::string add(std::string a, std::string b) = 0;

};


class N2CTestColor : public ITestColor {

public:
    int getRandomColor() override;
    std::string add(std::string a, std::string b) override;

private:
    std::random_device rd;
    std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(0, 256);
    std::minstd_rand generator = std::minstd_rand();
};

class TestColorFactory {

public:
    static void init(ITestColor *color);

    static ITestColor *create();

private:
    static ITestColor *m_color;
};