#ifndef FUNCTIONAL_CONFIG
#define FUNCTIONAL_CONFIG

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Function 类型桥接
%define %functional_bridge(original_type, target_type, return_type, param_type_and_name, param_name)   //functional_bridge

%shared_ptr(target_type)
%shared_ptr(target_type##4DI)
%shared_ptr(SharedPtr##target_type##4DI)
%feature("director") target_type;
%ignore target_type::m_weakOriginal;
%ignore target_type::m_mutex;
%ignore target_type::obtainOriginal;
%ignore target_type::ObtainOriginal;

// 确保这些方法在Java中是私有的
%javamethodmodifiers target_type::isEquals "private";
%javamethodmodifiers target_type::calculateHash "private";

// Java端的代码
%typemap(javacode) target_type %{
  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null || getClass() != obj.getClass()) return false;
    target_type other = (target_type) obj;
    return this.isEquals(other);
  }

  @Override
  public int hashCode() {
    return this.calculateHash();
  }
%}


%inline %{
class target_type {

public:
    target_type() = default;
    virtual ~target_type() = default;

    virtual return_type onCall##param_type_and_name = 0;

    virtual int calculateHash() {
        return static_cast<int>(std::hash<const target_type*>{}(this));
    }

    virtual bool isEquals(const target_type& other) {
        return this == &other;
    }

    static std::shared_ptr<original_type> obtainOriginal(JNIEnv *jenv, std::shared_ptr<target_type> *function_bridge, jobject j_function_bridge){
        std::lock_guard<std::mutex> lock(function_bridge->get()->m_mutex);
        if (auto original_ptr = function_bridge->get()->m_weakOriginal.lock()) {
            // 如果原始回调函数还存在，直接返回
            return original_ptr;
        }

        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(j_function_bridge);
        // 创建新的 shared_ptr，使用自定义删除器
        std::shared_ptr<target_type> new_function_bridge = std::shared_ptr<target_type>(function_bridge->get(), [globalRef](target_type* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });

        std::shared_ptr<original_type> p_function = std::make_shared<original_type>([new_function_bridge]##param_type_and_name -> return_type {
            return new_function_bridge->onCall##param_name;
        });

        new_function_bridge->m_weakOriginal = std::weak_ptr< original_type >(p_function);

        return p_function;
    }

    std::shared_ptr<original_type> ObtainOriginal(JNIEnv *jenv, jobject j_function_bridge){
        std::lock_guard<std::mutex> lock(this->m_mutex);
        if (auto original_ptr = this->m_weakOriginal.lock()) {
            // 如果原始回调函数还存在，直接返回
            return original_ptr;
        }

        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(j_function_bridge);
        // 创建新的 shared_ptr，使用自定义删除器
        std::shared_ptr<target_type> new_function_bridge = std::shared_ptr<target_type>(this, [globalRef](target_type* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });

        std::shared_ptr<original_type> p_function = std::make_shared<original_type>([new_function_bridge]##param_type_and_name -> return_type {
            return new_function_bridge->onCall##param_name;
        });

        new_function_bridge->m_weakOriginal = std::weak_ptr<original_type>(p_function);

        return p_function;
    }

private:
    std::mutex m_mutex;

    std::weak_ptr<original_type> m_weakOriginal;

};

%}


%{

class target_type##4DI : public target_type {

public:
    explicit target_type##4DI(original_type function) : m_original(std::move(function)) {}

    return_type onCall##param_type_and_name override {
        if (m_original) {
            return m_original##param_name;
        } else {
            JNIEnv* env;
            JNIContext context(env);
            SWIG_JavaThrowException(env, SWIG_JavaNullPointerException, "target_type##4DI m_original is null");
            return m_original##param_name;
        }
    }

private:
    original_type m_original;
};

class SharedPtr##target_type##4DI : public target_type {

public:
    explicit SharedPtr##target_type##4DI(const std::shared_ptr<original_type>& function) : m_original(function) {}

    return_type onCall##param_type_and_name override {
        if (m_original) {
            return m_original->operator()##param_name;
        } else {
            JNIEnv* env;
            JNIContext context(env);
            SWIG_JavaThrowException(env, SWIG_JavaNullPointerException, "SharedPtr##target_type##4DI m_original is null");
            return m_original->operator()##param_name;
        }
    }

    int calculateHash() override {
        return static_cast<int>(std::hash<const original_type*>{}(this->m_original.get()));
    }

    bool isEquals(const target_type& other) override {
        if (this == &other) {
            return true;
        }
        const auto* other_ptr = dynamic_cast<const SharedPtr##target_type##4DI*>(&other);
        if(other_ptr == nullptr) {
            return false;
        }
        return this->m_original.get() == other_ptr->m_original.get();
    }

private:
    std::shared_ptr<original_type> m_original;
};

%}

%typemap(jstype) original_type,
                 original_type&,
                 original_type*,
                 std::shared_ptr<original_type> #target_type

%typemap(jtype) original_type,
                original_type&,
                original_type*,
                std::shared_ptr<original_type> "long"

%typemap(javain) original_type,
                 original_type&,
                 original_type*,
                 std::shared_ptr<original_type> "$typemap(jstype, original_type).getCPtr($javainput)"

%typemap(javaout) original_type, original_type&, original_type*, std::shared_ptr<original_type> {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, original_type)(cPtr, true);
  }

%typemap(javadirectorin) original_type,
                         original_type&,
                         original_type*,
                         std::shared_ptr<original_type> "($jniinput == 0) ? null : new $typemap(jstype, original_type)($jniinput, true)"

%typemap(javadirectorout) original_type,
                          original_type&,
                          original_type*,
                          std::shared_ptr<original_type> "$typemap(jstype, original_type).getCPtr($javacall)"

%typemap(in) original_type %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<$typemap(jstype, original_type)> **)&jarg$argnum;
$1 = *target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
%}

%typemap(in) original_type& %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = original$argnum.get();
%}

%typemap(in) original_type* %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = original$argnum.get();
%}

%typemap(in) std::shared_ptr<original_type> %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = original$argnum;
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") original_type, original_type& %{
target_type *function_bridge$argnum = new target_type##4DI($1);
*(std::shared_ptr<target_type> **) &$input = new std::shared_ptr<target_type>(function_bridge$argnum);
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") std::shared_ptr<original_type> %{
target_type *function_bridge$argnum = new SharedPtr##target_type##4DI($1);
*(std::shared_ptr<target_type> **) &$input = new std::shared_ptr<target_type>(function_bridge$argnum);

%}

%enddef //functional_bridge


#endif // FUNCTIONAL_CONFIG
