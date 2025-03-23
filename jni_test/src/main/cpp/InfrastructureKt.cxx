#include "JNIContext.h"
#include "swig_gen_common.h"


extern "C"
JNIEXPORT jlong JNICALL
Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1NewSwigDirectorWrapper(
        JNIEnv *env, jclass clazz, jlong c_ptr, jobject wrapper) {
    jlong jresult = 0;
    SwigDirectorWrapper *arg1 = 0;
    std::unique_ptr<SwigDirectorWrapper> rvrdeleter1;
    SwigDirectorWrapper *result = 0;

    arg1 = *(SwigDirectorWrapper **) &c_ptr;
    if (!arg1) {
        SWIG_JavaThrowException(env, SWIG_JavaNullPointerException, "SwigDirectorWrapper && is null");
        return 0;
    }
    rvrdeleter1.reset(arg1);
    result = (SwigDirectorWrapper *) new SwigDirectorWrapper((SwigDirectorWrapper &&) *arg1);
    *(SwigDirectorWrapper **) &jresult = result;
    return jresult;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1DeleteSwigDirectorWrapper(
        JNIEnv *env, jclass clazz, jlong c_ptr) {
SwigDirectorWrapper *arg1;

arg1 = *(SwigDirectorWrapper **) &c_ptr;
delete arg1;
}

extern "C"
JNIEXPORT jboolean JNICALL
        Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1IsJObject(
        JNIEnv *env, jclass clazz, jlong c_ptr, jobject wrapper) {
jboolean jresult;
SwigDirectorWrapper *arg1;
bool result;

arg1 = *(SwigDirectorWrapper **) &c_ptr;
result = (bool) ((SwigDirectorWrapper const *) arg1)->IsJObject();
jresult = (jboolean) result;
return jresult;
}

extern "C"
JNIEXPORT jboolean JNICALL
        Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1IsCPtr(
        JNIEnv *env, jclass clazz, jlong c_ptr, jobject wrapper) {
jboolean jresult;
SwigDirectorWrapper *arg1;
bool result;

arg1 = *(SwigDirectorWrapper **) &c_ptr;
result = (bool) ((SwigDirectorWrapper const *) arg1)->IsCPtr();
jresult = (jboolean) result;
return jresult;
}

extern "C"
JNIEXPORT jobject JNICALL
        Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1GetJObject(
        JNIEnv *env, jclass clazz, jlong c_ptr, jobject wrapper) {
SwigDirectorWrapper *wrapperPtr = *(SwigDirectorWrapper **) &c_ptr;
jobject result = ((SwigDirectorWrapper const *) wrapperPtr)->GetJObject();
return result;
}

extern "C"
JNIEXPORT jlong JNICALL
        Java_com_hyh_jnitest_baisc_infrastructure_FINSwigDirectorWrapper__1GetCPtr(
        JNIEnv *env, jclass clazz, jlong c_ptr, jobject wrapper) {
SwigDirectorWrapper *wrapperPtr;
wrapperPtr = *(SwigDirectorWrapper **) &c_ptr;
jlong result = ((SwigDirectorWrapper const *) wrapperPtr)->GetCPtr();
return result;
}
