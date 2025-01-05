#ifndef OPTIONAL_CONFIG
#define OPTIONAL_CONFIG

//%{
//#include <optional>
//
//template<typename T>
//struct OptionalWrapper {
//    OptionalWrapper() : opt(std::nullopt) {}
//    OptionalWrapper(T val) : opt(std::move(val)) {}
//
//    bool has_value() const { return opt.has_value(); }
//    const T& value() const { return opt.value(); }
//
//    std::optional<T> opt;
//};
//%}

%define %simple_optional(original_type, target_type)

%typemap(jstype) std::optional<original_type>, std::optional<original_type>& "target_type"  //Java层 Java函数类型
%typemap(jtype) std::optional<original_type>, std::optional<original_type>& "long"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<original_type>, std::optional<original_type>& "jlong"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
//%typemap(javain) std::optional<original_type>, std::optional<original_type>& "$javainput"
%typemap(javain) std::optional<original_type>, std::optional<original_type>& "$typemap(jstype, original_type).getCPtr($javainput)"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<original_type>, std::optional<original_type>& {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, original_type)(cPtr, true);
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<original_type>, std::optional<original_type>& "($jniinput == 0) ? null : new $typemap(jstype, original_type)($jniinput, true)"

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<original_type>, std::optional<original_type>& "$typemap(jstype, original_type).getCPtr($javacall)"


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<original_type> %{
original_type* jarg$argnum_element = ((std::shared_ptr< original_type >*)jarg$argnum)->get();
if (jarg$argnum_element) {
  $1 = *jarg$argnum_element;
} else {
  $1 = std::nullopt;
}

%}
%typemap(in) std::optional<original_type>& %{
original_type* jarg$argnum_element = ((std::shared_ptr< original_type >*)jarg$argnum)->get();
if (jarg$argnum_element) {
  std::optional<FINFeatureFlagVariant> tmp_arg2 = std::make_optional<FINFeatureFlagVariant>(*jarg$argnum_element);
  $1 = &tmp_arg2;
} else {
  std::optional<FINFeatureFlagVariant> tmp_arg2 = std::nullopt;
  $1 = &tmp_arg2;
}
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<original_type> %{
if ((&$1)->has_value()) {
  original_type* value_ptr = new original_type((&$1)->value());
  *(std::shared_ptr<original_type> **)&$result = new std::shared_ptr<original_type>(value_ptr);
}
%}
%typemap(out) std::optional<original_type>& %{
if ($1->has_value()) {
  original_type* value_ptr = new original_type($1->value());
  *(std::shared_ptr<original_type>**)&$result = new std::shared_ptr<original_type>(value_ptr);
}
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") std::optional<original_type>, std::optional<original_type>& %{
if ($1.has_value()) {
  *(shared_ptr<original_type>**)&$input = new shared_ptr<original_type>(new original_type($1.value()));
} else {
  $input = 0;
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, original_type);") std::optional<original_type> %{
if ($input == 0) {
  $1 = std::nullopt;
} else {
  $1 = *((std::shared_ptr<original_type>*)$input)->get();
}
%}
%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, original_type);") std::optional<original_type>& %{
#error "typemaps for $1_type not available"
%}


%enddef

#endif // OPTIONAL_CONFIG