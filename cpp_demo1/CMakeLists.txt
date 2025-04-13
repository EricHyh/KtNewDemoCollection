cmake_minimum_required(VERSION 3.20.0)

project(CPP_Demo1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



file(GLOB_RECURSE MAIN_H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main/*.h")
file(GLOB_RECURSE MAIN_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp")
file(GLOB_RECURSE MAIN_CC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main/*.cc")

file(GLOB_RECURSE SRC_H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SRC_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRC_CC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")


add_executable(${PROJECT_NAME}

        ${MAIN_H_FILES}
        ${MAIN_CPP_FILES}
        ${MAIN_CC_FILES}

        ${SRC_H_FILES}
        ${SRC_CPP_FILES}
        ${SRC_CC_FILES}
)


target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 禁用优化并关闭 RVO/NRVO
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "GCC or Clang compiler detected")
        target_compile_options(${PROJECT_NAME} PRIVATE -O0 -fno-elide-constructors -fno-optimize-sibling-calls  -fno-inline -fno-inline-functions -fno-inline-functions-called-once -fno-inline-small-functions)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(STATUS "MSVC compiler detected")
        target_compile_options(${PROJECT_NAME} PRIVATE /Od /Ob0 /Oi- /Oy-)
else()
        message(STATUS "Unknown compiler detected")
        target_compile_options(${PROJECT_NAME} PRIVATE -O0 -fno-elide-constructors -fno-optimize-sibling-calls  -fno-inline -fno-inline-functions -fno-inline-functions-called-once -fno-inline-small-functions)
        # Add any other compiler-specific options here
endif()

if (MSVC)
    message(STATUS "MSVC compiler detected")
    target_compile_options(${PROJECT_NAME} PRIVATE /Od)
endif()