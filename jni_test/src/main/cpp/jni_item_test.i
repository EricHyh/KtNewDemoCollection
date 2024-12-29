%module JNIItemTest


%include "common_swig_config.i"
%include <std_string.i>


%{
#include "model/N2CTestItem.h"
#include "model/N2CItemIcon.h"

#include "model/TestItem.h"
#include "model/ItemIcon.h"

#include "color/TestColor.h"

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

%shared_ptr_wrapper(ITestItem);
%shared_ptr_wrapper(IItemIcon);

%director_shared_ptr_wrapper(ITestItem, com/example/jni_test/model/ITestItem);

%template(StringVector) std::vector<std::string>;
%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;


%include "model/ItemIcon.h"
%include "model/TestItem.h"

%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"
%include "color/TestColor.h"





// swig -c++ -java -package com.example.jni_test.model -directors jni_item_test.i