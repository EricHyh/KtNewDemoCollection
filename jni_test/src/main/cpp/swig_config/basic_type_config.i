#ifndef BASIC_TYPE_CONFIG
#define BASIC_TYPE_CONFIG

%typemap(jstype) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t& "long"  //Java层 Java函数类型
%typemap(jstype) std::optional<int64_t>, std::optional<int64_t>& "long"  //Java层 Java函数类型
%typemap(jstype) int32_t, int32_t&, uint32_t, uint32_t& "int"  //Java层 Java函数类型


%typemap(jtype) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t& "long"   //Java层 JNI函数参数类型
%typemap(jtype) std::optional<int64_t>, std::optional<int64_t>& "long"   //Java层 JNI函数参数类型
%typemap(jtype) int32_t, int32_t&, uint32_t, uint32_t& "int"   //Java层 JNI函数参数类型

%typemap(jni) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t& "jlong"    //C++层  JNI函数参数类型
%typemap(jni) std::optional<int64_t>, std::optional<int64_t>& "jlong"   //Java层 JNI函数参数类型
%typemap(jni) int32_t, int32_t&, uint32_t, uint32_t& "jint"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t&, uint32_t, uint32_t&, int32_t, int32_t& "$javainput"
%typemap(javain) std::optional<int64_t>, std::optional<int64_t>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t&, uint32_t, uint32_t&, int32_t, int32_t& {
    return $jnicall;
  }
%typemap(javaout) std::optional<int64_t>, std::optional<int64_t>& {
    return $jnicall;
  }
//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t&, uint32_t, uint32_t&, int32_t, int32_t& "$jniinput"
%typemap(javadirectorin) std::optional<int64_t>, std::optional<int64_t>& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t&, uint32_t, uint32_t&, int32_t, int32_t& "$javacall"
%typemap(javadirectorout) std::optional<int64_t>, std::optional<int64_t>& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) int64_t, uint64_t, uintptr_t, uint32_t, int32_t %{
$1 = $input;
%}
%typemap(in) std::optional<int64_t> %{
$1 = std::make_optional<int64_t>($input);
%}

%typemap(in) int64_t&, uint64_t&, uintptr_t&, uint32_t&, int32_t& %{
$1 = ($1_ltype)&$input;
%}
%typemap(in) std::optional<int64_t>& %{
*$1 = std::make_optional<int64_t>($input);
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) int64_t, uint64_t, uintptr_t, uint32_t, int32_t %{
$result = $1;
%}
%typemap(out) std::optional<int64_t> %{
if ($1.has_value()) {
  $result = $1.value();
} else {
  $result = 0;
}
%}
%typemap(out) int64_t&, uint64_t&, uintptr_t&, uint32_t&, int32_t& %{
$result = &$1;
%}
%typemap(out) std::optional<int64_t>& %{
if ((*$1).has_value()) {
  $result = (*$1).value();
} else {
  $result = 0;
}
%}

%typemap(directorin, descriptor="J") int64_t, int64_t&, uint64_t, uint64_t&, uintptr_t, uintptr_t& %{
$input = $1;
%}
%typemap(directorin, descriptor="J") std::optional<int64_t>, std::optional<int64_t>& %{
if ($1.has_value()) {
  $input = $1.value();
} else {
  $input = 0;
}
%}
%typemap(directorin, descriptor="I") int32_t, int32_t&, uint32_t, uint32_t& %{
$input = $1;
%}

%typemap(directorout, descriptor="J") int64_t, uint64_t, uintptr_t %{
$1 = $input;
%}
%typemap(directorout, descriptor="J") std::optional<int64_t> %{
$1 = std::make_optional<std::string>($input);
%}
%typemap(directorout, descriptor="I") int32_t, uint32_t %{
$1 = $input;
%}
%typemap(directorout, descriptor="J") int64_t&, uint64_t&, uintptr_t& %{
#error "typemaps for $1_type not available"
%}
%typemap(directorout, descriptor="J") std::optional<int64_t>& %{
#error "typemaps for $1_type not available"
%}
%typemap(directorout, descriptor="I") int32_t&, uint32_t& %{
#error "typemaps for $1_type not available"
%}

#endif // BASIC_TYPE_CONFIG