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

    ~JNIGlobalRef();

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

    jobject get() const;

private:
    jobject m_ref;
};


class SwigDirectorWrapper {
public:
    explicit SwigDirectorWrapper(JNIEnv *env, jobject obj)
            : m_data(std::make_unique<JNIGlobalRef>(env, obj)) {}

    explicit SwigDirectorWrapper(void *ptr) : m_data(reinterpret_cast<uintptr_t>(ptr)) {}

    ~SwigDirectorWrapper() = default;

    SwigDirectorWrapper(const SwigDirectorWrapper &) = delete;

    SwigDirectorWrapper &operator=(const SwigDirectorWrapper &) = delete;

    SwigDirectorWrapper(SwigDirectorWrapper &&) = default;

    SwigDirectorWrapper &operator=(SwigDirectorWrapper &&) = default;

    bool IsJObject() const noexcept;

    bool IsCPtr() const noexcept;

    jobject GetJObject() const noexcept;

    uintptr_t GetCPtr() const noexcept;

private:
    std::variant<std::unique_ptr<JNIGlobalRef>, uintptr_t> m_data;
};
