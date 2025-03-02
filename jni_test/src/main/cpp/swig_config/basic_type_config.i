#ifndef BASIC_TYPE_CONFIG
#define BASIC_TYPE_CONFIG


%define %basic_type_map(c_type, j_type, jni_type, desc)

%typemap(jstype) c_type, c_type& "j_type"  //Java层 Java函数类型
%typemap(jtype) c_type, c_type& "j_type"   //Java层 JNI函数参数类型
%typemap(jni) c_type, c_type& "jni_type"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) c_type, c_type& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) c_type, c_type& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) c_type, c_type& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) c_type, c_type& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) c_type %{
$1 = $input;
%}

%typemap(in) c_type& %{
$1 = ($1_ltype)&$input;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) c_type %{
$result = $1;
%}
%typemap(out) c_type& %{
*(c_type **)& = $1;
%}

%typemap(directorin, descriptor="desc") c_type, c_type& %{
$input = $1;
%}

%typemap(directorout, descriptor="desc") c_type %{
$1 = $input;
%}

%typemap(directorout, descriptor="desc") c_type& %{
#error "typemaps for $1_type not available"
%}

%enddef

%define %optional_basic_type_map(c_type, j_type, jni_type, desc)

%typemap(jstype) std::optional<c_type>, std::optional<c_type>& "j_type"  //Java层 Java函数类型
%typemap(jtype) std::optional<c_type>, std::optional<c_type>& "j_type"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<c_type>, std::optional<c_type>& "jni_type"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<c_type>, std::optional<c_type>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<c_type>, std::optional<c_type>& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<c_type>, std::optional<c_type>& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<c_type>, std::optional<c_type>& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<c_type> %{
$1 = std::make_optional<c_type>($input);
%}

%typemap(in) std::optional<c_type>& %{
auto $1_temp = std::make_optional<c_type>($input);
$1 = &$1_temp;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<c_type> %{
if ($1.has_value()) {
  $result = $1.value();
} else {
  $result = 0;
}
%}
%typemap(out) std::optional<c_type>& %{
if ($1.has_value()) {
  $result = $1.value();
} else {
  $result = 0;
}
%}

%typemap(directorin, descriptor="desc") std::optional<c_type>, std::optional<c_type>& %{
if ($1.has_value()) {
  $input = $1.value();
} else {
  $input = 0;
}
%}

%typemap(directorout, descriptor="desc") std::optional<c_type> %{
$1 = std::make_optional<c_type>($input);
%}

%typemap(directorout, descriptor="desc") std::optional<c_type>& %{
#error "typemaps for $1_type not available"
%}

%enddef


%basic_type_map(int64_t, long, jlong, J);
%basic_type_map(uint64_t, long, jlong, J);
%basic_type_map(uintptr_t, long, jlong, J);
%optional_basic_type_map(int64_t, long, jlong, J);
%optional_basic_type_map(uint64_t, long, jlong, J);
%optional_basic_type_map(uintptr_t, long, jlong, J);

%basic_type_map(int32_t, int, jint, I);
%basic_type_map(uint32_t, int, jint, I);
%optional_basic_type_map(int32_t, int, jint, I);
%optional_basic_type_map(uint32_t, int, jint, I);

%basic_type_map(int16_t, short, jshort, S);
%basic_type_map(uint16_t, short, jshort, S);
%optional_basic_type_map(int16_t, short, jshort, S);
%optional_basic_type_map(uint16_t, short, jshort, S);

%basic_type_map(int8_t, byte, jbyte, B);
%basic_type_map(uint8_t, byte, jbyte, B);
%optional_basic_type_map(int8_t, byte, jbyte, B);
%optional_basic_type_map(uint8_t, byte, jbyte, B);

#endif // BASIC_TYPE_CONFIG