
#pragma once


#include <string>
#include <memory>

using namespace std;

class SwigCallbackData {

public:
    int a;
    SwigCallbackData(const int a);

    void setStr(std::shared_ptr<std::string> str);

    void setStr2(shared_ptr<string> str);
};