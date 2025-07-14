//
// Created by eriche on 2025/2/16.
//

#include "ObserverManager.h"
#include "../TestUtil.h"
#include "field/MediatorLiveData.h"

IObserverManager *ObserverManager::s_manager = nullptr;

void ObserverManager::init(IObserverManager *manager) {
    ObserverManager::s_manager = manager;
}

void ObserverManager::addObserver(std::shared_ptr<TestObserver> observer) {
    s_manager->addObserver(observer);
}

void ObserverManager::removeObserver(std::shared_ptr<TestObserver> observer) {
    s_manager->removeObserver(observer);
}

void ObserverManager::addObserver2(std::shared_ptr<ITestObserver2> observer) {
    s_manager->addObserver2(observer);
}

void ObserverManager::removeObserver2(std::shared_ptr<ITestObserver2> observer) {
    s_manager->removeObserver2(observer);
}

int64_t ObserverManager::add1(int64_t a, int64_t b) {
    return s_manager->add1(a, b);
}

long long ObserverManager::add11(long long a, long long b) {
    return s_manager->add11(a, b);
}

int64_t ObserverManager::add2(int64_t &a, int64_t &b) {
    return s_manager->add2(a, b);
}

long long ObserverManager::add22(const long long &a, const long long &b) {
    return s_manager->add22(a, b);
}

std::optional<int64_t> ObserverManager::add3(std::optional<int64_t> a, std::optional<int64_t> b) {
    return s_manager->add3(a, b);
}

std::optional<int64_t> ObserverManager::add33(const std::optional<int64_t> &a, const std::optional<int64_t> &b) {
    return s_manager->add33(a, b);
}

void ObserverManager::byteTest1(std::vector<uint8_t> byteArray) {
    for (unsigned char i : byteArray) {
        LOGI("ObserverManager byteTest1 %s", std::to_string(i).c_str());
    }
    s_manager->byteTest1(byteArray);
}

void ObserverManager::byteTest2(const std::vector<uint8_t> &byteArray) {
    for (unsigned char i : byteArray) {
        LOGI("ObserverManager byteTest2 %s", std::to_string(i).c_str());
    }
    s_manager->byteTest2(byteArray);
}

std::vector<uint8_t> ObserverManager::byteTest3() {
    testGetJavaObj();
    return s_manager->byteTest3();
}

std::shared_ptr<ITestObserver2> ObserverManager::getObserver2() {
    return s_manager->getObserver2();
}

TestEnum1 ObserverManager::optionalEnum33() {
    return s_manager->optionalEnum33();
}
