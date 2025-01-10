%module SwigCallbackDemo

%include <std_map.i>
//%include <std_unordered_map.i>


%include "common_swig_config.i"
%include "string_config.i"
%include "optional_config.i"
%include "variant_config.i"
%include <std_string.i>

//typedef uint64_t jlong;
%import "basic_type_config.i"


////typedef uint64_t jlong;
//%apply jlong { uint64_t, uint64_t& };

%{
#include "SwigCallback.h"
#include "SwigCallbackData.h"
#include "TestSwigCallback.h"
#include "../JNIContext.h"
#include <stdint.h>
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

%simple_shared_optional(FINFeatureFlagVariant, FINFeatureFlagVariant)

//%shared_ptr_param_wrapper(SwigCallbackFunctionBridge)
//%shared_ptr_param_wrapper(SwigCallbackFunction1Bridge)
%functional_bridge(SwigCallbackFunction, SwigCallbackFunctionBridge, void, (const SwigCallbackData &data), (data));
%functional_bridge(SwigCallbackFunction1, SwigCallbackFunction1Bridge, void, (const SwigCallbackData &data), (data));


%functional_bridge(InnerObserver2, InnerObserver2Bridge, void, (const SwigCallbackData &data), (data));
%functional_bridge(InnerObserver3, InnerObserver3Bridge, int, (const SwigCallbackData &data), (data));

//typedef std::variant<int, double, long long, std::string> TestVariant;

//%apply TestVariant {std::variant<int, double, long long, std::string>};

//std::variant<int _COMMA_ double _COMMA_ long long _COMMA_ std::string>
//%variant_bridge_4(TestVariant,
//                  TestVariantBridge,
//                  int, Int,
//                  double, Double,
//                  long long, Long,
//                  std::string, String);

%variant_bridge_5(TestVariant, TestVariantBridge,
                    int, Int,
                    double, Double,
                    std::string, String,
                    bool, Bool,
                    int64_t, Long);

%java_package(std::variant<int __COMMA__ double __COMMA__ std::string __COMMA__ bool __COMMA__ int64_t>, com.example.ndk_demo_lib2)

%shared_type_bridge(std::variant<int __COMMA__ double __COMMA__ std::string __COMMA__ bool __COMMA__ int64_t>, TestVariantBridge, TestVariantBridge)

%template(Str2TestVariantMap) std::map<std::string, std::variant<int __COMMA__ double __COMMA__ std::string __COMMA__ bool __COMMA__ int64_t>>;
//%apply TestVariantBridge { std::variant<int, double, std::string, bool, int64_t> };
//%apply TestVariant { std::variant<int, double, std::string, bool, int64_t> };
//%template(Str2TestVariantMap) std::map<std::string, TestVariant>;



//%apply int { int }

//typedef long int int64_t;
//%apply long int { int64_t }


//%template(Str2Int64Map) std::map<std::string, int64_t>;
//
//
//
//%template(Str2StrMap) std::map<std::string, std::string>;
//%template(UnorderedStr2StrMap) std::unordered_map<std::string, std::string>;
//%template(FeatureFlagVariant2StrMap) std::unordered_map<std::shared_ptr<FINFeatureFlagVariant>, std::string>;


//%template(Str2TestVariantMap) std::map<std::string, TestVariant> ;

//%feature("nspace") TestNamespace;
//%nspace TestNamespace;
//%rename(TestNamespaceClass) TestNamespace;

%include "SwigCallback.h"
%include "SwigCallbackData.h"
%include "TestSwigCallback.h"


// swig -c++ -java -package com.example.ndk_demo_lib1 -directors -debug-tmsearch SwigCallback.i
// swig -c++ -java -package com.example.ndk_demo_lib1 -directors SwigCallback.i