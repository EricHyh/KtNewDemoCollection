//
// Created by eriche on 2025/2/16.
//

#include "ObserverManager.h"
#include "../TestUtil.h"
#include "field/MediatorLiveData.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <set>
#include <vector>
#include <codecvt>
#include <locale>
#include <algorithm>
#include <memory>


namespace {

    struct TestString {
        std::string orderId{};
        uint64_t orderIdHash = 0;
        std::string localId{};
        uint64_t localIdHash = 0;

        TestString(
                std::string orderId,
                std::string localId
        ) : orderId(std::move(orderId)), localId(std::move(localId)) {
            orderIdHash = std::hash<std::string>()(this->orderId);
            localIdHash = std::hash<std::string>()(this->localId);
        }

        // ==
        bool operator==(const TestString& other) const {
            if(!orderId.empty() && !other.orderId.empty() ){
                return orderId == other.orderId ;
            }
            return localId == other.localId ;
//            if (orderIdHash != 0 && other.orderIdHash != 0) {
//                return orderIdHash == other.orderIdHash && orderId == other.orderId;
//            }
//            return localIdHash ==other.localIdHash && localId == other.localId;
        }

        // !=
        bool operator!=(const TestString& other) const {
            return !(*this == other);
        }
    };
}
// hash function for TestString
namespace std {
    template<>
    struct hash<TestString> {
        size_t operator()(const TestString& ts) const {
//            if(ts.localIdHash != 0) {
//                return ts.localIdHash;
//            }
//            return ts.orderIdHash;
            if (!ts.localId.empty()) {
                return std::hash<std::string>()(ts.localId);
            }
            return std::hash<std::string>()(ts.orderId);
        }
    };
}

namespace {

// 生成唯一的orderId（20个大写字母+数字）FS1B6F676F26E9E000
    std::string generateUniqueOrderId(std::set < std::string > &existingIds) {
        const std::string charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static std::mt19937 rng(std::time(nullptr));
        std::uniform_int_distribution<> dist(0, charSet.size() - 1);

        std::string result;
        do {
            result.clear();
            for (int i = 0; i < 20; ++i) {
                result += charSet[dist(rng)];
            }
        } while (existingIds.find(result) != existingIds.end());

        existingIds.insert(result);
        return result;
    }

    // 生成唯一的text（7个小写字母）
    std::string generateUniqueText(std::set < std::string > &existingTexts) {
        const std::string charSet = "abcdefghijklmnopqrstuvwxyz";
        static std::mt19937 rng(std::time(nullptr));
        std::uniform_int_distribution<> dist(0, charSet.size() - 1);

        std::string result;
        do {
            result.clear();
            for (int i = 0; i < 32; ++i) {
                result += charSet[dist(rng)];
            }
        } while (existingTexts.find(result) != existingTexts.end());

        existingTexts.insert(result);
        return result;
    }

};

namespace {
    void test1() {
        std::string localId = "FIN|Android|78911001010|1234567890|100";
        std::vector<TestString> vec;
        for (int i = 0; i < 10000; ++i) {
            TestString ts(std::to_string(i), localId);
            vec.push_back(ts);
        }
        std::unordered_map<TestString, std::shared_ptr<uint64_t>> map;
        for (int i = 0; i < vec.size(); ++i) {
            map[vec[i]] = std::make_shared<uint64_t>(i);
        }
        // 执行耗时测试
        // 开始时间 ms
        std::vector<std::shared_ptr<uint64_t>> results;
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& i: vec) {
            auto it = map.find(i);
            if (it != map.end()) {
                // 找到对应的值
                results.emplace_back(it->second);
            }
        }
        // 结束时间 ms
        auto end = std::chrono::high_resolution_clock::now();
        // 计算耗时
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        LOGI("TestString耗时 - 1: %lld ms", duration);
    }

    void test2() {
        std::string localId = "FIN|Android|78911001010|1234567890|100";
        std::vector<TestString> vec;
        for (int i = 0; i < 10000; ++i) {
            TestString ts(std::to_string(i), localId);
            vec.push_back(ts);
        }
        std::unordered_map<TestString, std::shared_ptr<uint64_t>> map;
        for (int i = 0; i < vec.size(); ++i) {
            map[vec[i]] = std::make_shared<uint64_t>(i);
        }
        // 执行耗时测试
        // 开始时间 ms
        std::vector<std::shared_ptr<uint64_t>> results;
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& item: map){
            results.emplace_back(item.second);
        }
        // 结束时间 ms
        auto end = std::chrono::high_resolution_clock::now();
        // 计算耗时
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        LOGI("TestString耗时 - 2: %lld ms", duration);
    }

    void test3() {
        std::vector<TestString> vec;
        std::set < std::string > existingIds;
        for (int i = 0; i < 10000; ++i) {
            TestString ts(generateUniqueOrderId(existingIds), generateUniqueText(existingIds));
            vec.push_back(ts);
        }
        std::unordered_map<TestString, std::shared_ptr<uint64_t>> map;
        for (int i = 0; i < vec.size(); ++i) {
            map[vec[i]] = std::make_shared<uint64_t>(i);
        }
        // 执行耗时测试
        // 开始时间 ms
        std::vector<std::shared_ptr<uint64_t>> results;
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& i: vec) {
            auto it = map.find(i);
            if (it != map.end()) {
                // 找到对应的值
                results.emplace_back(it->second);
            }
        }
        // 结束时间 ms
        auto end = std::chrono::high_resolution_clock::now();
        // 计算耗时
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        LOGI("TestString耗时 - 3: %lld ms", duration);
    }
}


IObserverManager* ObserverManager::s_manager = nullptr;

void ObserverManager::init(IObserverManager* manager) {
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

int64_t ObserverManager::add2(int64_t& a, int64_t& b) {
    return s_manager->add2(a, b);
}

long long ObserverManager::add22(const long long& a, const long long& b) {
    return s_manager->add22(a, b);
}

std::optional<int64_t> ObserverManager::add3(std::optional<int64_t> a, std::optional<int64_t> b) {
    return s_manager->add3(a, b);
}

std::optional<int64_t> ObserverManager::add33(const std::optional<int64_t>& a, const std::optional<int64_t>& b) {
    return s_manager->add33(a, b);
}

void ObserverManager::byteTest1(std::vector<uint8_t> byteArray) {
    for (unsigned char i: byteArray) {
        LOGI("ObserverManager byteTest1 %s", std::to_string(i).c_str());
    }
    s_manager->byteTest1(byteArray);
}

void ObserverManager::byteTest2(const std::vector<uint8_t>& byteArray) {
    for (unsigned char i: byteArray) {
        LOGI("ObserverManager byteTest2 %s", std::to_string(i).c_str());
    }
    s_manager->byteTest2(byteArray);
}

std::vector<uint8_t> ObserverManager::byteTest3() {
//    testGetJavaObj();
    test1();
    test2();
    test3();

    return s_manager->byteTest3();
}

std::shared_ptr<ITestObserver2> ObserverManager::getObserver2() {
    return s_manager->getObserver2();
}

TestEnum1 ObserverManager::optionalEnum33() {
    return s_manager->optionalEnum33();
}
