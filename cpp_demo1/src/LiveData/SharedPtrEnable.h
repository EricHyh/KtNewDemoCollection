//
// Created by eriche on 2025/3/18.
//

#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>

// 宏定义：声明 friend class SharedPtrEnable 和创建智能指针的函数
#define DECLARE_PTR_CREATOR(ClassName) \
    public: \
        template<typename... Args> \
        static std::shared_ptr<ClassName> Create(Args&&... args) { \
            struct EnableMakeShared : public ClassName {    \
                explicit EnableMakeShared(Args&&... args) : ClassName(std::forward<Args>(args)...) {    \
                }   \
            };  \
            auto ptr = std::make_shared<EnableMakeShared>(std::forward<Args>(args)...);\
            ptr->AfterCreate();\
            return ptr;\
        }\
        ClassName(const ClassName&) = delete;   \
        ClassName& operator=(const ClassName&) = delete;    \
        ClassName(ClassName&&) = delete;    \
        ClassName& operator=(ClassName&&) = delete;


class SharedPtrEnable {
protected:
    // 保护构造函数，防止直接创建对象
    SharedPtrEnable() = default;

public:
    // 虚析构函数
    virtual ~SharedPtrEnable() = default;

    virtual void AfterCreate() {
    }

    // 禁用拷贝和移动
    SharedPtrEnable(const SharedPtrEnable&) = delete;

    SharedPtrEnable& operator=(const SharedPtrEnable&) = delete;

    SharedPtrEnable(SharedPtrEnable&&) = delete;

    SharedPtrEnable& operator=(SharedPtrEnable&&) = delete;
};

class Derived : public SharedPtrEnable, std::enable_shared_from_this<Derived> {
private:
    explicit Derived(int value) : value_(value) {
    }

    explicit Derived(std::string str) : str_(std::move(str)) {
    }

    Derived(int value, std::string str) : value_(value), str_(std::move(str)) {
    }

    DECLARE_PTR_CREATOR(Derived)

private:
    int value_{};
    std::string str_;
};

class Derived2 : public SharedPtrEnable, std::enable_shared_from_this<Derived2> {
private:
    explicit Derived2(int value) : value_(value) {
    }

    explicit Derived2(std::string str) : str_(std::move(str)) {
    }

    Derived2(int value, std::string str) : value_(value), str_(std::move(str)) {
    }

    DECLARE_PTR_CREATOR(Derived2)

private:
    int value_{};
    std::string str_;
};

namespace shared_ptr_test {
    inline void test() {
        const std::shared_ptr<Derived>& ptr1 = Derived::Create(1);
        const std::shared_ptr<Derived>& ptr2 = Derived::Create("");
        const std::shared_ptr<Derived>& ptr3 = Derived::Create(1, "");
    }
}
