#ifndef COMMON_SWIG_CONFIG
#define COMMON_SWIG_CONFIG

%{
#include <map>
#include <unordered_map>
#include <variant>
#include <memory>
#include <mutex>
#include <list>
#include <vector>
#include <functional>
%}

// 全局搜索，工程配置替换

// https://www.swig.org/Doc4.3/index.html

// java 包名配置
%define %java_package(TYPE, PACKAGE)    //java_package
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%enddef //java_package

#endif // COMMON_SWIG_CONFIG

// 修改 java 类函数的修饰符
// 源码位置：https://github.com/swig/swig/blob/master/Lib/java/java.swg
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)

// 源码位置：https://github.com/swig/swig/blob/master/Lib/java/boost_shared_ptr.i
// 源码位置：https://github.com/swig/swig/blob/master/Lib/shared_ptr.i
%define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...)
SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)
%enddef

%import "enums.swg"
%import "std_shared_ptr.i"
%import "std_unique_ptr.i"
%import "std_string.i"
%import "std_vector.i"   //https://github.com/swig/swig/blob/master/Lib/java/std_vector.i
%import "std_const_vector.i"
%import "std_map.i"
%import "std_unordered_map.i"

%import "functional_config.i"
%import "java_package_and_import_config.i"
%import "namespace_config.i"

//%import "stdint.i"            //不能用这个，已替换成 basic_type_config.i
%import "basic_type_config.i"
%import "string_config.i"
%import "byte_array_config.i"
%import "int_array_config.i"
%import "optional_config.i"

%import "shared_ptr_config.i"
%import "director_config.i"

%import "variant_type_wrapper_config.i"
%import "variant_type_map_config.i"

%import "map_type_config.i"     //基于 std_map.i 扩展
%import "vector_type_config.i"  //基于 std_vector.i 扩展

%import "java_object_config.i"


%ignore "private:";     //忽略所有私用成员

%naturalvar;            //一律将成员变量转成 set/get 函数


/**
 * 逗号宏定义，避免"带逗号的类型"被识别成多个参数<p>
 * 案例：<p>
 *  - 原始类型：std::variant<int , double , long long , std::string>
 *  <p>
 *  - 逗号处理：std::variant<int __COMMA__ double __COMMA__ long long __COMMA__ std::string>
 */
#ifndef __COMMA__
#define __COMMA__ ,
#endif

%define SDK_API
%enddef