//
// Created by eriche on 2024/8/23.
//
#pragma once

#include <jni.h>
#include "JNIContext.h"

using namespace financial_sdk;

struct JObjectWrapper {

    jobject receiver;

    JObjectWrapper(JNIEnv *env, jobject obj) {
        receiver = env->NewGlobalRef(obj);
    }

    ~JObjectWrapper() {
        JNIEnv *env = nullptr;
        JNIContext context(env);
        env->DeleteGlobalRef(receiver);
    }

    JObjectWrapper(const JObjectWrapper &) = delete;

    JObjectWrapper &operator=(const JObjectWrapper &) = delete;

};


