//
// Created by eriche on 2025/2/16.
//

#include "ObserverManager.h"

IObserverManager *ObserverManager::s_manager = nullptr;

void ObserverManager::init(IObserverManager *manager) {
    ObserverManager::s_manager = manager;
}

void ObserverManager::addObserver(std::shared_ptr <TestObserver> observer) {
    s_manager->addObserver(observer);
}

void ObserverManager::removeObserver(std::shared_ptr <TestObserver> observer) {
    s_manager->removeObserver(observer);
}

void ObserverManager::addObserver2(std::shared_ptr <ITestObserver2> observer) {
    s_manager->addObserver2(observer);
}

void ObserverManager::removeObserver2(std::shared_ptr <ITestObserver2> observer) {
    s_manager->removeObserver2(observer);
}
