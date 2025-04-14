#ifndef NAMESPACE_CONFIG
#define NAMESPACE_CONFIG

// 全局搜索，工程配置替换

#define NC_IM1(x) "pre_import com.hyh.jnitest."#x";"
#define NC_IM2(first, second) ""NC_IM1(first)"\n"NC_IM1(second)""
#define NC_IM3(first, second...) ""NC_IM1(first)"\n"NC_IM2(second)""
#define NC_IM4(first, second...) ""NC_IM1(first)"\n"NC_IM3(second)""
#define NC_IM5(first, second...) ""NC_IM1(first)"\n"NC_IM4(second)""
#define NC_IM6(first, second...) ""NC_IM1(first)"\n"NC_IM5(second)""

#define NC_JPAIC_IM(X) import com.hyh.jnitest.##X;

%define %nsp_2_java_0(NAMESPACE, PACKAGE)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%enddef

%define %nsp_2_java_1(NAMESPACE, PACKAGE, _1)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM1(_1)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
%}
%enddef

%define %nsp_2_java_2(NAMESPACE, PACKAGE, _1, _2)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM2(_1, _2)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
NC_JPAIC_IM(_2)
%}
%enddef

%define %nsp_2_java_3(NAMESPACE, PACKAGE, _1, _2, _3)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM3(_1, _2, _3)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
NC_JPAIC_IM(_2)
NC_JPAIC_IM(_3)
%}
%enddef

%define %nsp_2_java_4(NAMESPACE, PACKAGE, _1, _2, _3, _4)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM4(_1, _2, _3, _4)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
NC_JPAIC_IM(_2)
NC_JPAIC_IM(_3)
NC_JPAIC_IM(_4)
%}
%enddef

%define %nsp_2_java_5(NAMESPACE, PACKAGE, _1, _2, _3, _4, _5)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM5(_1, _2, _3, _4, _5)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
NC_JPAIC_IM(_2)
NC_JPAIC_IM(_3)
NC_JPAIC_IM(_4)
NC_JPAIC_IM(_5)
%}
%enddef

%define %nsp_2_java_6(NAMESPACE, PACKAGE, _1, _2, _3, _4, _5, _6)
%module(javabegin="pre_package com.hyh.jnitest."#PACKAGE";\r\n"NC_IM6(_1, _2, _3, _4, _5, _6)"") NAMESPACE
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE""
%pragma(java) jniclassimports=%{
NC_JPAIC_IM(_1)
NC_JPAIC_IM(_2)
NC_JPAIC_IM(_3)
NC_JPAIC_IM(_4)
NC_JPAIC_IM(_5)
NC_JPAIC_IM(_6)
%}
%enddef

#endif