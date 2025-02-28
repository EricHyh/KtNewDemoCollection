#ifndef VECTOR_TYPE_CONFIG
#define VECTOR_TYPE_CONFIG

%define %std_vector_bridge(c_value_type)

%typemap(jstype) std::vector<c_value_type>::value_type, std::vector<c_value_type>::value_type& "$typemap(jstype, c_value_type)"  //Java层 Java函数类型

%typemap(jtype) std::vector<c_value_type>::value_type, std::vector<c_value_type>::value_type& "$typemap(jtype, c_value_type)"  //Java层 JNI函数参数类型

%typemap(jni) std::vector<c_value_type>::value_type, std::vector<c_value_type>::value_type& "$typemap(jni, c_value_type)"  //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::vector<c_value_type>::value_type, std::vector<c_value_type>::value_type& "$typemap(javain, c_value_type)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::vector<c_value_type>::value_type, std::vector<c_value_type>::value_type& $typemap(javaout, c_value_type)


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::vector<c_value_type>::value_type $typemap(in, c_value_type)

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::vector<c_value_type>::value_type $typemap(out, c_value_type)

%enddef

#endif // VECTOR_TYPE_CONFIG