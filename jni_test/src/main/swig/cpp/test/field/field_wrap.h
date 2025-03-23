/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_FieldModule_WRAP_H_
#define SWIG_FieldModule_WRAP_H_

class SwigDirector_IntLiveDataObserver : public IntLiveDataObserver, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_IntLiveDataObserver(JNIEnv *jenv);
    virtual ~SwigDirector_IntLiveDataObserver();
    virtual void onCall(int const &value);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_StringLiveDataObserver : public StringLiveDataObserver, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_StringLiveDataObserver(JNIEnv *jenv);
    virtual ~SwigDirector_StringLiveDataObserver();
    virtual void onCall(std::string const &value);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_OptionalStringLiveDataObserver : public OptionalStringLiveDataObserver, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_OptionalStringLiveDataObserver(JNIEnv *jenv);
    virtual ~SwigDirector_OptionalStringLiveDataObserver();
    virtual void onCall(std::optional< std::string > const &value);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_IntLiveData : public LiveData< int >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_IntLiveData(JNIEnv *jenv,int value);
    virtual ~SwigDirector_IntLiveData();
    virtual int GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_StringLiveData : public LiveData< std::string >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_StringLiveData(JNIEnv *jenv,std::string value);
    virtual ~SwigDirector_StringLiveData();
    virtual std::string GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_OptionalStringLiveData : public LiveData< std::optional< std::string > >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_OptionalStringLiveData(JNIEnv *jenv,std::optional< std::string > value);
    virtual ~SwigDirector_OptionalStringLiveData();
    virtual std::optional< std::string > GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_MutableIntLiveData : public MutableLiveData< int >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_MutableIntLiveData(JNIEnv *jenv,int value);
    virtual ~SwigDirector_MutableIntLiveData();
    virtual int GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_MutableStringLiveData : public MutableLiveData< std::string >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_MutableStringLiveData(JNIEnv *jenv,std::string value);
    virtual ~SwigDirector_MutableStringLiveData();
    virtual std::string GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_MutableOptionalStringLiveData : public MutableLiveData< std::optional< std::string > >, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_MutableOptionalStringLiveData(JNIEnv *jenv,std::optional< std::string > value);
    virtual ~SwigDirector_MutableOptionalStringLiveData();
    virtual std::optional< std::string > GetValue() const;
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};


#endif
