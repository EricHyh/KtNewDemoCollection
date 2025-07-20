%include "../../../scripts/config/common_swig_config.i"
%nsp_2_java_0(FieldModule, test.field)

%{
#include "field/LiveData.h"
#include "field/FieldKeys.h"
#include "field/FieldDataModel.h"
%}

//%jni_package_import_0(test.field);

%java_package_import_0(BaseFiledKey, test.field);
%java_package_import_0(std::vector<std::shared_ptr<BaseFiledKey>>, test.field);

%java_package_import_0(FiledKey<int>, test.field);
%java_package_import_0(FiledKey<std::string>, test.field);
%java_package_import_0(FiledKey<std::optional<std::string>>, test.field);

%java_package_import_0(LiveDataObserver<int>, test.field);
%java_package_import_0(IntLiveDataObserver, test.field);

%java_package_import_0(LiveDataObserver<std::string>, test.field);
%java_package_import_0(StringLiveDataObserver, test.field);

%java_package_import_0(LiveDataObserver<std::optional<std::string>>, test.field);
%java_package_import_0(OptionalStringLiveDataObserver, test.field);

%java_package_import_0(FieldDataModel, test.field);
%java_package_import_0(MutableFieldDataModel, test.field);

%java_package_import_0(ILiveData, test.field);
%java_package_import_0(LiveData<int>, test.field);
%java_package_import_0(LiveData<std::string>, test.field);
%java_package_import_0(LiveData<std::optional<std::string>>, test.field);
%java_package_import_0(MutableLiveData<int>, test.field);
%java_package_import_0(MutableLiveData<std::string>, test.field);
%java_package_import_0(MutableLiveData<std::optional<std::string>>, test.field);


%ignore makeFiledKey<Value>;
%ignore FieldDataModel::getFieldValue;
%ignore ILiveData::GetSubType;


%functional_bridge(LiveDataObserver<int>, IntLiveDataObserver, void, (const int &value), (value));
%functional_bridge(LiveDataObserver<std::string>, StringLiveDataObserver, void, (const std::string &value), (value));
%functional_bridge(LiveDataObserver<std::optional<std::string>>, OptionalStringLiveDataObserver, void, (const std::optional<std::string> &value), (value));



%shared_ptr_wrapper(BaseFiledKey);
%std_vector_bridge(std::shared_ptr<BaseFiledKey>);
%template(BaseFiledKeyVector) std::vector<std::shared_ptr<BaseFiledKey>>;

%feature("nodirector") ILiveData;
%feature("nodirector") LiveData<int>;
%feature("nodirector") LiveData<std::string>;
%feature("nodirector") LiveData<std::optional<std::string>>;
%feature("nodirector") MutableLiveData<int>;
%feature("nodirector") MutableLiveData<std::string>;
%feature("nodirector") MutableLiveData<std::optional<std::string>>;

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

%shared_ptr_wrapper(ILiveData);
%shared_ptr_wrapper(LiveData<int>);
%shared_ptr_wrapper(LiveData<std::string>);
%shared_ptr_wrapper(LiveData<std::optional<std::string>>);
%shared_ptr_wrapper(MutableLiveData<int>);
%shared_ptr_wrapper(MutableLiveData<std::string>);
%shared_ptr_wrapper(MutableLiveData<std::optional<std::string>>);

%inheritance_class(ILiveData, LiveData<int>, LiveData<std::string>, LiveData<std::optional<std::string>>);

%include "field/LiveData.h"
%include "field/FieldKeys.h"
%include "field/FieldDataModel.h"



%template(IntFiledKey) FiledKey<int>;
%template(StringFiledKey) FiledKey<std::string>;
%template(OptionalStringFiledKey) FiledKey<std::optional<std::string>>;

%template(IntLiveData) LiveData<int>;
%template(StringLiveData) LiveData<std::string>;
%template(OptionalStringLiveData) LiveData<std::optional<std::string>>;

%template(MutableIntLiveData) MutableLiveData<int>;
%template(MutableStringLiveData) MutableLiveData<std::string>;
%template(MutableOptionalStringLiveData) MutableLiveData<std::optional<std::string>>;