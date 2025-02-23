#ifndef DIRECTOR_CONFIG
#define DIRECTOR_CONFIG

%define %swig_director_wrapper()

%ignore SwigDirectorWrapper::SwigDirectorWrapper(JNIEnv *, jobject);
%ignore SwigDirectorWrapper::SwigDirectorWrapper(void *);
%ignore SwigDirectorWrapper::SwigDirectorWrapper(const SwigDirectorWrapper &);
%ignore SwigDirectorWrapper::operator=(const SwigDirectorWrapper &);
%ignore SwigDirectorWrapper::SwigSwigDirectorWrapper(SwigDirectorWrapper &&);
%ignore SwigDirectorWrapper::operator=(SwigDirectorWrapper &&);


%typemap(javacode) SwigDirectorWrapper %{

  @SuppressWarnings("all")
  public <T> T acquire(IDirectorConstructor<T> constructor){
    if (isJObject()) {
      return (T) getJObject();
    } else {
      long cPtr = getCPtr();
      return (cPtr == 0) ? null : constructor.create(cPtr);
    }
  }

  interface IDirectorConstructor<T> {
    T create(long cPtr);
  }
%}

%inline %{

class SwigDirectorWrapper {
public:
    explicit SwigDirectorWrapper(JNIEnv *env, jobject obj)
            : m_data(std::make_unique<JNIGlobalRef>(env, obj)) {}

    explicit SwigDirectorWrapper(void *ptr) : m_data(ptr) {}

    ~SwigDirectorWrapper() = default;

    SwigDirectorWrapper(const SwigDirectorWrapper &) = delete;

    SwigDirectorWrapper &operator=(const SwigDirectorWrapper &) = delete;

    SwigDirectorWrapper(SwigDirectorWrapper &&) = default;

    SwigDirectorWrapper &operator=(SwigDirectorWrapper &&) = default;

    bool isJObject() const noexcept {
        return std::holds_alternative<std::unique_ptr<JNIGlobalRef>>(m_data);
    }

    bool isCPtr() const noexcept {
        return std::holds_alternative<void *>(m_data);
    }

    jobject getJObject() const noexcept {
        if (auto jref = std::get_if<std::unique_ptr<JNIGlobalRef>>(&m_data)) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            return env->NewLocalRef((*jref)->get());
        }
        return nullptr;
    }

    uintptr_t getCPtr() const noexcept {
        if (auto ptr = std::get_if<void *>(&m_data)) {
            return reinterpret_cast<uintptr_t>(*ptr);
        }
        return 0;
    }

private:
    std::variant<std::unique_ptr<JNIGlobalRef>, void *> m_data;
};

%}


%enddef

%define %director_shared_ptr_wrapper(TYPE)

//Java层，Java调用JNI函数时，对返回值的转换
%typemap(javaout) std::shared_ptr<TYPE> {
    long ptr = $jnicall;
    if (ptr == 0) {
      return null;
    } else {
      SwigDirectorWrapper wrapper = new SwigDirectorWrapper(ptr, true);
      return wrapper.acquire((SwigDirectorWrapper.IDirectorConstructor<$typemap(jstype, TYPE)>) cPtr -> new $typemap(jstype, TYPE)(cPtr, true));
    }
  }

%typemap(out) std::shared_ptr<TYPE> %{
if ($1) {
  auto *$1_ptr = dynamic_cast<SwigDirector_##$typemap(jstype, TYPE)*>($1.get());
  if ($1_ptr) {
    jobject $1_jobj = $1_ptr->swig_get_self(jenv);
    if ($1_jobj) {
      *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper($1_jobj);
    } else {
      *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
    }
  } else {
    *((SwigDirectorWrapper **)&$result) = new SwigDirectorWrapper(new std::shared_ptr<TYPE>($1));
  }
}
%}

%typemap(javadirectorin) std::shared_ptr<TYPE> "($jniinput == 0) ? null : new SwigDirectorWrapper($jniinput, true).acquire((SwigDirectorWrapper.IDirectorConstructor<$typemap(jstype, TYPE)>) cPtr -> new $typemap(jstype, TYPE)(cPtr, true)))"

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, TYPE);") std::shared_ptr<TYPE> %{
$input = 0;
if ($1) {
  auto *$1_ptr = dynamic_cast<SwigDirector_##$typemap(jstype, TYPE)*>($1.get());
  if ($1_ptr) {
    jobject $1_jobj = $1_ptr->swig_get_self(jenv);
    if ($1_jobj) {
      *((SwigDirectorWrapper **)&$input) = new SwigDirectorWrapper($1_jobj);
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
        auto *jresult_ptr = dynamic_cast<SwigDirector_##$typemap(jstype, TYPE)*>(smartarg->get());
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