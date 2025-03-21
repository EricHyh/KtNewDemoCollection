#ifndef INT_ARRAY_CONFIG
#define INT_ARRAY_CONFIG


%define %int_array_bridge()

%typemap(jstype) std::vector<int32_t>, std::vector<int32_t>& "int[]"  //Java层 Java函数类型

%typemap(jtype) std::vector<int32_t>, std::vector<int32_t>& "int[]"   //Java层 JNI函数参数类型

%typemap(jni) std::vector<int32_t>, std::vector<int32_t>& "jintArray"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::vector<int32_t>, std::vector<int32_t>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::vector<int32_t>, std::vector<int32_t>& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::vector<int32_t>, std::vector<int32_t>& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::vector<int32_t>, std::vector<int32_t>& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::vector<int32_t> %{
std::vector<int32_t> $1_temp;
jsize len = jenv->GetArrayLength($input);
$1_temp.resize(len);
jenv->GetIntArrayRegion($input, 0, len, (jint*)$1_temp.data());
$1 = std::move($1_temp);
%}
%typemap(in) std::vector<int32_t>& %{
std::vector<int32_t> $1_temp;
jsize len = jenv->GetArrayLength($input);
$1_temp.resize(len);
jenv->GetIntArrayRegion($input, 0, len, (jint*)$1_temp.data());
$1 = &$1_temp;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::vector<int32_t> %{
auto size = static_cast<jsize>($1.size());
jintArray jba = jenv->NewIntArray(size);
jenv->SetIntArrayRegion(jba, 0, size, (jint*)$1.data());
$result = jba;
%}
%typemap(out) std::vector<int32_t>& %{
auto size = static_cast<jsize>($1->size());
jintArray jba = jenv->NewIntArray(size);
jenv->SetIntArrayRegion(jba, 0, size, (jint*)$1->data());
$result = jba;
%}

%typemap(directorin, descriptor="[I") std::vector<int32_t>, std::vector<int32_t>& %{
auto size = static_cast<jsize>($1.size());
$input = jenv->NewIntArray(size);
jenv->SetIntArrayRegion($input, 0, size, (jint*)$1.data());
%}

%typemap(directorout, descriptor="[I") std::vector<int32_t> %{
std::vector<int32_t> $result_temp;
jsize len = jenv->GetArrayLength($input);
$result_temp.resize(len);
jenv->GetIntArrayRegion($input, 0, len, (jint*)$result_temp.data());
$result = $result_temp;
%}

%typemap(directorout, descriptor="[I") std::vector<int32_t>& %{
#error "typemaps for $1_type not available"
%}

%enddef

#endif // INT_ARRAY_CONFIG