//
// Created by eriche on 2024/12/20.
//
#include <jni.h>
#include <string>
#include "model/Native2CPPItemTest.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_createNative2CPPItemTest(JNIEnv *env, jobject thiz, jint index) {
    jlong jresult = 0;
    Native2CPPItemTest *item = new Native2CPPItemTest(index);
    *(Native2CPPItemTest **) &jresult = item;
    return jresult;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_releaseNative2CPPItemTest(JNIEnv *env, jobject thiz, jlong ptr) {
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    delete item;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getId(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getId();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getTitle(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getTitle();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getEnvelopePic(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getEnvelopePic();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getDesc(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getDesc();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getNiceDate(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getNiceDate();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1test_model_Native2CPPItemTestJNI_getAuthor(JNIEnv *env, jobject thiz, jlong ptr) {
    jstring jresult = 0;
    Native2CPPItemTest *item = nullptr;
    item = (Native2CPPItemTest *) ptr;
    const std::string &result = item->getAuthor();
    jresult = env->NewStringUTF((&result)->c_str());
    return jresult;
}