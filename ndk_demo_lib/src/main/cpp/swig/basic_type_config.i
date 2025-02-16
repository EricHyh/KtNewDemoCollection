#ifndef BASIC_TYPE_CONFIG
#define BASIC_TYPE_CONFIG

%typemap(jstype) int64_t, int64_t&, uint64_t, uint64_t& "long"  //Java层 Java函数类型
%typemap(jtype) int64_t, int64_t&, uint64_t, uint64_t& "long"   //Java层 JNI函数参数类型
%typemap(jni) int64_t, int64_t&, uint64_t, uint64_t& "jlong"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) int64_t, int64_t&, uint64_t, uint64_t& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) int64_t, int64_t&, uint64_t, uint64_t& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) int64_t, int64_t&, uint64_t, uint64_t& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) int64_t, int64_t&, uint64_t, uint64_t& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) int64_t, uint64_t %{
$1 = jarg$argnum;
%}

%typemap(in) int64_t&, uint64_t& %{
*$1 = jarg$argnum;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) int64_t, uint64_t %{
$result = $1;
%}
%typemap(out) int64_t&, uint64_t& %{
*$result = $1;
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, int64_t);") int64_t, int64_t&, uint64_t, uint64_t& %{
$input = $1;
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, int64_t);") int64_t, uint64_t %{
$1 = $input;
%}
%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, int64_t);") int64_t&, uint64_t& %{
#error "typemaps for $1_type not available"
%}


#endif // BASIC_TYPE_CONFIG