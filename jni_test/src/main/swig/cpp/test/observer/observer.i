%include "../../../scripts/config/common_swig_config.i"
%module ObserverModule

%byte_array_bridge()

%{
#include "observer/ObserverManager.h"
#include "JNITestEntrance.h"
%}

%jni_package_import_0(test.observer);


%java_package_import_0(std::vector<TestObserver2>, test.observer);

%java_package_import_0(TestObserver, test.observer);

%java_package_import_0(TestObserver2, test.observer);

%java_package_import_0(TestObserver2Data, test.observer);
%java_package_import_0(TestEnum1, test.observer);
%java_package_import_0(TestEnum2, test.observer);
%java_package_import_0(TestStruct, test.observer.model);
%java_package_import_0(TestStruct2, test.observer.model);
%java_package_import_0(TestOptional, test.observer);
%java_package_import_0(ITestObserver2, test.observer);
%java_package_import_0(std::vector<TestObserver2>, test.observer);
%java_package_import_0(IObserverManager, test.observer);
%java_package_import_0(ObserverManager, test.observer);

%java_package_import_0(JNITestEntrance, test.observer);

%java_package_import_0(TestStructVariant, test.observer);

%java_package_import_0(std::vector<TestStruct>, test.observer);
%java_package_import_0(std::vector<TestStruct2>, test.observer);


%shared_ptr_wrapper(ITestObserver2);

//using TestStructVariant = std::variant<std::monostate, TestStruct, TestStruct2>;
%variant_with_empty_bridge_2(
        TestStructVariant,
                             TestStructVariantBridge,
        TestStruct, TestStruct,
        TestStruct2, TestStruct2)
%normal_variant_type_bridge(TestStructVariant, TestStructVariantBridge, TestStructVariantBridge)


%functional_bridge(TestObserver, TestObserverBridge, void, (const int &data), (data));
%functional_bridge(TestObserver2, TestObserver2Bridge, void, (const TestObserver2Data &data), (data));
%std_vector_bridge(TestObserver2);
%template(TestObserver2Vector) std::vector<TestObserver2>;


%java_hash_equals(ITestObserver2);

%std_const_vector(TestStruct2, TestStruct2Vector);
%template(TestStruct2Vector) std::vector<TestStruct2>;

%import "std_vector.i"
%template(TestStructVector) std::vector<TestStruct>;

%optional_type_map(TestOptional);
%enum_optional_type_map(TestEnum1);

%rename(ITestObserver2Bridge) ITestObserver2;
%rename(TestOptionalBridge) TestOptional;


%include "observer/ObserverManager.h"
%include "JNITestEntrance.h"

