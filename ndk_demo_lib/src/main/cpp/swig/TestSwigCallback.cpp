


#include "TestSwigCallback.h"
#include <memory>
#include <thread>
#include <cstdlib>
#include <future>
#include <string>
#include "BaseTest.h"
#include "../date/date.h"
#include "../date/tz.h"

void TestSwigCallback::setCallback1(SwigCallback *swigCallback) {

    std::thread t([swigCallback] {
//        sleep(20);
        std::shared_ptr<SwigCallbackData> sp = std::make_shared<SwigCallbackData>(11);
        swigCallback->onTest1(sp);

        swigCallback->onTest2(SwigCallbackData(12));
        swigCallback->onTest4(12);
    });

    t.join();
}

void TestSwigCallback::setCallback2(std::shared_ptr<SwigCallback> swigCallback) {
    std::shared_ptr<SwigCallbackData> sp = std::make_shared<SwigCallbackData>(100);
    swigCallback->onTest1(sp);

    swigCallback->onTest2(SwigCallbackData(1000));
}

void TestSwigCallback::setCallback3(int num, std::shared_ptr<SwigCallback> swigCallback) {


//    std::thread t1([num, swigCallback]{
//        sleep(10);
//        std::shared_ptr<SwigCallbackData> sp = std::make_shared<SwigCallbackData>(100*num);
//        swigCallback->onTest1(sp);
//    });
//    t1.detach();
//
//    std::thread t2([num, swigCallback]{
//        sleep(12);
//        swigCallback->onTest2(SwigCallbackData(1000*num));
//    });
//    t2.detach();

    std::thread t3([num, swigCallback] {
//        sleep(12);
        //void(const SwigCallbackData &data)
        swigCallback->onTest5(10, "10", [](const SwigCallbackData &data) {
            __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "from java %d", data.a);
        }, 10);
    });
    t3.detach();
}


void TestSwigCallback::setCallback4(SwigCallbackFunction swigCallback) {
    std::thread t([swigCallback] {
//        sleep(10);
        swigCallback(SwigCallbackData(1000));
    });

    t.join();

}


class ThreadGuard {
public:
    explicit ThreadGuard(std::thread &&t) : t_(std::move(t)) {}

    ~ThreadGuard() {
        if (t_.joinable()) {
            t_.join();
        }
    }

    ThreadGuard(ThreadGuard &&) = default;

    ThreadGuard &operator=(ThreadGuard &&) = default;

    ThreadGuard(const ThreadGuard &) = delete;

    ThreadGuard &operator=(const ThreadGuard &) = delete;

    std::thread t_;
};

void TestSwigCallback::setCallback5(SwigCallbackFunction1 swigCallback) {

//    __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "real setCallback5 1");
//
//    std::thread t([swigCallback]{
//        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "Thread started");
//        std::this_thread::sleep_for(std::chrono::seconds(5));
//        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "About to call swigCallback");
//        swigCallback(SwigCallbackData(8000));
//        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "Thread finished");
//    });
//
//    // 分离线程，让它在后台运行
//    t.detach();
//
//
//    __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "real setCallback5 2");


    __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "real setCallback5 1");

    // 使用 shared_ptr 来管理线程的生命周期
    auto thread_ptr = std::make_shared<std::thread>([swigCallback, thread_holder = std::weak_ptr<std::thread>()] {
        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "Thread started");
        std::this_thread::sleep_for(std::chrono::seconds(5));
        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "About to call swigCallback");
        swigCallback(SwigCallbackData(8000));
        __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "Thread finished");




        // 线程执行完毕后，释放自己的 shared_ptr
        if (auto holder = thread_holder.lock()) {
            holder->detach();
        }
    });

    // 创建管理线程
    std::thread manager_thread([thread_ptr]() {
        if (thread_ptr->joinable()) {
            thread_ptr->join();
            __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "Thread real finished");
        }
        // thread_ptr 会在这里自动释放
    });

    // 分离管理线程，让它在后台运行
    manager_thread.detach();

    __android_log_print(ANDROID_LOG_INFO, "SwigCallback", "real setCallback5 2");



    for (const auto &name: Base::getSubclassNames()) {
        std::cout << "Subclass: " << name << std::endl;
        __android_log_print(ANDROID_LOG_INFO, "Created instance", "Subclass %s", name.c_str());
        auto instance = Base::create(name);
        if (instance) {
            __android_log_print(ANDROID_LOG_INFO, "Created instance", "Subclass %s", instance->getName().c_str());
        }
    }


    using namespace date;
    using namespace std::chrono;

    {
        // 获取当前时区的当前时间
        auto now = make_zoned(current_zone(), system_clock::now());
        std::ostringstream oss1;
        oss1 << date::format("%Y-%m-%d %H:%M:%S %Z", now);
        std::string now_str1 = oss1.str();
        __android_log_print(ANDROID_LOG_INFO, "now1 ","now %s", now_str1.c_str());

                // 转换到不同时区
        auto nyc = locate_zone("America/New_York");
        auto ny_time = make_zoned(nyc, system_clock::now());
        std::cout << "New York time: " << ny_time << std::endl;
        std::ostringstream oss2;
        oss2 << date::format("%Y-%m-%d %H:%M:%S %Z", ny_time);
        std::string now_str2 = oss2.str();
        __android_log_print(ANDROID_LOG_INFO, "now2 ","now %s", now_str2.c_str());

        // 时区转换
        auto tokyo = locate_zone("Asia/Tokyo");
        auto tokyo_time = make_zoned(tokyo, ny_time);
        std::ostringstream oss3;
        oss3 << date::format("%Y-%m-%d %H:%M:%S %Z", tokyo_time);
        std::string now_str3 = oss3.str();
        __android_log_print(ANDROID_LOG_INFO, "now3 ","now %s", now_str3.c_str());
    }

    {
        // 格式化时间
        auto now = make_zoned(current_zone(), system_clock::now());
        std::cout << format("%F %T %Z", now) << std::endl;

        // 解析时间字符串
        std::string time_str = "2023-06-15 14:30:00";
        local_seconds tp;
        std::istringstream ss{time_str};
        ss >> parse("%F %T", tp);
        std::cout << "Parsed: " << tp << std::endl;
    }
}