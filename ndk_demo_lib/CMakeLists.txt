# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

#cmake_minimum_required(VERSION 3.4.1)
#cmake_minimum_required(VERSION 3.20.0)
cmake_minimum_required(VERSION 3.10.2)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

aux_source_directory(../ndk_cpp_lib/. SRC_LIST) # 搜索当前目录下的所有.cpp文件



file(GLOB_RECURSE ANDROID_SDK_CXX_FILES "./main/cpp/*.cxx")
file(GLOB_RECURSE ANDROID_SDK_CPP_FILES "./main/cpp/*.cpp")

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${ANDROID_SDK_CXX_FILES}
        ${ANDROID_SDK_CPP_FILES}

        src/main/cpp/date/chrono_io.h
        src/main/cpp/date/date.h
        src/main/cpp/date/islamic.h
        src/main/cpp/date/iso_week.h
        src/main/cpp/date/julian.h
        src/main/cpp/date/solar_hijri.h
        src/main/cpp/date/tz.h
        src/main/cpp/date/tz_private.h
        src/main/cpp/date/tz.cpp



        src/main/cpp/swig/SwigCallback_wrap.cxx
        src/main/cpp/swig/SwigCallbackData.cpp
        src/main/cpp/swig/TestSwigCallback.cpp
        src/main/cpp/swig/BaseTest.h

        src/main/cpp/JNIContext.cpp
        src/main/cpp/native-lib.cpp

        ${SRC_LIST}
)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )


# 为这个目标添加编译定义
target_compile_definitions(native-lib PRIVATE USE_OS_TZDB=1 BUILD_TZ_LIB)


set_target_properties(native-lib PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)
