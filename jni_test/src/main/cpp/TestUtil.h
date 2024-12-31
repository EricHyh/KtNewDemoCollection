//
// Created by eriche on 2024/12/21.
//

#pragma once

#include <sstream>
#include <iostream>

#include <vector>
#include <utility>
#include <string>
#include <android/log.h>

#define LOG_TAG "N2CTestItem"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace test_util {

    template<typename... Args>
    inline std::string concat(Args &&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }

    const static std::vector<std::pair<std::string, std::string>> &icons = {
            std::make_pair<std::string, std::string>(
                    "WanAndroid基础",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"),
            std::make_pair<std::string, std::string>(
                    "Gradle Plugin",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"),
            std::make_pair<std::string, std::string>(
                    "Material Design",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"),
            std::make_pair<std::string, std::string>(
                    "MVI-Dispatcher",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"),
            std::make_pair<std::string, std::string>(
                    "出行防疫App",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"),
            std::make_pair<std::string, std::string>(
                    "北京公交",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"),
            std::make_pair<std::string, std::string>(
                    "wechat_flutter",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"),
            std::make_pair<std::string, std::string>(
                    "WanAndroid",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"),
            std::make_pair<std::string, std::string>(
                    "Piko",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"),
            std::make_pair<std::string, std::string>(
                    "Android组件化",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"),

            std::make_pair<std::string, std::string>(
                    "WanAndroid基础",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"),
            std::make_pair<std::string, std::string>(
                    "Gradle Plugin",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"),
            std::make_pair<std::string, std::string>(
                    "Material Design",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"),
            std::make_pair<std::string, std::string>(
                    "MVI-Dispatcher",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"),
            std::make_pair<std::string, std::string>(
                    "出行防疫App",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"),
            std::make_pair<std::string, std::string>(
                    "北京公交",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"),
            std::make_pair<std::string, std::string>(
                    "wechat_flutter",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"),
            std::make_pair<std::string, std::string>(
                    "WanAndroid",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"),
            std::make_pair<std::string, std::string>(
                    "Piko",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"),
            std::make_pair<std::string, std::string>(
                    "Android组件化",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"),

            std::make_pair<std::string, std::string>(
                    "WanAndroid基础",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"),
            std::make_pair<std::string, std::string>(
                    "Gradle Plugin",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"),
            std::make_pair<std::string, std::string>(
                    "Material Design",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"),
            std::make_pair<std::string, std::string>(
                    "MVI-Dispatcher",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"),
            std::make_pair<std::string, std::string>(
                    "出行防疫App",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"),
            std::make_pair<std::string, std::string>(
                    "北京公交",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"),
            std::make_pair<std::string, std::string>(
                    "wechat_flutter",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"),
            std::make_pair<std::string, std::string>(
                    "WanAndroid",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"),
            std::make_pair<std::string, std::string>(
                    "Piko",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"),
            std::make_pair<std::string, std::string>(
                    "Android组件化",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"),
    };

    inline std::pair<std::string, std::string> createIcon(int index) {
        index = index % icons.size();
        std::pair<std::string, std::string> pair = icons[index];
        pair.first = concat(pair.first, "-", index);
        return pair;
    }
}
