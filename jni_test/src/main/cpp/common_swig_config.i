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
%import "shared_ptr_swig_config.i"