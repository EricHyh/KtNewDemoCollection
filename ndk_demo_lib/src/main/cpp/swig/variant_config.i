#ifndef VARIANT_CONFIG
#define VARIANT_CONFIG

%import "normal_type_config.i"

%define %target_type_class_2(original_type, target_type, t1, t2)
%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    target_type(const t1& value){
        this->m_original = value;
    }

    target_type(const t2& value){
        this->m_original = value;
    }

    original_type m_original;
};

%}

%enddef

%define %target_type_class_3(original_type, target_type, t1, t2, t3)
%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    target_type(const t1& value){
        this->m_original = value;
    }

    target_type(const t2& value){
        this->m_original = value;
    }

    target_type(const t3& value){
        this->m_original = value;
    }

    original_type m_original;
};

%}

%enddef

%define %target_type_class_4(original_type, target_type, t1, t2, t3, t4)
%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    target_type(const t1& value){
        this->m_original = value;
    }

    target_type(const t2& value){
        this->m_original = value;
    }

    target_type(const t3& value){
        this->m_original = value;
    }

    target_type(const t4& value){
        this->m_original = value;
    }

    original_type m_original;
};

%}

%enddef

%define %target_type_class_5(original_type, target_type, t1, t2, t3, t4, t5)
%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    target_type(const t1& value){
        this->m_original = value;
    }

    target_type(const t2& value){
        this->m_original = value;
    }

    target_type(const t3& value){
        this->m_original = value;
    }

    target_type(const t4& value){
        this->m_original = value;
    }

    target_type(const t5& value){
        this->m_original = value;
    }

    original_type m_original;
};

%}

%enddef

%define %target_type_class_6(original_type, target_type, t1, t2, t3, t4, t5, t6)
%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    target_type(const t1& value){
        this->m_original = value;
    }

    target_type(const t2& value){
        this->m_original = value;
    }

    target_type(const t3& value){
        this->m_original = value;
    }

    target_type(const t4& value){
        this->m_original = value;
    }

    target_type(const t5& value){
        this->m_original = value;
    }

    target_type(const t6& value){
        this->m_original = value;
    }

    original_type m_original;
};

%}

%enddef

//------------------------------------------------------------------

%define %variant_bridge_2(original_type, target_type, t1, t2)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%target_type_class_2(original_type, target_type, t1, t2)

%shared_type_bridge(original_type, target_type, target_type)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_3(original_type, target_type, t1, t2, t3)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%target_type_class_3(original_type, target_type, t1, t2, t3)

%shared_type_bridge(original_type, target_type, target_type)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_4(original_type, target_type, t1, t2, t3, t4)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%target_type_class_4(original_type, target_type, t1, t2, t3, t4)

%shared_type_bridge(original_type, target_type, target_type)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_5(original_type, target_type, t1, t2, t3, t4, t5)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%target_type_class_5(original_type, target_type, t1, t2, t3, t4, t5)

%shared_type_bridge(original_type, target_type, target_type)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_6(original_type, target_type, t1, t2, t3, t4, t5, t6)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%target_type_class_6(original_type, target_type, t1, t2, t3, t4, t5, t6)

%shared_type_bridge(original_type, target_type, target_type)

%enddef

//------------------------------------------------------------------


#endif // VARIANT_CONFIG