//
// Created by eriche on 2025/2/16.
//

#include "JNITestEntrance.h"
#include "observer/ObserverManager.h"
#include "TestUtil.h"

#include <string>
#include <memory>
#include <unordered_map>

class AnonymousObserver : public ITestObserver2 {
public:
    explicit AnonymousObserver(const int &id) : id(id) {}
    void onCall(const int& data) override {
        // 实现 onCall 方法
        LOGI("AnonymousObserver onCall id=%s, data=%s", std::to_string(id).c_str(), std::to_string(data).c_str());
    }

private:
    int id;
};


namespace {

    std::unordered_map<int, std::shared_ptr<TestObserver>> s_observers;
    std::unordered_map<int, std::shared_ptr<ITestObserver2>> s_observer2s;

}

void JNITestEntrance::testAddObserver(int id) {
//    const std::shared_ptr<TestObserver> &ptr1 = std::make_shared<TestObserver>([=](const int &data) {
//        LOGI("JNI_OnLoad id=%s, data=%s", std::to_string(id).c_str(), std::to_string(data).c_str());
//    });
//    s_observers[id] = ptr1;
//    ObserverManager::addObserver(ptr1);

    const std::shared_ptr<ITestObserver2> &ptr2 = std::shared_ptr<ITestObserver2>(new AnonymousObserver(id));
    s_observer2s[id] = ptr2;
    ObserverManager::addObserver2(ptr2);
}

void JNITestEntrance::testRemoveObserver(int id) {
//    std::shared_ptr<TestObserver> &ptr1 = s_observers[id];
//    if (ptr1) {
//        ObserverManager::removeObserver(ptr1);
//    }

    std::shared_ptr<ITestObserver2> &ptr2 = s_observer2s[id];
    if (ptr2) {
        ObserverManager::removeObserver2(ptr2);
    }
}
