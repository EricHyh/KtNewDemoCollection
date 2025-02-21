%module JNIItemTest


%include "common_swig_config.i"
%include "functional_config.i"
%include "byte_array_config.i"
%include "enum_type_config.i"
%include "map_type_config.i"
%include <std_string.i>

%byte_array_bridge()

%{
#include "model/N2CTestItem.h"
#include "model/N2CItemIcon.h"
#include "observer/ObserverManager.h"

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


%feature("director") ITestItem;
%feature("director") IC2NTestItemFactory;
%feature("director") IItemIcon;
%feature("director") ITestColor;
%feature("director") IObserverManager;

%shared_ptr_wrapper(ITestItem);
%shared_ptr_wrapper(IItemIcon);

%director_shared_ptr_wrapper(ITestItem, com/example/jni_test/model/ITestItem);

%template(StringVector) std::vector<std::string>;
%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;

%functional_bridge(TestObserver, TestObserverBridge, void, (const int &data), (data));


//using TestVariant = std::variant<TestEnum2, TestStruct>;
//std::map<TestEnum1, TestVariant>
%variant_with_empty_bridge_2(TestVariant, TestVariantBridge,
        TestEnum2, TestEnum2,
        TestStruct, TestStruct
);

%normal_variant_type_bridge(TestVariant, TestVariantBridge, TestVariantBridge);

%std_map_bridge(std::map<TestEnum1 __COMMA__ TestVariant>, TestVariantMap);

%template(TestIntMap) std::map<int, int>;


%include "model/ItemIcon.h"
%include "model/TestItem.h"

%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"
%include "color/TestColor.h"
%include "observer/ObserverManager.h"
%include "JNITestEntrance.h"





// swig -c++ -java -package com.example.jni_test.model -directors jni_item_test.i