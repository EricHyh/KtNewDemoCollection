#ifndef JAVA_PACKAGE_AND_IMPORT_CONFIG
#define JAVA_PACKAGE_AND_IMPORT_CONFIG


#define JPAIC_IM(X) import com.hyh.jnitest.##X;
#define JPAIC_PACKAGE(X) package com.hyh.jnitest.##X;


%define %jni_package_import_0(PACKAGE)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
%}
%enddef

%define %jni_package_import_1(PACKAGE, _1)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
%}
%enddef

%define %jni_package_import_2(PACKAGE, _1, _2)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
%}
%enddef

%define %jni_package_import_3(PACKAGE, _1, _2, _3)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
%}
%enddef

%define %jni_package_import_4(PACKAGE, _1, _2, _3, _4)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
%}
%enddef

%define %jni_package_import_5(PACKAGE, _1, _2, _3, _4, _5)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
%}
%enddef

%define %jni_package_import_6(PACKAGE, _1, _2, _3, _4, _5, _6)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
%}
%enddef

%define %jni_package_import_7(PACKAGE, _1, _2, _3, _4, _5, _6, _7)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
%}
%enddef

%define %jni_package_import_8(PACKAGE, _1, _2, _3, _4, _5, _6, _7, _8)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
JPAIC_IM(_8)
%}
%enddef

%define %jni_package_import_9(PACKAGE, _1, _2, _3, _4, _5, _6, _7, _8, _9)
%pragma(java) jniclasspackage="com.hyh.jnitest."#PACKAGE;
%pragma(java) jniclassimports=%{
JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
JPAIC_IM(_8)
JPAIC_IM(_9)
%}
%enddef



%define %java_package_import_0(TYPE, PACKAGE)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

%}
%enddef

%define %java_package_import_1(TYPE, PACKAGE, _1)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
%}
%enddef

%define %java_package_import_2(TYPE, PACKAGE, _1, _2)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
%}
%enddef

%define %java_package_import_3(TYPE, PACKAGE, _1, _2, _3)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
%}
%enddef

%define %java_package_import_4(TYPE, PACKAGE, _1, _2, _3, _4)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
%}
%enddef

%define %java_package_import_5(TYPE, PACKAGE, _1, _2, _3, _4, _5)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
%}
%enddef

%define %java_package_import_6(TYPE, PACKAGE, _1, _2, _3, _4, _5, _6)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
%}
%enddef

%define %java_package_import_7(TYPE, PACKAGE, _1, _2, _3, _4, _5, _6, _7)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
%}
%enddef

%define %java_package_import_8(TYPE, PACKAGE, _1, _2, _3, _4, _5, _6, _7, _8)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
JPAIC_IM(_8)
%}
%enddef

%define %java_package_import_9(TYPE, PACKAGE, _1, _2, _3, _4, _5, _6, _7, _8, _9)
%typemap(javapackage) TYPE, TYPE *, TYPE &, std::shared_ptr<TYPE>, std::shared_ptr<TYPE> *, std::shared_ptr<TYPE> &, std::unique_ptr<TYPE>, std::unique_ptr<TYPE> *, std::unique_ptr<TYPE> & "com.hyh.jnitest.PACKAGE"
%typemap(javaimports) TYPE %{
JPAIC_PACKAGE(PACKAGE)

JPAIC_IM(_1)
JPAIC_IM(_2)
JPAIC_IM(_3)
JPAIC_IM(_4)
JPAIC_IM(_5)
JPAIC_IM(_6)
JPAIC_IM(_7)
JPAIC_IM(_8)
JPAIC_IM(_9)
%}
%enddef

#endif