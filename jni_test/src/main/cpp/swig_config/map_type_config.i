#ifndef ITERATOR_TYPE_CONFIG
#define ITERATOR_TYPE_CONFIG


%define %std_map_bridge(c_map_type, j_map_type)

%typemap(jstype) c_map_type::iterator, c_map_type::iterator& "$typemap(jstype, c_map_type).Iterator"  //Java层 Java函数类型

%typemap(jtype) c_map_type::iterator, c_map_type::iterator& "long"   //Java层 JNI函数参数类型

%typemap(jni) c_map_type::iterator, c_map_type::iterator& "jlong"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) c_map_type::iterator, c_map_type::iterator& "Iterator.getCPtr($javainput)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) c_map_type::iterator, c_map_type::iterator& {
    return new Iterator($jnicall, true);
  }
  

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) c_map_type::iterator %{
$1 = *(c_map_type::iterator*)jarg$argnum;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) c_map_type::iterator %{
*(c_map_type::iterator **)&$result = new c_map_type::iterator($1);
%}




%typemap(jstype) c_map_type, c_map_type& "j_map_type"  //Java层 Java函数类型
%typemap(jtype) c_map_type, c_map_type& "long"   //Java层 JNI函数参数类型
%typemap(jni) c_map_type, c_map_type& "jlong"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) c_map_type, c_map_type& "$typemap(jstype, c_map_type).getCPtr($javainput)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) c_map_type, c_map_type& {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, c_map_type)(cPtr, true);
  }


//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) c_map_type "($jniinput == 0) ? null : new $typemap(jstype, c_map_type)($jniinput, true)"
%typemap(javadirectorin) c_map_type& "($jniinput == 0) ? null : new $typemap(jstype, c_map_type)($jniinput, false)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) c_map_type, c_map_type& "$typemap(jstype, c_map_type).getCPtr($javacall)"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) c_map_type %{
auto *argp$argnum = *(c_map_type **)&$input;
if (!argp$argnum) {
  SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null c_map_type");
  return ;
}
$1 = *argp$argnum;
%}

%typemap(in) c_map_type& %{
$1 = *(c_map_type **)&$input;
if (!$1) {
  SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null c_map_type");
}
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) c_map_type %{
*(c_map_type **)&$result = new c_map_type($1);
%}

%typemap(out) c_map_type& %{
*(c_map_type **)&$result = $1;
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, c_map_type);") c_map_type %{
$input = 0;
*((c_map_type **)&$input) = new c_map_type(SWIG_STD_MOVE($1));
%}
%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, c_map_type);") c_map_type& %{
*(c_map_type **)&$input = (c_map_type *)&$1;
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_map_type);") c_map_type %{
auto *argp = *(std::map< TestEnum1,TestVariant> **)&$input;
if (!argp) {
  SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Unexpected null return for type c_map_type");
  return $1;
}
$1 = *argp;
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_map_type);") c_map_type& %{
#error "typemaps for $1_type not available"
%}

%template(j_map_type) c_map_type;

%enddef

#endif // ITERATOR_TYPE_CONFIG