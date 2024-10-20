%module SwigCallbackDemo


%include "common_swig_config.i"

%{
#include "SwigCallback.h"
#include "SwigCallbackData.h"
#include "TestSwigCallback.h"
#include "../JNIContext.h"
%}

%import "std_shared_ptr.i"

// 支持 shared_ptr
%shared_ptr(SwigCallbackData)
%shared_ptr(SwigCallback)
%shared_ptr(FINFeatureFlagVariant)
%shared_ptr(InnerObserver)


%feature("director") SwigCallback;

%shared_ptr_param_wrapper(SwigCallback)

%shared_ptr_param_wrapper(InnerObserver)

//%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)
//%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)
%function_type_bridge(SwigCallbackFunction,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_type_bridge(SwigCallbackFunction1,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);


%function_type_bridge(InnerObserver2,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_type_bridge(InnerObserver3,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);


%include "SwigCallback.h"
%include "SwigCallbackData.h"
%include "TestSwigCallback.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors SwigCallback.i