//
// Created by eriche on 2025/2/16.
//

#pragma once

#include <functional>
#include <memory>

using TestObserver = std::function<void(const int &data)>;


class IObserverManager {

public:
    virtual ~IObserverManager() = default;

    virtual void addObserver(std::shared_ptr<TestObserver> observer) = 0;

    virtual void removeObserver(std::shared_ptr<TestObserver> observer) = 0;

};


class ObserverManager {

public:
    static void init(IObserverManager *manager);

    static void addObserver(std::shared_ptr<TestObserver> observer);

    static void removeObserver(std::shared_ptr<TestObserver> observer);


private:
    static IObserverManager* s_manager;

};

