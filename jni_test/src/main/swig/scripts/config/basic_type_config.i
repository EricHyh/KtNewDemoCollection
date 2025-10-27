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
%basic_type_map(uint32_t, long, jlong, J);
%optional_basic_type_map(int64_t, long, jlong, J);
%optional_basic_type_map(uint64_t, long, jlong, J);
%optional_basic_type_map(uintptr_t, long, jlong, J);
%optional_basic_type_map(uint32_t, long, jlong, J);

%basic_type_map(int32_t, int, jint, I);
%basic_type_map(uint16_t, int, jint, I);
%optional_basic_type_map(int32_t, int, jint, I);
%optional_basic_type_map(uint16_t, int, jint, I);

%basic_type_map(int16_t, short, jshort, S);
%basic_type_map(uint8_t, short, jshort, S);
%optional_basic_type_map(int16_t, short, jshort, S);
%optional_basic_type_map(uint8_t, short, jshort, S);

%basic_type_map(int8_t, byte, jbyte, B);
%optional_basic_type_map(int8_t, byte, jbyte, B);



%typemap(jstype) std::optional<double>, std::optional<double>& "Double"  //Java层 Java函数类型
%typemap(jtype) std::optional<double>, std::optional<double>& "double"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<double>, std::optional<double>& "jdouble"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<double>, std::optional<double>& "$javainput == null ? Double.NaN : $javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<double>, std::optional<double>& {
    double temp = $jnicall;
    return Double.isNaN(temp) ? null : temp;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<double>, std::optional<double>& "Double.isNaN($jniinput) ? null : $jniinput"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<double>, std::optional<double>& "$javacall == null ? Double.NaN : $javacall"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<double> %{
if (std::isnan($input)) {
  $1 = std::nullopt;
} else {
  $1 = std::make_optional<double>($input);
}
%}

%typemap(in) std::optional<double>& %{
auto $1_temp = std::isnan($input) ? std::nullopt : std::make_optional<double>($input);
$1 = &$1_temp;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<double> %{
if ($1.has_value()) {
  $result = $1.value();
} else {
  $result = std::numeric_limits<double>::quiet_NaN();
}
%}
%typemap(out) std::optional<double>& %{
if ($1->has_value()) {
  $result = $1->value();
} else {
  $result = std::numeric_limits<double>::quiet_NaN();
}
%}

%typemap(directorin, descriptor="Ljava/lang/Double;") std::optional<double>, std::optional<double>& %{
if ($1.has_value()) {
  $input = $1.value();
} else {
  $input = std::numeric_limits<double>::quiet_NaN();
}
%}

%typemap(directorout, descriptor="Ljava/lang/Double;") std::optional<double> %{
if (std::isnan($input)) {
  $1 = std::nullopt;
} else {
  $1 = std::make_optional<double>($input);
}

%}

%typemap(directorout, descriptor="D") std::optional<double>& %{
#error "typemaps for $1_type not available"
%}







%typemap(jstype) std::optional<bool>, std::optional<bool>& "Boolean" //Java层 Java函数类型
%typemap(jtype) std::optional<bool>, std::optional<bool>& "byte"     //Java层 JNI函数参数类型
%typemap(jni) std::optional<bool>, std::optional<bool>& "jbyte"      //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<bool>, std::optional<bool>& "$javainput == null ? (byte) 2 : ($javainput ? (byte) 1 : 0)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<bool>, std::optional<bool>& {
    switch($jnicall){
      case 0: {
        return false;
      }
      case 1: {
        return true;
      }
      default: {
        return null;
      }
    }
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<bool>, std::optional<bool>& "$jniinput == 0 ? Boolean.FALSE : ($jniinput == 1 ? Boolean.TRUE : null)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<bool>, std::optional<bool>& "$javacall == null ? (byte) 2 : ($javacall ? (byte) 1 : 0)"

//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<bool> %{
switch ($input) {
  case 0: {
    $1 = std::make_optional<bool>(false);
    break;
  }
  case 1: {
    $1 = std::make_optional<bool>(true);
    break;
  }
  default: {
    $1 = std::nullopt;
    break;
  }
}
%}

%typemap(in) std::optional<bool>& %{
auto $1_temp = $input == 0 ? std::make_optional<bool>(false) : ($input == 0 ? std::make_optional<bool>(true) : std::nullopt);
$1 = &$1_temp;
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<bool> %{
if ($1.has_value()) {
 $result = $1.value() ? 1 : 0;
} else {
 $result = 2;
}
%}
%typemap(out) std::optional<bool>& %{
if ($1->has_value()) {
  $result = $1->value() ? 1 : 0;
} else {
  $result = 2;
}
%}

%typemap(directorin, descriptor="Ljava/lang/Boolean;") std::optional<bool>, std::optional<bool>& %{
if ($1.has_value()) {
  $input = $1.value() ? 1 : 0;
} else {
  $input = 2;
}
%}

%typemap(directorout, descriptor="Ljava/lang/Boolean;") std::optional<bool> %{
switch ($input) {
  case 0: {
    $1 = std::make_optional<bool>(false);
    break;
  }
  case 1: {
    $1 = std::make_optional<bool>(true);
    break;
  }
  default: {
    $1 = std::nullopt;
  break;
}
}

%}

%typemap(directorout, descriptor="Ljava/lang/Boolean;") std::optional<bool>& %{
#error "typemaps for $1_type not available"
%}


#endif // BASIC_TYPE_CONFIG