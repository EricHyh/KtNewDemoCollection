#ifndef ENUM_TYPE_CONFIG
#define ENUM_TYPE_CONFIG


%define %enum_bridge(original_type, target_type)

%typemap(jstype) original_type, original_type& "target_type"  //Java层 Java函数类型

%typemap(jtype) original_type, original_type& "int"   //Java层 JNI函数参数类型

%typemap(jni) original_type, original_type& "jint"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) original_type, original_type& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) original_type, original_type& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) original_type, original_type& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) original_type, original_type& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) original_type %{
$1 = jarg$argnum;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) original_type %{
$result = $1;
%}

%typemap(out) original_type& %{
*$result = $1;
%}

%typemap(directorin, descriptor="I") original_type, original_type& %{
$input = $1;
%}

%typemap(directorout, descriptor="I") original_type %{
$1 = $input;
%}
%typemap(directorout, descriptor="I") original_type& %{
#error "typemaps for $1_type not available"
%}

%enddef

#endif // ENUM_TYPE_CONFIG