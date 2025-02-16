//
// Created by eriche on 2024/12/20.
//

#include <jni.h>
#include <string>
#include "TestUtil.h"
#include "JNIContext.h"
#include "observer/ObserverManager.h"


class Empty1 {
private:
    int a;

};

class Empty2 {

public:
    void m1() {}

    virtual void m2() {}
};

extern "C" JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIContext::SetJVM(vm);
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    Empty1 empty1;
    Empty2 empty2;
    const std::string &string1 = std::to_string(sizeof(empty1));
    const std::string &string2 = std::to_string(sizeof(empty2));
    const std::string &string3 = std::to_string(sizeof(int));
    LOGI("JNI_OnLoad %s, %s, %s", string1.c_str(), string2.c_str(), string3.c_str());
    return JNI_VERSION_1_6;
}


