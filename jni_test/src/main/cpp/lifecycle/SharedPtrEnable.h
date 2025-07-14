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
    friend class SharedPtrEnable; \
    public: \
        template<typename... Args> \
        static std::shared_ptr<ClassName> Create(Args&&... args) { \
            return SharedPtrEnable<ClassName>::Create(std::forward<Args>(args)...); \
        }


template<class T>
class SharedPtrEnable : public std::enable_shared_from_this<T> {
protected:
    // 保护构造函数，防止直接创建对象
    SharedPtrEnable() = default;

public:
    // 静态工厂方法
    template<typename... Args>
    static std::shared_ptr<T> Create(Args &&... args) {
        // 使用自定义的创建方法
        struct EnableMakeShared : public T {
            explicit EnableMakeShared(Args &&... args) : T(std::forward<Args>(args)...) {}
        };
        return std::make_shared<EnableMakeShared>(std::forward<Args>(args)...);
    }

    // 虚析构函数
    virtual ~SharedPtrEnable() = default;

    // 禁用拷贝和移动
    SharedPtrEnable(const SharedPtrEnable &) = delete;

    SharedPtrEnable &operator=(const SharedPtrEnable &) = delete;

    SharedPtrEnable(SharedPtrEnable &&) = delete;

    SharedPtrEnable &operator=(SharedPtrEnable &&) = delete;

    // 获取 shared_ptr
    std::shared_ptr<T> GetShared() {
        return shared_from_this();
    }

    // 获取 shared_ptr
    std::weak_ptr<T> GetWeak() {
        return weak_from_this();
    }

private:
    using std::enable_shared_from_this<T>::shared_from_this;
    using std::enable_shared_from_this<T>::weak_from_this;
};

class Derived : public SharedPtrEnable<Derived> {
private:

    explicit Derived(int value) : value_(value) {}

    explicit Derived(std::string str) : str_(std::move(str)) {}

    Derived(int value, std::string str) : value_(value), str_(std::move(str)) {}

    DECLARE_PTR_CREATOR(Derived)

private:
    int value_;
    std::string str_;
};


void test() {
    const std::shared_ptr<Derived> &ptr1 = Derived::Create(1);
    const std::shared_ptr<Derived> &ptr2 = Derived::Create("");
    const std::shared_ptr<Derived> &ptr3 = Derived::Create(1, "");
}