#ifndef COMMON_SWIG_CONFIG
#define COMMON_SWIG_CONFIG

%{
#include <unordered_map>
#include <memory>
#include <mutex>
#include <list>
#include <functional>
%}

// java 包名配置
%define %java_package(TYPE, PACKAGE)    //java_package
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "PACKAGE"
%enddef //java_package


// 智能指针参数包装
%define %shared_ptr_param_wrapper(TYPE) //shared_ptr_param_wrapper
%typemap(in) std::shared_ptr<TYPE> {
    std::shared_ptr<TYPE> *argp$argnum = *(std::shared_ptr<TYPE> **)&jarg$argnum;
    if (argp$argnum) {
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
        // 创建新的 shared_ptr，使用自定义删除器
        $1 = std::shared_ptr<TYPE>(argp$argnum->get(), [globalRef](TYPE* ptr) {
            JNIEnv *env = nullptr;
            financial_sdk::JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });
    }
}
%enddef //shared_ptr_param_wrapper


// Function 类型桥接
%define %function_type_bridge(FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME)   //function_type_bridge

%shared_ptr(FUNCTION_TYPE##Bridge)
%ignore FUNCTION_TYPE##Bridge::original;
%ignore FUNCTION_TYPE##Bridge::m_mutex;
%ignore FUNCTION_TYPE##Bridge::obtainOriginal;

%inline %{
class FUNCTION_TYPE##Bridge {

        public:
        virtual ~FUNCTION_TYPE##Bridge() {}

        virtual
        void onCall##CALL_PARAM_TYPE_AND_NAME = 0;

        static const FUNCTION_TYPE obtainOriginal(std::shared_ptr< FUNCTION_TYPE##Bridge > function_bridge){
            std::lock_guard<std::mutex> lock(function_bridge->m_mutex);
            if (auto original_ptr = function_bridge->original.lock()) {
                // 如果原始回调函数还存在，直接返回
                return *original_ptr;
            }

            std::shared_ptr<FUNCTION_TYPE> p_function = std::make_shared<FUNCTION_TYPE>([function_bridge]##CALL_PARAM_TYPE_AND_NAME {
                function_bridge->onCall##CALL_PARAM_NAME;
            });

            function_bridge->original = std::weak_ptr< FUNCTION_TYPE >(p_function);

            return *p_function;
        }

        private:
        std::mutex m_mutex;

        std::weak_ptr <FUNCTION_TYPE> original;

};
%}

%enddef //function_type_bridge

// Function 类型桥接
%define %template_function_type_bridge(FUNCTION_TYPE, FUNCTION_BRIDGE_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME)   //template_function_type_bridge

%shared_ptr(FUNCTION_BRIDGE_TYPE##Bridge)
%ignore FUNCTION_BRIDGE_TYPE##Bridge::original;
%ignore FUNCTION_BRIDGE_TYPE##Bridge::m_mutex;
%ignore FUNCTION_BRIDGE_TYPE##Bridge::obtainOriginal;

%inline %{
class FUNCTION_BRIDGE_TYPE##Bridge {

        public:
        virtual ~FUNCTION_BRIDGE_TYPE##Bridge() {}

        virtual
        void onCall##CALL_PARAM_TYPE_AND_NAME = 0;

        static const FUNCTION_TYPE obtainOriginal(std::shared_ptr< FUNCTION_BRIDGE_TYPE##Bridge > function_bridge){
            std::lock_guard<std::mutex> lock(function_bridge->m_mutex);
            if (auto original_ptr = function_bridge->original.lock()) {
                // 如果原始回调函数还存在，直接返回
                return *original_ptr;
            }

            std::shared_ptr<FUNCTION_TYPE> p_function = std::make_shared<FUNCTION_TYPE>([function_bridge]##CALL_PARAM_TYPE_AND_NAME {
                function_bridge->onCall##CALL_PARAM_NAME;
            });

            function_bridge->original = std::weak_ptr< FUNCTION_TYPE >(p_function);

            return *p_function;
        }

        private:
        std::mutex m_mutex;

        std::weak_ptr <FUNCTION_TYPE> original;

};
%}

%enddef //template_function_type_bridge

// Function 类型的参数桥接
%define %function_param_bridge(FUNCTION_BRIDGE_TYPE, RECEIVER_TYPE, METHOD_NAME) //function_param_bridge

%extend RECEIVER_TYPE {

        public:
        void METHOD_NAME(std::shared_ptr<FUNCTION_BRIDGE_TYPE##Bridge> function_bridge) {
            self->METHOD_NAME(FUNCTION_BRIDGE_TYPE##Bridge::obtainOriginal(function_bridge));
        }
};

%ignore RECEIVER_TYPE::METHOD_NAME;

%enddef //function_param_bridge

%define %function_param_bridge_with_pre_params(FUNCTION_BRIDGE_TYPE, RECEIVER_TYPE, METHOD_NAME, PARAMS_EXP, PARAMS_NAME) //function_param_bridge

// 辅助宏：去除括号
#define REMOVE_PARENS(...) __VA_ARGS__

%extend RECEIVER_TYPE {
        public:
        void METHOD_NAME(REMOVE_PARENS PARAMS_EXP, std::shared_ptr<FUNCTION_BRIDGE_TYPE##Bridge> function_bridge) {
            self->METHOD_NAME(REMOVE_PARENS PARAMS_NAME, FUNCTION_BRIDGE_TYPE##Bridge::obtainOriginal(function_bridge));
        }
};

%ignore RECEIVER_TYPE::METHOD_NAME;

%enddef //function_param_bridge


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