//
// Created by eriche on 2025/2/16.
//

#include "JNITestEntrance.h"
#include "observer/ObserverManager.h"
#include "TestUtil.h"

#include <string>
#include <memory>
#include <unordered_map>


namespace {

    std::unordered_map<int, std::shared_ptr<TestObserver>> s_observers;

}

void JNITestEntrance::testAddObserver(int id) {
    const std::shared_ptr<TestObserver> &ptr = std::make_shared<TestObserver>([=](const int &data) {
        LOGI("JNI_OnLoad id=%s, data=%s", std::to_string(id).c_str(), std::to_string(data).c_str());
    });
    s_observers[id] = ptr;
    ObserverManager::addObserver(ptr);
}

void JNITestEntrance::testRemoveObserver(int id) {
    std::shared_ptr<TestObserver> &ptr = s_observers[id];
    if (ptr) {
        ObserverManager::removeObserver(ptr);
    }
}
