#ifndef STRING_CONFIG
#define STRING_CONFIG

//-------------------------------------std::optional<std::string> 转换适配-----------------------------------------------

%typemap(jstype) std::optional<std::string>, std::optional<std::string>& "String"  //Java层 Java函数类型
%typemap(jtype) std::optional<std::string>, std::optional<std::string>& "String"   //Java层 JNI函数参数类型
%typemap(jni) std::optional<std::string>, std::optional<std::string>& "jstring"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::optional<std::string>, std::optional<std::string>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::optional<std::string>, std::optional<std::string>& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::optional<std::string>, std::optional<std::string>& %{$jniinput%}

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::optional<std::string>, std::optional<std::string>& "$javacall"


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::optional<std::string> %{
const char* c_result_pstr = jenv->GetStringUTFChars(jarg$argnum, nullptr);
$1 = std::make_optional<std::string>(c_result_pstr);
jenv->ReleaseStringUTFChars(jarg$argnum, c_result_pstr);
%}
%typemap(in) std::optional<std::string>& %{
const char* c_result_pstr = jenv->GetStringUTFChars(jarg$argnum, nullptr);
std::optional< std::string > temp_arg$argnum = std::make_optional<std::string>(c_result_pstr);
$1 = &temp_arg$argnum;
jenv->ReleaseStringUTFChars(jarg$argnum, c_result_pstr);
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::optional<std::string> %{
if ($1.has_value()) {
    $result = jenv->NewStringUTF($1.value().c_str());
} else {
    $result = nullptr;
}
%}
%typemap(out) std::optional<std::string>& %{
if ((*$1).has_value()) {
    $result = jenv->NewStringUTF((*$1).value().c_str());
} else {
    $result = nullptr;
}
%}


%typemap(directorin, descriptor="Ljava/lang/String;") std::optional<std::string>, std::optional<std::string>& %{
if ($1.has_value()) {
    $input = jenv->NewStringUTF($1.value().c_str());
} else {
    $input = nullptr;
}
Swig::LocalRefGuard str_refguard(jenv, $input);
%}

%typemap(directorout, descriptor="Ljava/lang/String;") std::optional<std::string> %{
if ($input == nullptr) {
    $1 = std::nullopt;
} else {
    const char *c_result_pstr = (const char *)jenv->GetStringUTFChars($input, 0);
    if (!c_result_pstr) return $1;
    $1 = std::make_optional<std::string>(c_result_pstr);
    jenv->ReleaseStringUTFChars($input, c_result_pstr);
}
%}
%typemap(directorout, descriptor="Ljava/lang/String;") std::optional<std::string>& %{
if ($input == nullptr) {
    *$1 = std::nullopt;
} else {
    const char *c_result_pstr = (const char *)jenv->GetStringUTFChars($input, 0);
    if (!c_result_pstr) return *$1;
    *$1 = std::make_optional<std::string>(c_result_pstr);
    jenv->ReleaseStringUTFChars($input, c_result_pstr);
}
%}


//-------------------------------------std::optional<std::string> 转换适配-----------------------------------------------



//-------------------------------------std::shared_ptr<std::string> 转换适配---------------------------------------------

%typemap(jstype) std::shared_ptr<std::string>, std::shared_ptr<std::string>& "String"  //Java层 Java函数类型
%typemap(jtype) std::shared_ptr<std::string>, std::shared_ptr<std::string>& "String"   //Java层 JNI函数参数类型
%typemap(jni) std::shared_ptr<std::string>, std::shared_ptr<std::string>& "jstring"    //C++层  JNI函数参数类型

//Java层，Java调用JNI函数时，对函数参数的转换
%typemap(javain) std::shared_ptr<std::string>, std::shared_ptr<std::string>& "$javainput"

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::shared_ptr<std::string>, std::shared_ptr<std::string>& {
    return $jnicall;
  }

//Java层，C++调用Java函数时，对函数参数的转换
%typemap(javadirectorin) std::shared_ptr<std::string>, std::shared_ptr<std::string>& %{$jniinput%}

//Java层，C++调用Java函数时，对返回值的转换
%typemap(javadirectorout) std::shared_ptr<std::string>, std::shared_ptr<std::string>& "$javacall"


//C++层，JNI函数参数，java类型转C++类型
%typemap(in) std::shared_ptr<std::string> %{
const char* c_result_pstr = jenv->GetStringUTFChars(jarg$argnum, nullptr);
$1 = std::make_shared<std::string>(c_result_pstr);
jenv->ReleaseStringUTFChars(jarg$argnum, c_result_pstr);
%}
%typemap(in) std::shared_ptr<std::string>& %{
const char* c_result_pstr = jenv->GetStringUTFChars(jarg$argnum, nullptr);
*$1 = std::make_shared<std::string>(c_result_pstr);
jenv->ReleaseStringUTFChars(jarg$argnum, c_result_pstr);
%}

//C++层，JNI函数返回值，C++类型转java类型
%typemap(out) std::shared_ptr<std::string> %{
if (&$1) {
    $result = jenv->NewStringUTF((&$1)->get()->c_str());
} else {
    $result = nullptr;
}
%}
%typemap(out) std::shared_ptr<std::string>& %{
if ($1) {
    $result = jenv->NewStringUTF($1->get()->c_str());
} else {
    $result = nullptr;
}
%}


%typemap(directorin, descriptor="Ljava/lang/String;") std::shared_ptr<std::string>, std::shared_ptr<std::string>& %{
if ($1) {
    $input = jenv->NewStringUTF($1->c_str());
} else {
    $input = nullptr;
}
Swig::LocalRefGuard str_refguard(jenv, $input);
%}

%typemap(directorout, descriptor="Ljava/lang/String;") std::shared_ptr<std::string> %{
if ($input == nullptr) {
    $1 = nullptr;
} else {
    const char *c_result_pstr = (const char *)jenv->GetStringUTFChars($input, 0);
    if (!c_result_pstr) return $1;
    $1 = std::make_shared<std::string>(c_result_pstr);
    jenv->ReleaseStringUTFChars($input, c_result_pstr);
}
%}
%typemap(directorout, descriptor="Ljava/lang/String;") std::shared_ptr<std::string>& %{
if ($input == nullptr) {
    $1 = nullptr;
} else {
    const char *c_result_pstr = (const char *)jenv->GetStringUTFChars($input, 0);
    if (!c_result_pstr) return *$1;
    *$1 = std::make_shared<std::string>(c_result_pstr);
    jenv->ReleaseStringUTFChars($input, c_result_pstr);
}
%}

//-------------------------------------std::shared_ptr<std::string> 转换适配---------------------------------------------

#endif // STRING_CONFIG