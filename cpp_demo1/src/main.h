//
// Created by eriche on 2025/4/12.
//

#pragma once

#include <functional>
#include <thread>
#include <unistd.h>
#include <iostream>

#include "Reference/ReferenceTest2.h"

namespace
{
    void RunAsyncTask() {
        int num = 42;  // 定义一个整数变量

        std::thread([&num]() {
            std::this_thread::sleep_for(std::chrono::seconds(3)); 
            printf("Value: %d\n", num); 
        }).detach(); 
        
    }
} // namespace



