%module SwigCallbackDemo


%include "common_swig_config.i"
%import "SwigCallbackxx.i"

%{
#include "SwigCallback.h"
#include "SwigCallbackData.h"
#include "TestSwigCallback.h"
#include "../JNIContext.h"
%}


// 支持 shared_ptr
//%include "std_shared_ptr.i"
//%include "std_unique_ptr.i"
%shared_ptr(SwigCallbackData)
%shared_ptr(SwigCallback)
%shared_ptr(FINFeatureFlagVariant)
%shared_ptr(InnerObserver)

%feature("director") InnerObserver;
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
%function_type_bridge(SwigCallbackFunction,(const SwigCallbackData &data), (data));
%function_param_bridge(SwigCallbackFunction, TestSwigCallback, setCallback4);
%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)



//%shared_ptr(SwigCallbackFunction1Bridge)
%function_type_bridge(SwigCallbackFunction1, (const SwigCallbackData &data), (data));
%function_param_bridge(SwigCallbackFunction1, TestSwigCallback, setCallback5);
%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)


//%function_param_bridge_with_pre_params(SwigCallbackFunction1, TestSwigCallback, setCallback5, (int param1), (param1));


%include "SwigCallback.h"
%include "SwigCallbackData.h"
%include "TestSwigCallback.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors SwigCallback.i