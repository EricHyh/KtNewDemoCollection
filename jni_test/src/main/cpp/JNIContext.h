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

    // 拷贝构造函数
    JNIGlobalRef(const JNIGlobalRef &other) : m_ref(nullptr) {
        if (other.m_ref) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            m_ref = env->NewGlobalRef(other.m_ref);
        }
    }

    // 拷贝赋值运算符
    JNIGlobalRef &operator=(const JNIGlobalRef &other) {
        if (this != &other) {
            JNIGlobalRef temp(other);
            std::swap(m_ref, temp.m_ref);
        }
        return *this;
    }

    // 移动构造函数
    JNIGlobalRef(JNIGlobalRef&& other) noexcept : m_ref(other.m_ref) {
        other.m_ref = nullptr;
    }

    // 移动赋值运算符
    JNIGlobalRef& operator=(JNIGlobalRef&& other) noexcept {
        if (this != &other) {
            if (m_ref) {
                JNIEnv *env = nullptr;
                JNIContext context(env);
                env->DeleteGlobalRef(m_ref);
            }
            m_ref = other.m_ref;
            other.m_ref = nullptr;
        }
        return *this;
    }

    jobject get() const { return m_ref; }

private:
    jobject m_ref;
};