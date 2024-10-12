%module SwigDemo

////%typemap(javapackage) Callback2 "com.example.xxx"
//%typemap(javapackage) SWIGTYPE "com.example.xx1"
//
//%pragma(java) moduleimports=%{
//import com.example.your.package.name.*;
//%}

//%feature("javacode") Callback2 %{
//// 你的自定义代码放在这里
//import java.util.*;
//%}

%{
#include "D:\workspace\KtDemoCollection\ndk_demo_lib\src\main\cpp\TestSwigData.h"
#include "TestSwig.h"
#include "test1/CallbackDataT1.h"
#include <unordered_map>
#include <jni.h>
#include <memory>
// 全局变量来存储 Java 对象的全局引用
std::unordered_map<Callback1*, jobject> g_callbackRefs;
std::unordered_map<Callback2*, jobject> g_callback2Refs;
%}

%typemap(javabody) Callback2 %{

    static {
        System.loadLibrary("mylib");
    }
%}



%typemap(javacode) Callback2 %{
  // This is a test comment
  public void testMethod() {
    System.out.println("Test method");
  }
%}

%typemap(javaimports) Callback2 %{
// This is a test comment
package com.xxx.xxx;
%}



%include "std_shared_ptr.i"

//%typemap("javapackage") TestCallback3Wrapper "com.example.package2"
//%typemap("javapackage") TestCallback3Wrapper, TestCallback3Wrapper *, TestCallback3Wrapper & "com.example.package2"

//%typemap(javaclassname) TestSwigData "TestSwigDataBridge";

%typemap("javapackage") TestCallbackWrapper, TestCallbackWrapper *, TestCallbackWrapper & "com.xxx.package"



// 支持 shared_ptr
%include "std_shared_ptr.i"
%shared_ptr(TestSwigData2)
%shared_ptr(CallbackDataT1)

// 启用 std::string 和 std::vector 支持
%include "std_string.i"
%include "std_vector.i"

// 声明使用的模板
%template(StringVector) std::vector<std::string>;
%template(IntVector) std::vector<int>;



//%feature("javapackage") CallbackDataT1Vector "com.xxx.package1";
//%template(CallbackDataT1Vector) std::vector<CallbackDataT1>;
//%feature("javapackage") CallbackDataT1Vector "com.xxx.package1";

%javamethodmodifiers CallbackDataT1Vector "public";
%typemap(javaclassmodifiers) CallbackDataT1Vector "public class";
%typemap(javacode) CallbackDataT1Vector %{
// 可以在这里添加额外的 Java 代码
%}
//%template(CallbackDataT1Vector) std::vector<CallbackDataT1>;
%rename(CallbackDataT1Vector) std::vector<CallbackDataT1>;
//namespace com{
//    namespace xxx {
//        namespace package1{
//                %template(CallbackDataT1Vector) std::vector<CallbackDataT1>;
//        }
//    }
//}




//%feature("director") Callback2;


%template(TestSwigData2Vector) std::vector<TestSwigData2>;



//%template(com.xx.CallbackDataT1Vector) std::vector<std::shared_ptr<CallbackDataT1>>;

// 启用 director 功能
%feature("director") TestCallbackWrapper;
%feature("director") TestCallback3Wrapper;
%feature("director") TestCallback4Wrapper;
%feature("director") IntTestCallback4Bridge;

%rename(TestCallbackBridge) TestCallbackWrapper;
%rename(TestSwigDataBridge) TestSwigData;
%rename(TestSwigData2Bridge) TestSwigData2;



//%ignore JObjectWrapper;
//%ignore JNIEnv;

// 修改 TestSwig 类的方法

%{
#include <thread>
static thread_local JNIEnv* t_env = nullptr;
static thread_local jobject t_callback = nullptr;

// JObjectWrapper 的简单实现
class JObjectWrapper {
        public:
        JObjectWrapper(JNIEnv* env, jobject obj) : m_env(env), m_obj(obj) {}
        JNIEnv* m_env;
        jobject m_obj;
};
%}



//%extend TestSwig {
//        void test2(TestCallbackWrapper* callback) {
//            if (callback) {
//                self->test2([callback](const TestSwigData& value) {
//                    callback->call(value);
//                });
//            }
//        }
//
//        void test3(TestCallback3Wrapper* callback) {
//            if (callback) {
//                self->test3([callback](const TestSwigData& value) {
//                    callback->call(value);
//                });
//            }
//        }
//
//        void test4(TestCallback4Wrapper<int>* callback) {
//            if (callback) {
//                std::shared_ptr<JObjectWrapper> jarg2_wrapper = std::make_shared<JObjectWrapper>(t_env, t_callback);
//                self->test4([jarg2_wrapper, callback](const int& value) {
//                    callback->call(value);
//                });
//            }
//        }
//}
//
//%typemap(in) Callback1 CallbackTest::addCallback {
//    Callback1 *argp = *(Callback1 **)&jarg$argnum;
//    if (!argp) {
//    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null Callback1");
//    return $null;
//    }
//    $1 = *argp;
//}
//
//%typemap(argout) Callback1 CallbackTest::addCallback{
//    Callback1 *argp = *(Callback1 **)&jarg$argnum;
//    jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
//    g_callbackRefs[argp] = globalRef;
//}
//
//%typemap(in) Callback1 (CallbackTest::removeCallback) {
//    Callback1 *argp = *(Callback1 **)&jarg$argnum;
//    if (!argp) {
//        SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null Callback1");
//        return $null;
//    }
//    $1 = *argp;
//
//    auto it = g_callbackRefs.find(argp);
//    if (it != g_callbackRefs.end()) {
//        jenv->DeleteGlobalRef(it->second);
//        g_callbackRefs.erase(it);
//    }
//}
//
//%shared_ptr(Callback2)
//
//%typemap(in) Callback2 (CallbackTest::setCallback) {
//        Callback2 *argp = *(Callback2 **)&jarg$argnum;
//        if (!argp) {
//            SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null Callback2");
//            return $null;
//        }
//        $1 = *argp;
//
//        auto it = g_callback2Refs.find(argp);
//        if (it != g_callback2Refs.end()) {
//            jenv->DeleteGlobalRef(it->second);
//            g_callbackRefs.erase(it);
//        }
//}
//
//
//%typemap(in) std::shared_ptr<Callback2> (CallbackTest::setCallback2) {
//        std::shared_ptr<Callback2> *argp = *(std::shared_ptr<Callback2> **)&jarg$argnum;
//        if (argp) {
//            // 创建全局引用
//            jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
//
//            // 创建新的 shared_ptr，使用自定义删除器
//            $1 = std::shared_ptr<Callback2>(argp->get(), [globalRef](Callback2* ptr) {
//                JNIEnv* env;
//                if (g_jvm->GetEnv((void**)&env, JNI_VERSION_1_6) == JNI_OK) {
//                    env->DeleteGlobalRef(globalRef);
//                }
//                delete ptr;
//            });
//        }
//}


// 清理 typemap，以免影响其他函数
%clear JNIEnv *;
%clear jobject;

// 忽略原始的方法（移到文件前面）
%ignore TestSwig::test2;
%ignore TestSwig::test3;
%ignore TestSwig::test4;


// 首先包含必要的头文件
//%include "D:\workspace\KtDemoCollection\ndk_demo_lib\src\main\cpp\TestSwigData.h"
//%include "TestSwig.h"

//%rename("%(fullname)sWrapper") TestSwigData;


//%shared_ptr(Callback1)
//
%feature("director") Callback1;


//%typemap("javapackage") CallbackDataT1Vector, CallbackDataT1Vector *, CallbackDataT1Vector & "com.xxx.package1"



// 修改 Callback1 的构造函数
//%javamethodmodifiers Callback1::Callback1 "public";
//%rename(Callback1) Callback1::Callback1;
//%feature("javacode") Callback1::Callback1 %{
//{
//SwigDemoJNI.Callback1_director_connect(this, swigCPtr, true, false);
//}
//%}

// 定义 IntTestCallback4Wrapper
//%template(IntTestCallback4Bridge) TestCallback4Wrapper<int>;


// 设置 Java 包名
//%pragma(java) jniclasspackage="com.example.package1"

//%typemap("javapackage") TestCallback3Wrapper "com.example.package2"

//%rename("%(fullname)s_Bridge", notregexmatch$name=".*_Bridge$") "";
%include "test1/CallbackTest.h"
%include "test1/CallbackDataT1.h"

// swig -c++ -java -directors testswig.i