#ifndef FUNCTIONAL_CONFIG
#define FUNCTIONAL_CONFIG

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// Function 类型桥接
%define %inner_template_function_type_bridge(FUNCTION_TYPE, TEMPLATE_FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME, PACKAGE)   //inner_template_function_type_bridge

%shared_ptr(TEMPLATE_FUNCTION_TYPE##Bridge)
%feature("director") TEMPLATE_FUNCTION_TYPE##Bridge;
%ignore TEMPLATE_FUNCTION_TYPE##Bridge::original;
%ignore TEMPLATE_FUNCTION_TYPE##Bridge::m_mutex;
%ignore TEMPLATE_FUNCTION_TYPE##Bridge::obtainOriginal;

%inline %{
class TEMPLATE_FUNCTION_TYPE##Bridge {

    public:
    virtual ~TEMPLATE_FUNCTION_TYPE##Bridge() {}

    virtual
    void onCall##CALL_PARAM_TYPE_AND_NAME = 0;

    static const FUNCTION_TYPE obtainOriginal(JNIEnv *jenv, std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> *function_bridge, jobject j_function_bridge){
        std::lock_guard<std::mutex> lock(function_bridge->get()->m_mutex);
        if (auto original_ptr = function_bridge->get()->original.lock()) {
            // 如果原始回调函数还存在，直接返回
            return *original_ptr;
        }

        // 创建全局引用
        jobject globalRef = jenv->NewGlobalRef(j_function_bridge);
        // 创建新的 shared_ptr，使用自定义删除器
        std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> new_function_bridge = std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge>(function_bridge->get(), [globalRef](TEMPLATE_FUNCTION_TYPE##Bridge* ptr) {
            JNIEnv *env = nullptr;
            JNIContext context(env);
            // 删除全局引用
            env->DeleteGlobalRef(globalRef);
        });

        std::shared_ptr<FUNCTION_TYPE> p_function = std::make_shared<FUNCTION_TYPE>([new_function_bridge]##CALL_PARAM_TYPE_AND_NAME {
            new_function_bridge->onCall##CALL_PARAM_NAME;
        });

        new_function_bridge->original = std::weak_ptr< FUNCTION_TYPE >(p_function);

        return *p_function;
    }

    private:
    std::mutex m_mutex;

    std::weak_ptr <FUNCTION_TYPE> original;

};
%}

%typemap(jstype) FUNCTION_TYPE, FUNCTION_TYPE& #TEMPLATE_FUNCTION_TYPE"Bridge"
%typemap(jtype) FUNCTION_TYPE, FUNCTION_TYPE& "long"
%typemap(javain) FUNCTION_TYPE, FUNCTION_TYPE& #TEMPLATE_FUNCTION_TYPE"Bridge.getCPtr($javainput)"


%typemap(in) FUNCTION_TYPE %{
std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> *smartarg$argnum = *(std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> **)&jarg$argnum;
$1 = TEMPLATE_FUNCTION_TYPE##Bridge::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
%}

%typemap(in) FUNCTION_TYPE& %{
std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> *smartarg$argnum = *(std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> **)&jarg$argnum;
auto original$argnum = TEMPLATE_FUNCTION_TYPE##Bridge::obtainOriginal(jenv, smartarg$argnum, jarg$argnum_);
$1 = &original$argnum;
%}

%typemap(directorin, descriptor="L"#PACKAGE"/"#TEMPLATE_FUNCTION_TYPE"Bridge;") FUNCTION_TYPE, FUNCTION_TYPE& %{

class Local##TEMPLATE_FUNCTION_TYPE##Bridge_$argnum : public TEMPLATE_FUNCTION_TYPE##Bridge {
    public:
    explicit Local##TEMPLATE_FUNCTION_TYPE##Bridge_$argnum(FUNCTION_TYPE function) : m_original(std::move(function)) {}

    void onCall##CALL_PARAM_TYPE_AND_NAME override {
            if (m_original) {
                m_original##CALL_PARAM_NAME;
            }
    }

    private:
    FUNCTION_TYPE m_original;
};

TEMPLATE_FUNCTION_TYPE##Bridge *function_bridge$argnum = new Local##TEMPLATE_FUNCTION_TYPE##Bridge_$argnum($1);

*(std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge> **) &$input = function_bridge$argnum ? new std::shared_ptr<TEMPLATE_FUNCTION_TYPE##Bridge>(function_bridge$argnum) : 0;

%}

%typemap(javadirectorin) FUNCTION_TYPE, FUNCTION_TYPE& %{($jniinput == 0) ? null : new TEMPLATE_FUNCTION_TYPE##Bridge($jniinput, true)%}

%enddef //inner_template_function_type_bridge

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

%define %template_function_type_bridge(FUNCTION_TYPE, TEMPLATE_FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME, PACKAGE)   //template_function_type_bridge
%inner_template_function_type_bridge(FUNCTION_TYPE, TEMPLATE_FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME, PACKAGE)
%enddef //template_function_type_bridge

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

%define %function_type_bridge(FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME, PACKAGE)   //function_type_bridge
%inner_template_function_type_bridge(FUNCTION_TYPE, FUNCTION_TYPE, CALL_PARAM_TYPE_AND_NAME, CALL_PARAM_NAME, PACKAGE)
%enddef //function_type_bridge

#endif // FUNCTIONAL_CONFIG
