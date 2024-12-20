//
// Created by eriche on 2024/12/20.
//

#pragma once

#include <string>
#include <android/log.h>

#define LOG_TAG "Native2CPPItemTest"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class Native2CPPItemTest {

public:
    Native2CPPItemTest(int index);

    ~Native2CPPItemTest() = default;

    std::string getId() {
        LOGI("getId: %s", this->id.c_str());
        return this->id;
    }

    std::string getTitle() {
        LOGI("getTitle: %s", this->title.c_str());
        return this->title;
    }

    std::string getEnvelopePic() {
        LOGI("getEnvelopePic: %s", this->envelopePic.c_str());
        return this->envelopePic;
    }

    std::string getDesc() {
        LOGI("getDesc: %s", this->desc.c_str());
        return this->desc;
    }

    std::string getNiceDate() {
        LOGI("getNiceDate: %s", this->niceDate.c_str());
        return this->niceDate;
    }

    std::string getAuthor() {
        LOGI("getAuthor: %s", this->author.c_str());
        return this->author;
    }

private:
    std::string id;
    std::string title;
    std::string envelopePic;
    std::string desc;
    std::string niceDate;
    std::string author;
};
