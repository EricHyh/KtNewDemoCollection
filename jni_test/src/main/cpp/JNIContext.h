//
// Created by eriche on 2024/8/16.
//

#pragma once

#include <jni.h>


class JNIContext {
public:
    static void SetJVM(JavaVM *jvm);

    JNIContext(JNIEnv *&env);

    ~JNIContext();

private:
    static JavaVM *g_jvm_;
    jboolean flag_;
};

