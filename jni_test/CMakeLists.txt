cmake_minimum_required(VERSION 3.10.2)

project("JNITest")


file(GLOB_RECURSE ANDROID_SDK_CXX_FILES "src/main/cpp/*.cxx")
file(GLOB_RECURSE ANDROID_SDK_CPP_FILES "src/main/cpp/*.cpp")

add_library(${PROJECT_NAME} SHARED
        ${ANDROID_SDK_CXX_FILES}
        ${ANDROID_SDK_CPP_FILES}
)

target_link_libraries(${PROJECT_NAME}
        android
        log
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)