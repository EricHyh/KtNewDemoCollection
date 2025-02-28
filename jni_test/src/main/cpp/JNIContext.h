//
// Created by eriche on 2024/8/16.
//

#pragma once

#include <jni.h>
#include <variant>
#include <memory>


class JNIContext {
public:
    static void SetJVM(JavaVM *jvm);

    JNIContext(JNIEnv *&env);

    ~JNIContext();

private:
    static JavaVM *g_jvm_;
    jboolean flag_;
};


class JNIGlobalRef {
public:
    JNIGlobalRef(JNIEnv *env, jobject obj) : m_ref(env->NewGlobalRef(obj)) {}

    ~JNIGlobalRef() {
        if (m_ref) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            env->DeleteGlobalRef(m_ref);
        }
    }

    JNIGlobalRef(const JNIGlobalRef &) = delete;

    JNIGlobalRef &operator=(const JNIGlobalRef &) = delete;

    jobject get() const { return m_ref; }

private:
    jobject m_ref;
};