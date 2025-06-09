//
// Created by eriche on 2025/4/12.
//

#include "main.h"
#include "BizModel/TestBizModel.h"


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


int main() {
    std::cout << "Hello, World!" << std::endl; // 输出 "Hello, World!";

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


    CopyTest* const test_ptr = &test1;

    // test_ref = test2;
    test2 = test3;


    test1.Print();
    test_ref.Print();

    return 0;
}
