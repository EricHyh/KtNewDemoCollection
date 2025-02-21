#ifndef BYTE_ARRAY_CONFIG
#define BYTE_ARRAY_CONFIG


%define %byte_array_bridge()

%typemap(jstype) std::vector<uint8_t>, std::vector<uint8_t>& "byte[]"  //Java层 Java函数类型

%typemap(jtype) std::vector<uint8_t>, std::vector<uint8_t>& "byte[]"   //Java层 JNI函数参数类型

%typemap(jni) std::vector<uint8_t>, std::vector<uint8_t>& "jbyteArray"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::vector<uint8_t>, std::vector<uint8_t>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::vector<uint8_t>, std::vector<uint8_t>& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::vector<uint8_t>, std::vector<uint8_t>& "$jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::vector<uint8_t>, std::vector<uint8_t>& "$javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::vector<uint8_t>, std::vector<uint8_t>& %{
jsize len = jenv->GetArrayLength($input);
$1.resize(len);
jenv->GetByteArrayRegion($input, 0, len, (jbyte*)$1.data());
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::vector<uint8_t>, std::vector<uint8_t>& %{
jbyteArray jba = jenv->NewByteArray($1.size());
jenv->SetByteArrayRegion(jba, 0, $1.size(), (jbyte*)$1.data());
$result = jba;
%}

%typemap(directorin, descriptor="[B") std::vector<uint8_t>, std::vector<uint8_t>& %{
$input = jenv->NewByteArray($1.size());
jenv->SetByteArrayRegion($input, 0, $1.size(), (jbyte*)$1.data());
%}

%typemap(directorout, descriptor="[B") std::vector<uint8_t> %{
jsize len = jenv->GetArrayLength($input);
(&$result)->resize(len);
jenv->GetByteArrayRegion($input, 0, len, (jbyte*)(&$result)->data());
%}

%typemap(directorout, descriptor="[B") std::vector<uint8_t>& %{
#error "typemaps for $1_type not available"
%}

%enddef

#endif // BYTE_ARRAY_CONFIG