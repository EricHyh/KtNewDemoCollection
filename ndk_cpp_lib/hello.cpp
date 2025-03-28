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
//#include "keyword/const_template_test.cpp"


#include <mutex>
#include <shared_mutex>



namespace{

    //const std::shared_mutex& g_mutex = std::shared_mutex();

}


int main()
{
    std::shared_mutex mutex1;
    std::mutex mutex2;
    // Circle c(3);
    // // cout<<"Area="<<c.Area()<<endl;
    // cout << "Area=" << 3.14 << endl;
    // printf("Hellow!\n");
    // string test = Test::getString();
    // //printf(test.c_str());
    // reference_test::test();
    //const_template_test::test();

    // std::shared_lock<std::shared_mutex> lock1(mutex);
    // printf("after lock1\n");

    // std::shared_lock<std::shared_mutex> lock2(mutex);
    // printf("after lock2\n");

    // std::unique_lock<std::shared_mutex> lock(mutex);
    // printf("after lock3\n");

    std::lock_guard<std::mutex> lock1(mutex2);
    printf("after lock1\n");
    std::lock_guard<std::mutex> lock2(mutex2);
    printf("after lock2\n");

    return 0;
}