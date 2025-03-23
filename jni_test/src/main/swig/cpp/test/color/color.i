%include "../../../scripts/config/common_swig_config.i"
%module ColorModule

%{
#include "color/TestColor.h"
%}

%jni_package_import_0(test.color);

// region 股票模型

%java_package_import_0(ITestColor, test.color);
%java_package_import_0(N2CTestColor, test.color);
%java_package_import_0(TestColorFactory, test.color);

%shared_ptr_wrapper(ITestColor)
%shared_ptr_wrapper(N2CTestColor)

%include "color/TestColor.h"