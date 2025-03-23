%include "../../../scripts/config/common_swig_config.i"
%module ItemModule

%import "infrastructure/infrastructure.i"
//
%{
#include "model/N2CTestItem.h"
#include "model/N2CItemIcon.h"
#include "model/TestItem.h"
#include "model/ItemIcon.h"
%}


%jni_package_import_0(test.item);

%java_package_import_0(ITestItem, test.item);
%java_package_import_0(IItemIcon, test.item);
%java_package_import_0(N2CTestItem, test.item);
%java_package_import_0(N2CItemIcon, test.item);
%java_package_import_0(std::vector<std::shared_ptr<IItemIcon>>, test.item);

%java_package_import_0(IC2NTestItemFactory, test.item);
%java_package_import_0(C2NTestItemFactory, test.item);


%shared_ptr_wrapper(ITestItem)
%shared_ptr_wrapper(IItemIcon)
%shared_ptr_wrapper(N2CTestItem)
%shared_ptr_wrapper(N2CItemIcon)

%director_shared_ptr_wrapper(ITestItem);

%template(IItemIconVector) std::vector<std::shared_ptr<IItemIcon>>;


%include "model/ItemIcon.h"
%include "model/TestItem.h"
%include "model/N2CTestItem.h"
%include "model/N2CItemIcon.h"



