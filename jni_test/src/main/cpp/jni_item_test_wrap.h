/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_JNIItemTest_WRAP_H_
#define SWIG_JNIItemTest_WRAP_H_

class SwigDirector_IItemIcon : public IItemIcon, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_IItemIcon(JNIEnv *jenv);
    virtual ~SwigDirector_IItemIcon();
    virtual std::string getName();
    virtual std::string getIcon();
public:
    bool swig_overrides(int n) {
      return (n < 2 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<2> swig_override;
};

class SwigDirector_ITestItem : public ITestItem, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_ITestItem(JNIEnv *jenv);
    virtual ~SwigDirector_ITestItem();
    virtual std::string getId();
    virtual std::string getTitle();
    virtual std::string getEnvelopePic();
    virtual std::string getDesc();
    virtual std::string getNiceDate();
    virtual std::string getAuthor();
    virtual std::vector< std::string > getTags();
    virtual std::vector< std::shared_ptr< IItemIcon > > getIcons();
public:
    bool swig_overrides(int n) {
      return (n < 8 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<8> swig_override;
};

class SwigDirector_IC2NTestItemFactory : public IC2NTestItemFactory, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_IC2NTestItemFactory(JNIEnv *jenv);
    virtual ~SwigDirector_IC2NTestItemFactory();
    virtual std::shared_ptr< ITestItem > create(int index);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<1> swig_override;
};

class SwigDirector_N2CTestItem : public N2CTestItem, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_N2CTestItem(JNIEnv *jenv,int index);
    virtual ~SwigDirector_N2CTestItem();
    virtual std::string getId();
    virtual std::string getTitle();
    virtual std::string getEnvelopePic();
    virtual std::string getDesc();
    virtual std::string getNiceDate();
    virtual std::string getAuthor();
    virtual std::vector< std::string > getTags();
    virtual std::vector< std::shared_ptr< IItemIcon > > getIcons();
public:
    bool swig_overrides(int n) {
      return (n < 8 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<8> swig_override;
};

class SwigDirector_N2CItemIcon : public N2CItemIcon, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_N2CItemIcon(JNIEnv *jenv,int index);
    virtual ~SwigDirector_N2CItemIcon();
    virtual std::string getName();
    virtual std::string getIcon();
public:
    bool swig_overrides(int n) {
      return (n < 2 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<2> swig_override;
};


#endif
