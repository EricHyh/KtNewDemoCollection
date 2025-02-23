#ifndef SHARED_PTR_SWIG_CONFIG
#define SHARED_PTR_SWIG_CONFIG


// 智能指针参数包装
%define %shared_ptr_wrapper(TYPE) //shared_ptr_wrapper

%typemap(in) std::shared_ptr<TYPE> %{
    std::shared_ptr<TYPE> *argp$argnum = *(std::shared_ptr<TYPE> **)&jarg$argnum;
    if (argp$argnum) {
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
        // 创建新的 shared_ptr，使用自定义删除器
        $1 = std::shared_ptr<TYPE>(argp$argnum->get(), [globalRef](TYPE* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });
    }
%}

%typemap(in) std::shared_ptr<TYPE>& %{
    std::shared_ptr<TYPE> temp$argnum;
    $1 = &temp$argnum;
    std::shared_ptr<TYPE> *argp$argnum = *(std::shared_ptr<TYPE> **)&jarg$argnum;
    if (argp$argnum) {
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
        // 创建新的 shared_ptr，使用自定义删除器
        *$1 = std::shared_ptr<TYPE>(argp$argnum->get(), [globalRef](TYPE* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });
    }
%}


%enddef  //shared_ptr_wrapper

//%define %director_shared_ptr_wrapper(TYPE)
//
//
//%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, TYPE);") std::shared_ptr<TYPE> %{
//    if (!$input) {
//        $1 = nullptr;
//    } else {
//        std::shared_ptr<TYPE> * jresult_smartPtr = *(std::shared_ptr<TYPE> **)&$input;
//        auto *jresult_ptr = dynamic_cast<SwigDirector_##$typemap(jstype, TYPE)*>(jresult_smartPtr->get());
//        jobject jobj = jresult_ptr->swig_get_self(jenv);
//        // 创建全局引用
//        jobject globalRef = jenv->NewGlobalRef(jobj);
//        todo
//        $1 = std::shared_ptr<TYPE>(jresult_smartPtr->get(), [globalRef](TYPE* ptr) {
//            JNIEnv *env = nullptr;
//            JNIContext context(env);
//            // 删除全局引用
//            env->DeleteGlobalRef(globalRef);
//        });
//    }
//%}
//
////%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, TYPE);") std::shared_ptr<TYPE> %{
////
////%}
//
//%enddef  //director_shared_ptr_wrapper


#endif // SHARED_PTR_SWIG_CONFIG