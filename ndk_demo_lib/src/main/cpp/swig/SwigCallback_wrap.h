/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_SwigCallbackDemo_WRAP_H_
#define SWIG_SwigCallbackDemo_WRAP_H_

class SwigDirector_SwigCallbackFunctionBridge : public SwigCallbackFunctionBridge, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SwigCallbackFunctionBridge(JNIEnv *jenv);
    virtual ~SwigDirector_SwigCallbackFunctionBridge();
    virtual void onCall(SwigCallbackData const &data);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_SwigCallbackFunction1Bridge : public SwigCallbackFunction1Bridge, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SwigCallbackFunction1Bridge(JNIEnv *jenv);
    virtual ~SwigDirector_SwigCallbackFunction1Bridge();
    virtual void onCall(SwigCallbackData const &data);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_InnerObserver2Bridge : public InnerObserver2Bridge, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_InnerObserver2Bridge(JNIEnv *jenv);
    virtual ~SwigDirector_InnerObserver2Bridge();
    virtual void onCall(SwigCallbackData const &data);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_InnerObserver3Bridge : public InnerObserver3Bridge, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_InnerObserver3Bridge(JNIEnv *jenv);
    virtual ~SwigDirector_InnerObserver3Bridge();
    virtual void onCall(SwigCallbackData const &data);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_InnerObserver : public InnerObserver, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_InnerObserver(JNIEnv *jenv);
    virtual ~SwigDirector_InnerObserver();
    virtual void onTest1(std::shared_ptr< SwigCallbackData > data1);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_SwigCallback : public SwigCallback, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SwigCallback(JNIEnv *jenv);
    virtual void onTest1(std::shared_ptr< SwigCallbackData > data1);
    virtual void onTest2(SwigCallbackData data2);
    virtual void onTest3(std::shared_ptr< InnerObserver > innerCallback);
    virtual std::shared_ptr< SwigCallbackData > onTest4(int gg);
    virtual void onTest5(int a,std::string b,InnerObserver2 innerCallback,int c);
    virtual void onTest6(int a,std::string b,InnerObserver2 innerCallback2,InnerObserver3 innerCallback3,int c);
    virtual void onTest7(std::string str);
    virtual std::string onTest8();
    virtual void onTest9(std::optional< std::string > &str);
    virtual std::optional< std::string > &onTest10();
    virtual void onTest11(std::shared_ptr< std::string > &str);
    virtual void onTest12(std::map< std::string,std::string,std::less< std::string > > str);
    virtual void onTest13(std::unordered_map< std::string,std::string > str);
    virtual void onTest14(std::unordered_map< std::shared_ptr< FINFeatureFlagVariant >,std::string > str);
    virtual std::shared_ptr< std::string > onTest12();
    virtual ~SwigDirector_SwigCallback();
public:
    bool swig_overrides(int n) {
      return (n < 15 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<15> swig_override;
};


#endif
