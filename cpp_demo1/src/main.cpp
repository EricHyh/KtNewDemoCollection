//
// Created by eriche on 2025/4/12.
//

#include "main.h"
#include "BizModel/TestBizModel.h"
#include <type_traits> // 用于类型检查
#include <functional> // 用于类型检查
#include <iostream>
#include <tuple>

#include "LiveData/LiveData.h"
#include "LiveData/SharedPtrEnable.h"
#include "LiveData/MediatorLiveData.h"

class CopyTest {
public:
    // 默认构造函数
    explicit CopyTest(const int num) : m_int(num) {
    }

    // 拷贝构造函数
    CopyTest(const CopyTest& orig) : m_int(orig.m_int) {
        // 深拷贝逻辑（如果需要）
        std::cout << "Copy constructor called\n" << std::endl;
    }

    // 移动构造函数
    CopyTest(CopyTest&& orig) noexcept : m_int(orig.m_int) {
        // 确保将原对象置为有效状态
        orig.m_int = 0;
        std::cout << "Move constructor called\n" << std::endl;
    }

    // 拷贝赋值运算符
    CopyTest& operator=(const CopyTest& rhs) {
        if (this != &rhs) {
            // 防止自赋值
            m_int = rhs.m_int;
            // 深拷贝逻辑（如果需要）
        }
        std::cout << "Copy assignment operator called\n" << std::endl;
        return *this;
    }

    // 移动赋值运算符
    CopyTest& operator=(CopyTest&& rhs) noexcept {
        if (this != &rhs) {
            // 防止自赋值
            m_int = rhs.m_int;
            // 确保将原对象置为有效状态
            rhs.m_int = 0;
        }
        std::cout << "Move assignment operator called\n" << std::endl;
        return *this;
    }

    void Print() const {
        std::cout << m_int << std::endl;
    }

private:
    int m_int; // 类的唯一成员变量
};

namespace {
    void test1() {
        // getchar();       // 等待用户输入[6,8](@ref)


        // TestFieldBizModel bizModel;
        // bizModel.Apply(std::make_shared<XXXModify1>());
        // bizModel.Apply(std::make_shared<XXXModify2>());
        // bizModel.Apply(XXXModify3());
        // bizModel.Apply(XXXModify4());
        // bizModel.Apply(std::make_shared<XXXModify4>());


        CopyTest test1(10);
        CopyTest test2(20);
        CopyTest test3(30);

        CopyTest& test_ref = test1;


        CopyTest *const test_ptr = &test1;

        // test_ref = test2;
        test2 = test3;


        test1.Print();
        test_ref.Print();
    }


    template<typename... Args>
    auto add(const Args... args) {
        static_assert((std::is_arithmetic_v<Args> && ...),
                      "All arguments must be numeric types!");
        return (0 + ... + args); // 二元左折叠，支持空参数包
    }

    void test2() {
        const auto num = add(0, 2.1, 3, 4, 5, 6);
        std::cout << "test2:" << num << std::endl;
    }

    template<typename Value>
    struct LazyData {
        std::function<Value()> getValue1;
        std::function<Value()> getValue2;
        std::function<bool()> success;
    };

    template<typename Value>
    struct LazyData2 {
        std::function<Value()> getValue1;
        std::function<Value()> getValue2;
        std::function<bool()> success;
    };

    // 递归终止函数（无参数时返回0）
    template<typename Value>
    Value add_impl() {
        return Value();
    }

    // 递归展开函数（处理至少一个参数）
    template<typename Value, typename Head, typename... Tail>
    Value add_impl(const Head& head, const Tail&... tail) {
        if (head.success()) {
            return head.getValue1() + head.getValue2();
        }
        return add_impl<Value>(tail...);
    }

    // 主模板函数（自动推导返回类型）
    template<typename... Args>
    auto addLazyData(const Args&... args) {
        if constexpr (sizeof...(args) == 0) {
            return 0; // 无参数时直接返回0
        } else {
            // 获取第一个参数的类型并推导Value类型
            using FirstType = std::tuple_element_t<0, std::tuple<Args...> >;
            using ValueType = decltype(std::declval<FirstType>().getValue1() + std::declval<FirstType>().getValue2());
            return add_impl<ValueType>(args...);
        }
    }


    template<typename... Args>
    auto addLazyData2(const Args&... args) {
        // 推导返回值类型（以首个参数的 getValue1 类型为准）
        using FirstType = std::tuple_element_t<0, std::tuple<Args...> >;
        using ValueType = decltype(std::declval<FirstType>().getValue1() + std::declval<FirstType>().getValue2());
        ValueType result; // 默认返回值

        // 折叠表达式：短路求值 + 条件执行
        ([&] {
            if (args.success()) {
                result = args.getValue1() + args.getValue2();
                return true; // 找到有效值，终止后续计算
            }
            return false;
        }() || ...); // 二元左折叠，利用 || 的短路特性[3,5](@ref)

        return result;
    }

    void test3() {
        const LazyData<int> lz1 = {
            []() { return 1; },
            []() { return 1; },
            []() { return false; },
        };
        const LazyData<int> lz2 = {
            []() { return 2; },
            []() { return 3; },
            []() { return false; },
        };
        const LazyData2<int> lz3 = {
            []() { return 7; },
            []() { return 3; },
            []() { return true; },
        };
        const int num = addLazyData2(lz1, lz2, lz3);
        std::cout << "test3:" << num << std::endl;
    }
}


int main() {
    // test3();
    // live_data::test1();
    testMutableLiveData();
    // shared_ptr_test::test();

    return 0;
}
