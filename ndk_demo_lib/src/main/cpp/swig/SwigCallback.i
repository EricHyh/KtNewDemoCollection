%module SwigCallbackDemo


%include "common_swig_config.i"
%import "SwigCallbackxx.i"

%{
#include "SwigCallback.h"
#include "SwigCallbackData.h"
#include "TestSwigCallback.h"
#include "../JNIContext.h"
%}

//%import "SwigCallback.h"

%ignore InnerObserver2;
%ignore std::function<void(const SwigCallbackData&)>;

// 重新定义 InnerObserver2



// 支持 shared_ptr
//%include "std_shared_ptr.i"
//%include "std_unique_ptr.i"
%shared_ptr(SwigCallbackData)
%shared_ptr(SwigCallback)
%shared_ptr(FINFeatureFlagVariant)
%shared_ptr(InnerObserver)


%feature("director") SwigCallback;


//%typemap(in) std::shared_ptr<SwigCallback> {
//        std::shared_ptr<SwigCallback> *argp$argnum = *(std::shared_ptr<SwigCallback> **)&jarg$argnum;
//        if (argp$argnum) {
//            // 创建全局引用
//            jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
//            // 创建新的 shared_ptr，使用自定义删除器
//            $1 = std::shared_ptr<SwigCallback>(argp$argnum->get(), [globalRef](SwigCallback* ptr) {
//                JNIEnv *env = nullptr;
//                financial_sdk::JNIContext context(env);
//                env->DeleteGlobalRef(globalRef);
//            });
//        }
//}

%shared_ptr_param_wrapper(SwigCallback)

%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)

%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)

%shared_ptr_param_wrapper(InnerObserver)



// using SwigCallbackFunction = std::function<void(const SwigCallbackData &)>;
//%inline %{
//class SwigCallbackFunctionBridge {
//
//    public:
//    virtual ~SwigCallbackFunctionBridge() {}
//
//    virtual
//    void onCall(const SwigCallbackData &param) = 0;
//
//
//};
//%}
//
//
//%extend TestSwigCallback {
//
//    void setCallback4(std::shared_ptr<SwigCallbackFunctionBridge> swigCallback) {
//        self->setCallback4([swigCallback](const SwigCallbackData &param){
//            swigCallback->onCall(param);
//        });
//    }
//};
//
//
//%ignore TestSwigCallback::setCallback4;
//%shared_ptr(SwigCallbackFunctionBridge)
%function_type_bridge(SwigCallbackFunction,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_param_bridge(SwigCallbackFunction, TestSwigCallback, setCallback4);
%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)



//%shared_ptr(SwigCallbackFunction1Bridge)
%function_type_bridge(SwigCallbackFunction1, (const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_param_bridge(SwigCallbackFunction1, TestSwigCallback, setCallback5);
%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)


//%function_type_bridge(InnerObserver2, (const SwigCallbackData &data), (data));
//%function_param_bridge(InnerObserver2, SwigCallback, onTest5);
//%shared_ptr_param_wrapper(InnerObserver2Bridge)

//%function_param_bridge_with_pre_params(SwigCallbackFunction1, TestSwigCallback, setCallback5, (int param1), (param1));

//%feature("director") InnerObserver2Callback;
//%shared_ptr(InnerObserver2Callback)
//
//%inline %{
//
//class InnerObserver2Callback {
//
//    public:
//        virtual ~InnerObserver2Callback() = default;
//        virtual void onCall(const SwigCallbackData &data) = 0;
//
//};
//
////typedef InnerObserver2Callback* InnerObserver2;
//
//%};

%function_type_bridge(InnerObserver2,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);




// 为 InnerObserver2 创建一个 Java 回调接口
//%typemap(jni) InnerObserver2 "jobject"
//%typemap(jtype) InnerObserver2 "InnerObserver2Callback"
//%typemap(jstype) InnerObserver2 "InnerObserver2Bridge"
//%typemap(jtype) InnerObserver2 "long"
//%typemap(jstype) InnerObserver2 "long"
//%typemap(javain) InnerObserver2 "$javainput"
//%typemap(javain) InnerObserver2 "InnerObserver2Bridge.getCPtr($javainput)"

//%typemap(in) InnerObserver2 %{
//std::shared_ptr< InnerObserver2Bridge > *smartarg$argnum = *(std::shared_ptr<  InnerObserver2Bridge > **)&jarg$argnum;
//$1 = InnerObserver2Bridge::obtainOriginal(*smartarg$argnum);
//%}

//%typemap(out) InnerObserver2 %{
//$result = ptr_to_jlong($1);
//%}

//%typemap(directorin, descriptor="Lcom/example/InnerObserver2Callback;") InnerObserver2 %{
//$input = ptr_to_jlong11($1);
//%}

//%typemap(directorin, descriptor="Lcom/example/ndk_demo_lib1/InnerObserver2Bridge;") InnerObserver2 %{
//class LocalCallback : public InnerObserver2Bridge {
//public:
//        explicit LocalCallback(InnerObserver2 innerCallback) : m_original(std::move(innerCallback)) {}
//
//        void onCall(const SwigCallbackData &data) override {
//                if (m_original) {
//                        m_original(data);
//                }
//        }
//
//private:
//        InnerObserver2 m_original;
//};
//
//InnerObserver2Bridge *callback = new LocalCallback(innerCallback);
//
//*(std::shared_ptr<InnerObserver2Bridge> **) &$input = callback ? new std::shared_ptr<InnerObserver2Bridge>(callback) : 0;
//%}

%typemap(directorout) InnerObserver2 %{
$result = ($1_type)jlong_to_ptr12($input);
%}

%typemap(javadirectorin) InnerObserver2 %{
        ($jniinput == 0) ? null : new InnerObserver2Bridge($jniinput, true)%}

//%typemap(javain) InnerObserver2 "InnerObserver2Callback.getCPtr($javainput)"

//%typemap(javadirectorin) InnerObserver2 "new InnerObserver2Callback($jniinput, false)"
//%typemap(javadirectorout) InnerObserver2 "InnerObserver2Callback.getCPtr($javacall)"
//
//%typemap(directorout) InnerObserver2 {
//$result = ($1_type)SWIG_JAVA_JLONG_TO_POINTER(InnerObserver2Callback, $input);
//}


//%typemap(javacode) InnerObserver2Callback %{
//public static long getCPtr(InnerObserver2Callback obj) {
//    return (obj == null) ? 0 : obj.swigCPtr;
//}
//%}

//%typemap(javain) InnerObserver2 "$javainput"

//%typemap(in) InnerObserver2 %{
//    jclass clazz = jenv->GetObjectClass($input);
//    jmethodID mid = jenv->GetMethodID(clazz, "callback", "(LSwigCallbackData;)V");
//    if (!mid) {
//        SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, "Method callback not found");
//        return $null;
//    }
//    $1 = [=](const SwigCallbackData &data) {
//    jclass dataClass = jenv->FindClass("SwigCallbackData");
//    jmethodID constructor = jenv->GetMethodID(dataClass, "<init>", "()V");
//    jobject jdata = jenv->NewObject(dataClass, constructor);
//
//    // 这里需要设置 jdata 对象的属性，以匹配 C++ 的 SwigCallbackData
//
//    jenv->CallVoidMethod($input, mid, jdata);
//    jenv->DeleteLocalRef(jdata);
//};
//%}



// 为 Java 端创建回调接口
//%typemap(javacode) SwigCallback %{
//public interface InnerObserver2Callback {
//    void callback(SwigCallbackData data);
//}
//%}

//%feature("director") InnerObserver;


%include "SwigCallback.h"
%include "SwigCallbackData.h"
%include "TestSwigCallback.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors SwigCallback.i