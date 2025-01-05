%module SwigCallbackDemo


%include <std_map.i>
%include <std_unordered_map.i>
%include "common_swig_config.i"
%include "string_config.i"
%include "optional_config.i"
%include <std_string.i>



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

%simple_optional(FINFeatureFlagVariant, FINFeatureFlagVariant)

//%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)
//%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)
%function_type_bridge(SwigCallbackFunction,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_type_bridge(SwigCallbackFunction1,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);


%function_type_bridge(InnerObserver2,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);
%function_type_bridge(InnerObserver3,(const SwigCallbackData &data), (data), com/example/ndk_demo_lib1);


%template(Str2StrMap) std::map<std::string, std::string>;
%template(UnorderedStr2StrMap) std::unordered_map<std::string, std::string>;
%template(FeatureFlagVariant2StrMap) std::unordered_map<std::shared_ptr<FINFeatureFlagVariant>, std::string>;

//%feature("nspace") TestNamespace;
//%nspace TestNamespace;
//%rename(TestNamespaceClass) TestNamespace;

%include "SwigCallback.h"
%include "SwigCallbackData.h"
%include "TestSwigCallback.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors SwigCallback.i