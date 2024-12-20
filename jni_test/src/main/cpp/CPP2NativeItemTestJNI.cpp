//
// Created by eriche on 2024/12/20.
//
#include <jni.h>
#include <string>
#include "model/CPP2NativeItemTest.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_createCPP2NativeItemTest(JNIEnv *env, jobject thiz, jint index) {
    jlong jresult = 0;
    CPP2NativeItemTest *item = new CPP2NativeItemTest(index);
    *(CPP2NativeItemTest **) &jresult = item;
    return jresult;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_releaseCPP2NativeItemTest(JNIEnv *env, jobject thiz, jlong ptr) {
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    delete item;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getId(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getId();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getTitle(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getTitle();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getEnvelopePic(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getEnvelopePic();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getDesc(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getDesc();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getNiceDate(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getNiceDate();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_CPP2NativeItemTestJNI_getAuthor(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    CPP2NativeItemTest *item = nullptr;
    item = (CPP2NativeItemTest *) ptr;
    const std::string &result = item->getAuthor();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}