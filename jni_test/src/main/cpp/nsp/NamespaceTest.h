//
// Created by eriche on 2025/3/2.
//

#pragma once

//namespace first::second {
//
//
//    namespace test1 {
//        int add1(int a, int b);
//    }
//
//
//    namespace test2 {
//        int add2(int a, int b);
//    }
//
//}
//
//
//class IBaseTestTemplate {
//
//public:
//    virtual ~IBaseTestTemplate() = default;
//
//};
//
//template<class T>
//class ITestTemplate : public IBaseTestTemplate {
//
//public:
//    virtual ~ITestTemplate() = default;
//
//    virtual void onTemplate(T t) = 0;
//
//};
//
//class ITestTemplateFactory {
//
//public:
//    virtual ~ITestTemplateFactory() = default;
//
//    virtual std::shared_ptr<IBaseTestTemplate> createTestTemplate() = 0;
//
//};


//struct TestStruct1 {
//    int a;
//};
//
//struct TestStruct2 {
//    TestStruct1 struct1;
//
//    TestStruct1 getTestStruct11();
//
//    std::vector<const TestStruct1> getTestStruct1List();
//};