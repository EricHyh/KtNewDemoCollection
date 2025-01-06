#ifndef FUNCTIONAL_CONFIG
#define FUNCTIONAL_CONFIG

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Function 类型桥接
%define %functional_bridge(original_type, target_type, return_type, param_type_and_name, param_name)   //functional_bridge

%shared_ptr(target_type)
%feature("director") target_type;
%ignore target_type::original;
%ignore target_type::m_mutex;
%ignore target_type::obtainOriginal;

%inline %{
class target_type {

    public:
    virtual ~target_type() {}

    virtual
    return_type onCall##param_type_and_name = 0;

    static const std::shared_ptr<original_type> obtainOriginal(JNIEnv *jenv, std::shared_ptr<target_type> *function_bridge, jobject j_function_bridge){
        std::lock_guard<std::mutex> lock(function_bridge->get()->m_mutex);
        if (auto original_ptr = function_bridge->get()->original.lock()) {
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

        new_function_bridge->original = std::weak_ptr< original_type >(p_function);

        return p_function;
    }

    private:
    std::mutex m_mutex;

    std::weak_ptr <original_type> original;

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

class Local##target_type##_$argnum : public target_type {
    public:
    explicit Local##target_type##_$argnum(original_type function) : m_original(std::move(function)) {}

    return_type onCall##param_type_and_name override {
        if (m_original) {
            return m_original##param_name;
        } else {
            JNIEnv* env;
            JNIContext context(env);
            SWIG_JavaThrowException(env, SWIG_JavaNullPointerException, "Local##target_type##_$argnum m_original is null");
            return m_original##param_name;
        }
    }

    private:
    original_type m_original;
};

target_type *function_bridge$argnum = new Local##target_type##_$argnum($1);

*(std::shared_ptr<target_type> **) &$input = function_bridge$argnum ? new std::shared_ptr<target_type>(function_bridge$argnum) : 0;

%}

%typemap(directorin, descriptor="L$packagepath/$typemap(jstype, original_type);") std::shared_ptr<original_type> %{

class Local##target_type##_$argnum : public target_type {
        public:
        explicit Local##target_type##_$argnum(const std::shared_ptr<original_type>& function) : m_original(function) {}

        return_type onCall##param_type_and_name override {
            if (m_original) {
                return m_original->operator()##param_name;
            } else {
                JNIEnv* env;
                JNIContext context(env);
                SWIG_JavaThrowException(env, SWIG_JavaNullPointerException, "Local##target_type##_$argnum m_original is null");
                return m_original->operator()##param_name;
            }
        }

        private:
        std::shared_ptr<original_type> m_original;
};

target_type *function_bridge$argnum = new Local##target_type##_$argnum($1);

*(std::shared_ptr<target_type> **) &$input = function_bridge$argnum ? new std::shared_ptr<target_type>(function_bridge$argnum) : 0;

%}

%enddef //functional_bridge


#endif // FUNCTIONAL_CONFIG
