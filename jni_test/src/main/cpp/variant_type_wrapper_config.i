#ifndef VARIANT_CONFIG
#define VARIANT_CONFIG

%define type_expand(target_type, c_t, nice_t)
    target_type(const c_t& value){
        this->m_original = value;
    }

    bool Is##nice_t(){
        return std::holds_alternative<c_t>(m_original);
    }

    c_t Get##nice_t(){
        return std::get<c_t>(m_original);
    }
    %enddef

%define %target_type_class_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_with_empty_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = default;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_with_empty_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = default;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_with_empty_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = default;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    type_expand(target_type, c_t5, nice_t5)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_with_empty_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = default;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    type_expand(target_type, c_t5, nice_t5)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_6(original_type, target_type,
        c_t1, nice_t1,
        c_t2, nice_t2,
        c_t3, nice_t3,
        c_t4, nice_t4,
        c_t5, nice_t5,
        c_t6, nice_t6)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = delete;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    type_expand(target_type, c_t5, nice_t5)

    type_expand(target_type, c_t6, nice_t6)

    original_type m_original;
};

%}

%enddef

%define %target_type_class_with_empty_6(original_type, target_type,
        c_t1, nice_t1,
        c_t2, nice_t2,
        c_t3, nice_t3,
        c_t4, nice_t4,
        c_t5, nice_t5,
        c_t6, nice_t6)

%ignore target_type::m_original;
%ignore target_type::target_type(const original_type& value);

%inline %{
class target_type {

public:
    target_type() = default;

    target_type(const original_type& value) : m_original(value) {}

    type_expand(target_type, c_t1, nice_t1)

    type_expand(target_type, c_t2, nice_t2)

    type_expand(target_type, c_t3, nice_t3)

    type_expand(target_type, c_t4, nice_t4)

    type_expand(target_type, c_t5, nice_t5)

    type_expand(target_type, c_t6, nice_t6)

    original_type m_original;
};

%}

%enddef

//------------------------------------------------------------------

%define %variant_bridge_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%target_type_class_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%enddef

%define %variant_with_empty_bridge_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%target_type_class_with_empty_2(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%target_type_class_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%enddef

%define %variant_with_empty_bridge_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%target_type_class_with_empty_3(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3)

%enddef

//------------------------------------------------------------------
%define %variant_bridge_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%target_type_class_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%enddef

%define %variant_with_empty_bridge_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%target_type_class_with_empty_4(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%target_type_class_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%enddef

%define %variant_with_empty_bridge_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%target_type_class_with_empty_5(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5)

%enddef

//------------------------------------------------------------------

%define %variant_bridge_6(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5, c_t6, nice_t6)

%target_type_class_6(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5, c_t6, nice_t6)

%enddef

%define %variant_with_empty_bridge_6(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5, c_t6, nice_t6)

%target_type_class_with_empty_6(original_type, target_type, c_t1, nice_t1, c_t2, nice_t2, c_t3, nice_t3, c_t4, nice_t4, c_t5, nice_t5, c_t6, nice_t6)

%enddef

//------------------------------------------------------------------


#endif // VARIANT_CONFIG