#ifndef NAMESPACE_CONFIG
#define NAMESPACE_CONFIG

#define IM1(x) "import "#x";"
#define IM2(first, second) ""IM1(first)"\n"IM1(second)""
#define IM3(first, second...) ""IM1(first)"\n"IM2(second)""
#define IM4(first, second...) ""IM1(first)"\n"IM3(second)""
#define IM5(first, second...) ""IM1(first)"\n"IM4(second)""
#define IM6(first, second...) ""IM1(first)"\n"IM5(second)""


%define %nsp_2_java_0(NAMESPACE, PACKAGE)
%module(javabegin="package "#PACKAGE";") NAMESPACE
%enddef

%define %nsp_2_java_1(NAMESPACE, PACKAGE, _1)
%module(javabegin="package "#PACKAGE";\r\n"IM1(_1)"") NAMESPACE
%enddef

%define %nsp_2_java_2(NAMESPACE, PACKAGE, _1, _2)
%module(javabegin="package "#PACKAGE";\r\n"IM2(_1, _2)"") NAMESPACE
%enddef

%define %nsp_2_java_3(NAMESPACE, PACKAGE, _1, _2, _3)
%module(javabegin="package "#PACKAGE";\r\n"IM3(_1, _2, _3)"") NAMESPACE
%enddef

%define %nsp_2_java_4(NAMESPACE, PACKAGE, _1, _2, _3, _4)
%module(javabegin="package "#PACKAGE";\r\n"IM4(_1, _2, _3, _4)"") NAMESPACE
%enddef

%define %nsp_2_java_5(NAMESPACE, PACKAGE, _1, _2, _3, _4, _5)
%module(javabegin="package "#PACKAGE";\r\n"IM5(_1, _2, _3, _4, _5)"") NAMESPACE
%enddef

%define %nsp_2_java_6(NAMESPACE, PACKAGE, _1, _2, _3, _4, _5, _6)
%module(javabegin="package "#PACKAGE";\r\n"IM6(_1, _2, _3, _4, _5, _6)"") NAMESPACE
%enddef

#endif