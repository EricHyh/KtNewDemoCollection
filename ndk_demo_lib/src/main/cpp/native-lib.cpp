#include <jni.h>
#include <string>
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