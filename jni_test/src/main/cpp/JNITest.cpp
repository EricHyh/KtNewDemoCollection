//
// Created by eriche on 2024/12/20.
//

#include <jni.h>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include <shared_mutex>
#include "TestUtil.h"
#include "JNIContext.h"
#include "observer/ObserverManager.h"


class Empty1 {
private:
    int a;

};

class Empty2 {

public:
    void m1() {}

    virtual void m2() {}
};
//
//struct TestData {
//    int num;
//
//    TestData(const int& num) : num(num) {}
//};
//
//struct TestData2 {
//    const int num;
//
//    TestData2(const int& num) : num(num) {}
//};
//
//
//void RunTask(std::function<void()> task) {
//    // 执行task
//    task();
//}
//
//void RunAsyncTask(std::function<void()> task) {
//    // 异步执行 task
//    std::thread(task).detach();
//
//    RunTask(nullptr);
//}

//
//struct TestData {
//    std::string name;
//};
//
//class TestMultiThreadEnv {
//
//public:
//
//    void UpDate(const TestData& newData) {
//        std::lock_guard<std::mutex> lock(m_dataLock);
//        this->m_data = newData;
//    }
//
//    const TestData& GetData() const {
//        std::lock_guard<std::mutex> lock(m_dataLock);
//        return m_data;
//    }
//
//private:
//    mutable std::mutex m_dataLock;
//    TestData m_data;
//};
//
//void RunTest() {
//    TestMultiThreadEnv env;
//    const TestData& data = env.GetData();
//    data.name;
//}


struct TestData {
    std::string name;
};

class TestMultiThreadEnv {

public:

    void UpDate(const TestData& newData) {
        auto newObj = std::make_shared<TestData>(newData); // 创建新对象
        std::unique_lock lock(m_mutex);
        // *this->m_data = newData; // 避免使用这种方式
        m_data.swap(newObj); // 原子替换指针
    }

    std::shared_ptr<const TestData> GetData() const {
        std::shared_lock lock(m_mutex);
        return m_data;   // 返回当前快照
    }

private:
    mutable std::shared_mutex m_mutex;
    std::shared_ptr<TestData> m_data = std::make_shared<TestData>(); // 初始化
};

void RunTest() {
    TestMultiThreadEnv env;
    if(auto data = env.GetData()) { // 正确检查并访问
        data->name;
    }
}


extern "C" JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIContext::SetJVM(vm);
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    Empty1 empty1;
    Empty2 empty2;
    const std::string &string1 = std::to_string(sizeof(empty1));
    const std::string &string2 = std::to_string(sizeof(empty2));
    const std::string &string3 = std::to_string(sizeof(int));
    LOGI("JNI_OnLoad %s, %s, %s", string1.c_str(), string2.c_str(), string3.c_str());
    RunTest();
    return JNI_VERSION_1_6;
}


