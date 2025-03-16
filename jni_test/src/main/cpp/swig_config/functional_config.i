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

// 确保这些方法在Java中是私有的
%javamethodmodifiers target_type::isEquals "private";
%javamethodmodifiers target_type::calculateHash "private";

%feature("nodirector") target_type::isEquals;
%feature("nodirector") target_type::calculateHash;

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

    static original_type obtainOriginal(JNIEnv *jenv, std::shared_ptr<target_type> *func_bridge, jobject j_func_bridge){
        using ReturnType = typename original_type::result_type;
        std::weak_ptr<target_type> weak_func_bridge = *func_bridge;
        original_type func = [weak_func_bridge, ref = JNIGlobalRef(jenv, j_func_bridge)]##param_type_and_name -> return_type {
            std::shared_ptr<target_type> func_bridge_ptr = weak_func_bridge.lock();
            if (func_bridge_ptr) {
                return func_bridge_ptr->onCall##param_name;
            } else if (std::is_same_v<ReturnType, void>) {
                return;
            } else {
                return ReturnType();
            }
        };
        return func;
    }

    static std::shared_ptr<original_type> obtainOriginal(std::shared_ptr<target_type> *func_bridge) {
        if (auto func_ptr = (*func_bridge)->m_func) {
            return func_ptr;
        }
        using ReturnType = typename original_type::result_type;
        std::weak_ptr<target_type> weak_func_bridge = *func_bridge;
        std::shared_ptr<original_type> func_ptr = std::make_shared<original_type>([weak_func_bridge]##param_type_and_name -> return_type {
            std::shared_ptr<target_type> func_bridge_ptr = weak_func_bridge.lock();
            if (func_bridge_ptr) {
                return func_bridge_ptr->onCall##param_name;
            } else if (std::is_same_v<ReturnType, void>) {
                return;
            } else {
                return ReturnType();
            }
        });

        (*func_bridge)->m_func = func_ptr;

        return func_ptr;
    }

private:
    std::shared_ptr<original_type> m_func;
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
                 std::shared_ptr<original_type>,
                 std::shared_ptr<const original_type> #target_type

%typemap(jtype) original_type,
                original_type&,
                original_type*,
                std::shared_ptr<original_type>,
                std::shared_ptr<const original_type> "long"

%typemap(javain) original_type,
                 original_type&,
                 original_type*,
                 std::shared_ptr<original_type>,
                 std::shared_ptr<const original_type> "$typemap(jstype, original_type).getCPtr($javainput)"

%typemap(javaout) original_type, original_type&, original_type*, std::shared_ptr<original_type>, std::shared_ptr<const original_type> {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new $typemap(jstype, original_type)(cPtr, true);
  }

%typemap(javadirectorin) original_type,
                         original_type&,
                         original_type*,
                         std::shared_ptr<original_type>,
                         std::shared_ptr<const original_type> "($jniinput == 0) ? null : new $typemap(jstype, original_type)($jniinput, true)"

%typemap(javadirectorout) original_type,
                          original_type&,
                          original_type*,
                          std::shared_ptr<original_type>,
                          std::shared_ptr<const original_type> "$typemap(jstype, original_type).getCPtr($javacall)"

%typemap(in) original_type %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<$typemap(jstype, original_type)> **)&jarg$argnum;
$1 = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
%}

%typemap(in) original_type& %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = &original$argnum;
%}

%typemap(in) original_type* %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = &original$argnum.get();
%}

%typemap(in) std::shared_ptr<original_type>, std::shared_ptr<const original_type> %{
std::shared_ptr<target_type> *smartarg$argnum = *(std::shared_ptr<target_type> **)&jarg$argnum;
auto original$argnum = target_type::obtainOriginal(smartarg$argnum);
$1 = original$argnum;
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") original_type, original_type& %{
target_type *function_bridge$argnum = new target_type##4DI($1);
*(std::shared_ptr<target_type> **) &$input = new std::shared_ptr<target_type>(function_bridge$argnum);
%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") std::shared_ptr<original_type>, std::shared_ptr<const original_type> %{
target_type *function_bridge$argnum = new SharedPtr##target_type##4DI($1);
*(std::shared_ptr<target_type> **) &$input = new std::shared_ptr<target_type>(function_bridge$argnum);
%}

%enddef //functional_bridge


#endif // FUNCTIONAL_CONFIG
