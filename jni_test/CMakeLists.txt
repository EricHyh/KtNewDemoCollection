cmake_minimum_required(VERSION 3.10.2)

project("JNITest")




file(GLOB_RECURSE ANDROID_SDK_CXX_FILES "src/main/cpp/*.cxx")
file(GLOB_RECURSE ANDROID_SDK_CPP_FILES "src/main/cpp/*.cpp")

file(GLOB_RECURSE SWIG_CXX_FILES "src/main/swig/cpp/*.cxx")
file(GLOB_RECURSE SWIG_CPP_FILES "src/main/swig/cpp/*.cpp")

add_library(${PROJECT_NAME} SHARED
        ${ANDROID_SDK_CXX_FILES}
        ${ANDROID_SDK_CPP_FILES}

        ${SWIG_CXX_FILES}
        ${SWIG_CPP_FILES}
)

target_link_libraries(${PROJECT_NAME}
        android
        log
)

target_include_directories(${PROJECT_NAME}
        PRIVATE src/main/cpp
        PRIVATE src/main/swig/cpp
        PRIVATE src/main/swig/cpp/test
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)