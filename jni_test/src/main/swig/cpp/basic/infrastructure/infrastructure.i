%include "../../../scripts/config/common_swig_config.i"
%module FINInfrastructure

%jni_package_import_0(basic.infrastructure)

%java_package_import_0(std::vector<std::string>, basic.infrastructure)

%template(StringVector) std::vector<std::string>;
