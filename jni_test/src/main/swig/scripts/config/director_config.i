#ifndef DIRECTOR_CONFIG
#define DIRECTOR_CONFIG

%import "shared_ptr_config.i"

%define %director_shared_ptr_wrapper(TYPE)

%shared_ptr(TYPE);
%feature("director") TYPE;
%shared_ptr_wrapper(TYPE);

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::shared_ptr<TYPE> {
    long ptr = $jnicall;
    if (ptr == 0) {
      return null;
    } else {
      com.hyh.jnitest.basic.infrastructure.SwigDirectorWrapper wrapper = new com.hyh.jnitest.basic.infrastructure.SwigDirectorWrapper(ptr, true);
      return wrapper.acquire(cPtr -> new $typemap(jstype, TYPE)(cPtr, true));
    }
  }

%typemap(out) std::shared_ptr<TYPE> %{
if ($1) {
  auto *$1_ptr = dynamic_cast<Swig::Director*>($1.get());
  if ($1_ptr) {
    jobject $1_jobj = $1_ptr->swig_get_self(jenv);
    if ($1_jobj) {
      *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper(jenv, $1_jobj);
    } else {
      *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
    }
  } else {
    *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
  }
}
%}

%typemap(javadirectorin) std::shared_ptr<TYPE> "($jniinput == 0) ? null : new com.hyh.jnitest.basic.infrastructure.SwigDirectorWrapper($jniinput, true).acquire(cPtr -> new $typemap(jstype, TYPE)(cPtr, true))"

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, TYPE);") std::shared_ptr<TYPE> %{
$input = 0;
if ($1) {
  auto *$1_ptr = dynamic_cast<Swig::Director*>($1.get());
  if ($1_ptr) {
    jobject $1_jobj = $1_ptr->swig_get_self(jenv);
    if ($1_jobj) {
      *((SwigDirectorWrapper **)&$input) = new SwigDirectorWrapper(jenv, $1_jobj);
    } else {
      *((SwigDirectorWrapper **)&$input) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
    }
  } else {
    *((SwigDirectorWrapper **)&$input) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
  }
}
%}

%typemap(directorout, descriptor="L$packagepath/$typemap(jstype, TYPE);") std::shared_ptr<TYPE> %{
    if ($input) {
        std::shared_ptr<TYPE> *smartarg = *(std::shared_ptr<TYPE> **)&$input;
        auto *jresult_ptr = dynamic_cast<Swig::Director*>(smartarg->get());
        if (jresult_ptr) {
            jobject jobj = jresult_ptr->swig_get_self(jenv);
            // 创建全局引用
            jobject globalRef = jenv->NewGlobalRef(jobj);
            $1 = std::shared_ptr<TYPE>(smartarg->get(), [globalRef](TYPE* ptr) {
                JNIEnv *env = nullptr;
                JNIContext context(env);
                // 删除全局引用
                env->DeleteGlobalRef(globalRef);
            });
        } else {
            $1 = *smartarg;
        }
    }
%}

%enddef

#endif // DIRECTOR_CONFIG