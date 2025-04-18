#include <stdio.h>
#include <string>
#include <iostream>
#include "Circle.h"
#include "pointer/shared_ptr_test.cpp"
#include "pointer/weak_ptr_test.cpp"
#include "pointer/unique_ptr_test.cpp"
#include "reference/reference_test.cpp"
#include "keyword/static_test.cpp"
#include "keyword/const_test.cpp"
// #include "keyword/const_template_test.cpp"

#include <mutex>
#include <shared_mutex>
#include <memory>
#include <functional>

namespace
{

    // const std::shared_mutex& g_mutex = std::shared_mutex();

}

class TestData
{
};

// class CFINTimer
// {
// public:
//     ~CFINTimer()
//     {
//         printf("~CFINTimer\n");
//     }
//     void good()
//     {
//         printf("good\n");
//     }

//     TestData getData()
//     {
//         return m_data;
//     }

// private:
//     TestData m_data;
// };

// class CFINTimerWrapper
// {

// public:
//     std::shared_ptr<CFINTimer> m_timer;
//     ~CFINTimerWrapper()
//     {
//         // if (auto sharedPtr = m_timer.lock()) {
//         //     sharedPtr->good();
//         // }
//         printf("~CFINTimerWrapper\n");
//     }
// };



class SharedPtrData{
public:
    SharedPtrData() = default;

    ~SharedPtrData() = default;

    SharedPtrData(SharedPtrData&& other){
        cout << "SharedPtrData 移动构造" << endl;
    }
    
    SharedPtrData &operator=(SharedPtrData&& other){
        cout << "SharedPtrData 移动赋值" << endl;
    }
};


int main()
{


    {
        auto func1 = [data = std::make_shared<SharedPtrData>()](){
            cout << "func1" << endl;
        };
    
        auto func2 = [func1 = std::move(func1)](){
            func1();
            cout << "func2" << endl;
        };
    
        func2();
    }



    // std::shared_mutex mutex1;
    // std::recursive_mutex mutex1;
    // std::mutex mutex2;
    // Circle c(3);
    // // cout<<"Area="<<c.Area()<<endl;
    // cout << "Area=" << 3.14 << endl;
    // printf("Hellow!\n");
    // string test = Test::getString();
    // //printf(test.c_str());
    // reference_test::test();
    // const_template_test::test();

    // std::shared_lock<std::shared_mutex> lock1(mutex);
    // printf("after lock1\n");

    // std::shared_lock<std::shared_mutex> lock2(mutex);
    // printf("after lock2\n");

    // std::unique_lock<std::shared_mutex> lock(mutex);
    // printf("after lock3\n");

    // std::lock_guard<std::mutex> lock1(mutex2);
    // printf("after lock1\n");

    // {
    //     CFINTimerWrapper timerWrapper;
    //     timerWrapper.m_timer = std::make_shared<CFINTimer>();
    // }

    // printf("after lock2\n");

    // CFINTimer timer;
    // TestData data = timer.getData();
    // const TestData& data = timer.getData();

    return 0;
}