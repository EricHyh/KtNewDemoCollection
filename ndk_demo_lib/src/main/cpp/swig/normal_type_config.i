#ifndef NORMAL_TYPE_CONFIG
#define NORMAL_TYPE_CONFIG

%define %shared_type_bridge(original_type, c_target_type, j_target_type)

%typemap(jstype) original_type, original_type& "j_target_type"  //Java层 Java函数类型
%typemap(jtype) original_type, original_type& "long"   //Java层 JNI函数参数类型
%typemap(jni) original_type, original_type& "jlong"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) original_type, original_type& "$typemap(jstype, original_type).getCPtr($javainput)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) original_type, original_type& {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, original_type)(cPtr, true);
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) original_type, original_type& "($jniinput == 0) ? null : new $typemap(jstype, original_type)($jniinput, true)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) original_type, original_type& "$typemap(jstype, original_type).getCPtr($javacall)"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) original_type %{
c_target_type* jarg$argnum_element = ((std::shared_ptr<c_target_type>*)jarg$argnum)->get();
if (jarg$argnum_element) {
  $1 = jarg$argnum_element->m_original;
}
%}

%typemap(in) original_type& %{
c_target_type* jarg$argnum_element = ((std::shared_ptr<c_target_type>*)jarg$argnum)->get();
if (jarg$argnum_element) {
  $1 = &jarg$argnum_element->m_original;
}
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) original_type %{
c_target_type* value_ptr = new c_target_type($1);
*(std::shared_ptr<c_target_type> **)&$result = new std::shared_ptr<c_target_type>(value_ptr);
%}
%typemap(out) original_type& %{
c_target_type* value_ptr = new c_target_type(*$1);
*(std::shared_ptr<c_target_type>**)&$result = new std::shared_ptr<c_target_type>(value_ptr);
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") original_type, original_type& %{
*(shared_ptr<c_target_type>**)&jvariant = new shared_ptr<c_target_type>(new c_target_type(variant));
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, original_type);") original_type %{
if ($input) {
  $1 = ((std::shared_ptr<c_target_type>*)$input)->get()->m_original;
}
%}
%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, original_type);") original_type& %{
#error "typemaps for $1_type not available"
%}

%enddef

#endif // NORMAL_TYPE_CONFIG