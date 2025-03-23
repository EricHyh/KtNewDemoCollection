#ifndef OPTIONAL_CONFIG
#define OPTIONAL_CONFIG

%define %optional_type_map(c_type)

%typemap(jstype) std::optional<c_type>, std::optional<c_type>& "$typemap(jstype, c_type)"  //Java层 Java函数类型
%typemap(jtype) std::optional<c_type>, std::optional<c_type>& "$typemap(jtype, c_type)"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<c_type>, std::optional<c_type>& "$typemap(jni, c_type)"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<c_type>, std::optional<c_type>& "$typemap(javain, c_type)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<c_type>, std::optional<c_type>& {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, c_type)(cPtr, true);
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<c_type>, std::optional<c_type>& "($jniinput == 0) ? null : new $typemap(jstype, c_type)($jniinput, true)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<c_type>, std::optional<c_type>& "$typemap(jstype, c_type).getCPtr($javacall)"


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<c_type> %{
if ($input) {
  $1 = std::make_optional<c_type>(*(c_type *) $input);
} else {
  $1 = std::nullopt;
}
%}

%typemap(in) std::optional<c_type>& %{
if ($input) {
  auto $1_temp = std::make_optional<c_type>(*(c_type *) $input);
  $1 = &$1_temp;
} else {
  std::optional<c_type> $1_temp = std::nullopt;
  $1 = &$1_temp;
}
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<c_type> %{
if ($1.has_value()) {
  *(c_type **) &$result = new c_type($1.value());
}
%}
%typemap(out) std::optional<c_type>& %{
if ($1->has_value()) {
  *(c_type **) &$result = new c_type($1->value());
}
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type>, std::optional<c_type>& %{
if ($1.has_value()) {
  *(c_type **) &$input = new c_type($1.value());
} else {
  $input = 0;
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type> %{
if ($input) {
  auto $input_ptr = *(c_type **) &$input;
  $1 = std::make_optional<c_type>(*$input_ptr);
} else {
  $1 = std::nullopt;
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type>& %{
#error "typemaps for $1_type not available"
%}

%enddef


%define %enum_optional_type_map(c_type)

%typemap(jstype) std::optional<c_type>, std::optional<c_type>& "$typemap(jstype, c_type)"  //Java层 Java函数类型
%typemap(jtype) std::optional<c_type>, std::optional<c_type>& "int"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<c_type>, std::optional<c_type>& "jint"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<c_type>, std::optional<c_type>& "$javainput == null ? Integer.MIN_VALUE : $javainput.swigValue()"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<c_type>, std::optional<c_type>& {
    int value = $jnicall;
    if (value == Integer.MIN_VALUE) {
        return null;
    } else {
        return $typemap(jstype, c_type).swigToEnum(value);
    }
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<c_type>, std::optional<c_type>& "$jniinput == Integer.MIN_VALUE ? null : $typemap(jstype, c_type).swigToEnum($jniinput)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<c_type>, std::optional<c_type>& "$javacall"


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<c_type> %{
if ($input != INT32_MIN) {
  $1 = std::make_optional<c_type>((c_type)$input);
} else {
  $1 = std::nullopt;
}
%}

%typemap(in) std::optional<c_type>& %{
if ($input != INT32_MIN) {
  auto $1_temp = std::make_optional<c_type>((c_type)$input);
  $1 = &$1_temp;
} else {
  std::optional<c_type> $1_temp = std::nullopt;
  $1 = &$1_temp;
}
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<c_type> %{
if ($1.has_value()) {
  $result = (jint)$1.value();
} else {
  $result = INT32_MIN;
}
%}
%typemap(out) std::optional<c_type>& %{
if ($1->has_value()) {
  $result = (jint)$1->value();
} else {
  $result = INT32_MIN;
}
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type>, std::optional<c_type>& %{
if ($1.has_value()) {
  $input = (jint)$1.value();
} else {
  $input = INT32_MIN;
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type> %{
if ($input != INT32_MIN) {
  $1 = std::make_optional<c_type>((c_type)$input);
} else {
  $1 = std::nullopt;
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, c_type);") std::optional<c_type>& %{
#error "typemaps for $1_type not available"
%}

%enddef

#endif // OPTIONAL_CONFIG