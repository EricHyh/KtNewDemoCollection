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


//%typemap(jstype) std::optional<std::string> "String"  //Java层 Java函数类型
//%typemap(jtype) std::optional<std::string> "String"   //java层 JNI函数参数类型
//%typemap(jni) std::optional<std::string> "jstring"    //C++层  JNI函数参数类型
//
//%typemap(javain) (std::optional<std::string>) "$javainput"
//
////C++层，函数参数，java类型转C++类型
//%typemap(in) std::optional<std::string> %{
//const char* strChars = jenv->GetStringUTFChars(jarg$argnum, nullptr);
//$1 = std::make_shared<std::string>(strChars);
//jenv->ReleaseStringUTFChars(jarg$argnum, strChars);
//%}




#endif // OPTIONAL_CONFIG