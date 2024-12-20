//
// Created by eriche on 2024/12/20.
//

#pragma once

#include <jni.h>
#include <string>

class CPP2NativeItemTest {
public:
    CPP2NativeItemTest(int index);

    ~CPP2NativeItemTest() = default;

    std::string getId();

    std::string getTitle();

    std::string getEnvelopePic();

    std::string getDesc();

    std::string getNiceDate();

    std::string getAuthor();

private:
    jobject nativeObj;
};

