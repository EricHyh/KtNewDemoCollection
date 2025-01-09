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
    virtual int onCall(SwigCallbackData const &data);
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
    virtual void setOptional(std::optional< FINFeatureFlagVariant > opt);
    virtual void setOptional2(std::optional< FINFeatureFlagVariant > &opt);
    virtual std::optional< FINFeatureFlagVariant > getOptional();
    virtual std::optional< FINFeatureFlagVariant > getOptional2();
public:
    bool swig_overrides(int n) {
      return (n < 5 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<5> swig_override;
};

class SwigDirector_SwigCallback : public SwigCallback, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SwigCallback(JNIEnv *jenv);
    virtual void onTestVariant1(TestVariant variant);
    virtual void onTestVariant2(TestVariant const &variant);
    virtual TestVariant onTestVariant3();
    virtual void onTestVariant4(std::map< std::string,TestVariant,std::less< std::string > > variants);
    virtual ~SwigDirector_SwigCallback();
    virtual void onTest2(InnerObserver2 &observer2);
    virtual void onTest22(std::shared_ptr< InnerObserver2 > observer2);
public:
    bool swig_overrides(int n) {
      return (n < 6 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<6> swig_override;
};


#endif
