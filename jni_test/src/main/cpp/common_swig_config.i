#ifndef COMMON_SWIG_CONFIG
#define COMMON_SWIG_CONFIG

%{
#include <unordered_map>
#include <memory>
#include <mutex>
#include <list>
#include <vector>
#include <functional>
%}

// java 包名配置
%define %java_package(TYPE, PACKAGE)    //java_package
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "PACKAGE"
%enddef //java_package


// 智能指针参数包装
%define %shared_ptr_param_wrapper(TYPE) //shared_ptr_param_wrapper
%typemap(in) std::shared_ptr<TYPE>, std::shared_ptr<TYPE> const & %{
    std::shared_ptr<TYPE> temp$argnum;
    $1 = &temp$argnum;
    std::shared_ptr<TYPE> *argp$argnum = *(std::shared_ptr<TYPE> **)&jarg$argnum;
    if (argp$argnum) {
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
        // 创建新的 shared_ptr，使用自定义删除器
        *$1 = std::shared_ptr<TYPE>(argp$argnum->get(), [globalRef](TYPE* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });
    }
%}


%enddef //shared_ptr_param_wrapper


#endif // COMMON_SWIG_CONFIG


// 源码位置：https://github.com/swig/swig/blob/master/Lib/java/java.swg
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)

// 源码位置：https://github.com/swig/swig/blob/master/Lib/java/boost_shared_ptr.i
// 源码位置：https://github.com/swig/swig/blob/master/Lib/shared_ptr.i
%define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...)
SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)
%enddef


%import "std_shared_ptr.i"
%import "std_unique_ptr.i"
%import "std_string.i"
%import "std_vector.i"


//if (jresult) {
////std::shared_ptr<  ITestItem >SwigDirector_ITestItem
//std::shared_ptr< ITestItem > *smart_jresult = *(std::shared_ptr<  ITestItem > **)&jresult;
//
//std::shared_ptr< ITestItem > * smartarg = *(std::shared_ptr<  ITestItem > **)&jresult;
//
//SwigDirector_ITestItem *pItem = reinterpret_cast<SwigDirector_ITestItem>(smartarg->get()));
//object item_jobject = pItem->swig_get_self(jenv);
//
//// 创建全局引用
//object globalRef = jenv->NewGlobalRef(item_jobject);
//
//c_result = std::shared_ptr<ITestItem>(smartarg->get(), [globalRef](ITestItem* ptr) {
//    JNIEnv *env = nullptr;
//    JNIContext context(env);
//    // 删除全局引用
//    env->DeleteGlobalRef(globalRef);
//});
//
//c_result = *smartarg;
//}