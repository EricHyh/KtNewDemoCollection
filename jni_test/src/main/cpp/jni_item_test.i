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

#include "field/FieldDataModel.h"
#include "field/FieldKeys.h"
#include "field/LiveData.h"
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
%shared_ptr_wrapper(IFINBrokerCapabilityConfig);

%director_shared_ptr_wrapper(ITestItem);

%template(StringVector) std::vector<std::string>;
%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;

%ignore makeFiledKey<Value>;
%ignore FieldDataModel::getFieldValue;

%functional_bridge(TestObserver, TestObserverBridge, void, (const int &data), (data));
%functional_bridge(TestObserver2, TestObserver2Bridge, void, (const TestObserver2Data &data), (data));
%std_vector_bridge(TestObserver2);
%template(TestObserver2Vector) std::vector<TestObserver2>;


%functional_bridge(LiveDataObserver<int>, IntLiveDataObserver, void, (const int &value), (value));
%functional_bridge(LiveDataObserver<std::string>, StringLiveDataObserver, void, (const std::string &value), (value));
%functional_bridge(LiveDataObserver<std::optional<std::string>>, OptionalStringLiveDataObserver, void, (const std::optional<std::string> &value), (value));



%shared_ptr_wrapper(BaseFiledKey);
%std_vector_bridge(std::shared_ptr<BaseFiledKey>);
%template(BaseFiledKeyVector) std::vector<std::shared_ptr<BaseFiledKey>>;

%feature("nodirector") FiledKey<int>;
%feature("nodirector") FiledKey<std::string>;
%feature("nodirector") FiledKey<std::optional<std::string>>;
%feature("nodirector") BaseFiledKey;


%shared_ptr(FiledKey<int>);
%shared_ptr(FiledKey<std::string>);
%shared_ptr(FiledKey<std::optional<std::string>>);

%extend FieldDataModel {
    std::shared_ptr<LiveData<int>> getIntFiledValue(const FiledKey<int>& key){
        return self->getFiledValue(key);
    }

    std::shared_ptr<LiveData<std::string>> getStringFiledValue(const FiledKey<std::string>& key){
        return self->getFiledValue(key);
    }

    std::shared_ptr<LiveData<std::optional<std::string>>> getOptionalStringFiledValue(const FiledKey<std::optional<std::string>>& key){
        return self->getFiledValue(key);
    }
}

%extend MutableFieldDataModel {
    std::shared_ptr<MutableLiveData<int>> getIntFiledValue(const FiledKey<int>& key){
        return self->getMutableFiledValue(key);
    }

    std::shared_ptr<MutableLiveData<std::string>> getStringFiledValue(const FiledKey<std::string>& key){
        return self->getMutableFiledValue(key);
    }

    std::shared_ptr<MutableLiveData<std::optional<std::string>>> getOptionalStringFiledValue(const FiledKey<std::optional<std::string>>& key){
        return self->getMutableFiledValue(key);
    }
}

%shared_ptr_wrapper(LiveData<int>);
%shared_ptr_wrapper(LiveData<std::string>);
%shared_ptr_wrapper(LiveData<std::optional<std::string>>);
%shared_ptr_wrapper(MutableLiveData<int>);
%shared_ptr_wrapper(MutableLiveData<std::string>);
%shared_ptr_wrapper(MutableLiveData<std::optional<std::string>>);


%java_hash_equals(ITestObserver2);


%optional_type_map(TestOptional);
%enum_optional_type_map(TestEnum1);

%rename(ITestObserver2Bridge) ITestObserver2;
%rename(TestOptionalBridge) TestOptional;

%rename(NamespaceTest1) first::second::test1;

%include "field/FieldDataModel.h"
%include "field/FieldKeys.h"
%include "field/LiveData.h"

%include "model/ItemIcon.h"
%include "model/TestItem.h"

%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"
%include "color/TestColor.h"
%include "observer/ObserverManager.h"
%include "nsp/NamespaceTest.h"
%include "JNITestEntrance.h"



%template(IntFiledKey) FiledKey<int>;
%template(StringFiledKey) FiledKey<std::string>;
%template(OptionalStringFiledKey) FiledKey<std::optional<std::string>>;

%template(IntLiveData) LiveData<int>;
%template(StringLiveData) LiveData<std::string>;
%template(OptionalStringLiveData) LiveData<std::optional<std::string>>;

%template(MutableIntLiveData) MutableLiveData<int>;
%template(MutableStringLiveData) MutableLiveData<std::string>;
%template(MutableOptionalStringLiveData) MutableLiveData<std::optional<std::string>>;


// swig -c++ -java -package com.example.jni_test.model -directors jni_item_test.i