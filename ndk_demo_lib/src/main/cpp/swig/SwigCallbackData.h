
#pragma once


#include <string>
#include <memory>

using namespace std;

class SwigCallbackData {

public:
    SwigCallbackData(const int a);

    void setStr(std::shared_ptr<std::string> str);

    void setStr2(shared_ptr<string> str);
};