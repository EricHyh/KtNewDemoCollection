%module JNIItemTest


%include "swig_config/common_swig_config.i"

%include <std_string.i>

%byte_array_bridge()

%{
#include "model/N2CTestItem.h"
#include "model/N2CItemIcon.h"
#include "observer/ObserverManager.h"
#include "nsp/NamespaceTest.h"

#include "model/TestItem.h"
#include "model/ItemIcon.h"

#include "color/TestColor.h"

#include "JNITestEntrance.h"
#include "JNIContext.h"
%}

%shared_ptr(ITestItem)
%shared_ptr(IItemIcon)
%shared_ptr(N2CTestItem)
%shared_ptr(N2CItemIcon)
%shared_ptr(ITestColor)
%shared_ptr(N2CTestColor)

%shared_ptr(ITestObserver2)


%feature("director") ITestItem;
%feature("director") IC2NTestItemFactory;
%feature("director") IItemIcon;
%feature("director") ITestColor;
%feature("director") IObserverManager;
%feature("director") ITestObserver2;

%swig_director_wrapper_prepare();

%shared_ptr_wrapper(ITestItem);
%shared_ptr_wrapper(IItemIcon);

%director_shared_ptr_wrapper(ITestItem);

%template(StringVector) std::vector<std::string>;
%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;

%functional_bridge(TestObserver, TestObserverBridge, void, (const int &data), (data));
%functional_bridge(TestObserver2, TestObserver2Bridge, void, (const TestObserver2Data &data), (data));
%std_vector_bridge(TestObserver2);
%template(TestObserver2Vector) std::vector<TestObserver2>;

%java_hash_equals(ITestObserver2);

%rename(ITestObserver2Bridge) ITestObserver2;

%rename(NamespaceTest1) first::second::test1;


%include "model/ItemIcon.h"
%include "model/TestItem.h"

%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"
%include "color/TestColor.h"
%include "observer/ObserverManager.h"
%include "nsp/NamespaceTest.h"
%include "JNITestEntrance.h"





// swig -c++ -java -package com.example.jni_test.model -directors jni_item_test.i