#include <jni.h>
#include <string>
#include <chrono>
#include <vector>
#include <locale>
#include <android/log.h>
#include "JNIContext.h"

//extern "C" JNIEXPORT jstring
//JNICALL
//stringFromJNI(JNIEnv *env, jobject thiz)
//{
//    std::string hello =Test::getString();
//    return env->NewStringUTF(hello.c_str());
//}
//
//static const JNINativeMethod nativeMethods[] = {
//        // Java中的函数名, 函数签名信息, native的函数指针
//        {"stringFromJNI", "()Ljava/lang/String;", (void *) (stringFromJNI)},
//};
//
//
//jint RegisterNatives(JNIEnv *env)
//{
//    jclass clazz = env->FindClass("com/example/ndk_demo_lib/TestJNI");
//    if (clazz == NULL)
//    {
//        return JNI_ERR;
//    }
//    return env->RegisterNatives(
//            clazz,
//            nativeMethods,
//            sizeof(nativeMethods) / sizeof(nativeMethods[0])
//    );
//}

extern "C" JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIContext::SetJVM(vm);
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_1demo_1lib_TestJNI_add(JNIEnv *env, jobject thiz) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_1demo_1lib_TestJNI_test_1java_1add(JNIEnv *env, jobject thiz, jint num) {
    jclass testJNI_class = env->GetObjectClass(thiz);
    jmethodID java_add_methodId = env->GetMethodID(testJNI_class, "java_add", "()V");

    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < num; ++i) {
        env->CallVoidMethod(thiz, java_add_methodId);
    }

    auto end = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    __android_log_print(ANDROID_LOG_INFO, "TestJNI", "test c_t_j %d, use time = %s", num,
                        std::to_string(duration.count()).c_str());

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_1demo_1lib_TestJNI_test_1sort(JNIEnv *env, jobject thiz) {
    std::vector<std::wstring> strings = {L"苹果", L"香蕉", L"橙子", L"葡萄", L"b", L"a"};// pg、x、c、pt

    // 设置区域设置为中文
    std::locale chinaLocale("");

    // 使用标准排序，结合区域设置
    std::sort(strings.begin(), strings.end(), [&chinaLocale](const std::wstring& a, const std::wstring& b) {
        return std::use_facet<std::collate<wchar_t>>(chinaLocale).compare(a.data(), a.data() + a.size(), b.data(), b.data() + b.size()) < 0;
    });

    // 输出排序后的结果
    for (const auto &str: strings) {
        __android_log_print(ANDROID_LOG_INFO, "TestJNI", "%ls", str.c_str());
    }

}