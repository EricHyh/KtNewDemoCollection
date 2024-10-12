//
// Created by eriche on 2024/8/24.
//

#include "TestSwig.h"
#include "thread"

TestSwig::TestSwig() : r(100) {

}

TestSwig::TestSwig(double R) : r(R) {

}

double TestSwig::Area() const {
    return this->r * this->r;
}

void TestSwig::test1(const TestSwigData &data) const {

}

void TestSwig::test2(const TestCallback& callback) const {
    callback(TestSwigData());
}

void TestSwig::test3(const TestCallback3 &callback) const {

}

void TestSwig::test4(const TestCallback4<int> &callback) const {
    std::thread([callback]{
        std::this_thread::sleep_for(std::chrono::seconds(3));
        callback(100);
    }).detach();
}

//void TestSwig::test44(const TestCallback4<double> &callback) const {
//
//}


// 实现适配器函数
//void testCallbackAdapter(TestSwig* self, TestCallbackWrapper* wrapper) {
//    if (self && wrapper) {
//        self->test2([wrapper](const TestSwigData& value) {
//            wrapper->call(value);
//        });
//    }
//}
