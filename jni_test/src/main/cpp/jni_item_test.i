%module JNIItemTest


%include "common_swig_config.i"
%include <std_string.i>


%{
#include "model/N2CTestItem.h"
#include "model/N2CItemIcon.h"

#include "model/TestItem.h"
#include "model/ItemIcon.h"

#include "JNIContext.h"
%}

%shared_ptr(ITestItem)
%shared_ptr(IItemIcon)
%shared_ptr(N2CTestItem)
%shared_ptr(N2CItemIcon)


%feature("director") ITestItem;
%feature("director") IC2NTestItemFactory;
%feature("director") IItemIcon;


%shared_ptr_param_wrapper(ITestItem)
%shared_ptr_param_wrapper(IItemIcon)


%typemap(directorout, descriptor="Lcom/example/jni_test/model/ITestItem;") std::shared_ptr<ITestItem> %{
    if (!$input) {
        $1 = nullptr;
    } else {
        std::shared_ptr< ITestItem > * smartarg = *(std::shared_ptr<  ITestItem > **)&$input;
        auto *item_ptr = dynamic_cast<SwigDirector_ITestItem*>(smartarg->get());
        jobject item_jobject = item_ptr->swig_get_self(jenv);
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(item_jobject);
        $1 = std::shared_ptr<ITestItem>(smartarg->get(), [globalRef](ITestItem* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });
    }
%}


%template(StringVector) std::vector<std::string>;
%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;






%include "model/ItemIcon.h"
%include "model/TestItem.h"

%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"





// swig -c++ -java -package com.example.jni_test.model -directors jni_item_test.i