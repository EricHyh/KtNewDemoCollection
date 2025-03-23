#ifndef SHARED_PTR_SWIG_CONFIG
#define SHARED_PTR_SWIG_CONFIG


// 智能指针参数包装
%define %shared_ptr_wrapper(TYPE) //shared_ptr_wrapper

%shared_ptr(TYPE);

%typemap(in) std::shared_ptr<TYPE> %{
    std::shared_ptr<TYPE> *argp$argnum = *(std::shared_ptr<TYPE> **)&jarg$argnum;
    if (argp$argnum) {
        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(jarg$argnum_);
        // 创建新的 shared_ptr，使用自定义删除器 x
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

#endif // SHARED_PTR_SWIG_CONFIG