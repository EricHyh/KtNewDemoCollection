//
// Created by eriche on 2025/5/24.
//

#pragma once


#include "field/FieldDataModel.h"
#include "field/FieldKeys.h"
#include <variant>

class IModify {

public:
    virtual ~IModify() = default;

};


class IFieldBizModel {
public:
    virtual bool IsMatched(std::shared_ptr<IModify> modify) = 0;

    virtual void Apply(std::shared_ptr<IModify> modify) = 0;
};

template<class Value>
class CMutableField {
public:
    CMutableField() = delete;

    CMutableField(IFieldBizModel* model, FiledKey<Value> key);

    bool SetValue(Value value) {

    }

private:
    FieldDataModel m_dataModel;
    FiledKey<Value> m_key;
};




class XXXModify : IModify {

};

class XXXModify1 : XXXModify {

};

class XXXModify2 : XXXModify {

};

class XXXModify3 : XXXModify {

};





template<class Modify, class ...Ts>
class CFieldBizModel : public IFieldBizModel {

    static_assert(std::is_base_of_v<IModify, Modify>, "Modify must derive from IModify");
    static_assert((std::is_base_of_v<Modify, Ts> && ...), "All Ts must be exactly Modify");

public:
    bool IsMatched(std::shared_ptr<IModify> modify) override {
        return (std::dynamic_pointer_cast<Ts>(modify) || ...);
    }

//    bool IsMatched(const IModify& modify) override {
//        return ((typeid(modify) == typeid(Ts)) || ...);
//    }

    void Apply(std::shared_ptr<IModify> modify) override {
        std::variant<Ts...> variant = *modify;
        _Apply(variant);
    }

protected:
    virtual void _Apply(std::variant<Ts...> modify) = 0;

    template<class Value>
    CMutableField<Value> Field(FiledKey<Value> key);


//public:
//    virtual bool IsMatched(std::shared_ptr<Modify> modify) = 0;
//
////    virtual void Apply(std::shared_ptr<Modify> modify) = 0;
//
//    virtual void Apply(std::variant<Ts...> modify) = 0;
//
//protected:
//    template<class Value>
//    CMutableField<Value> Field(FiledKey<Value> key);
};






// 1. 定义统一类型别名：基类 + 派生类元组
template<typename Base, typename... Derives>
using ModifyFamily = std::tuple<Base, std::tuple<Derives...>>;


using XXXModifyFamily = ModifyFamily<XXXModify, XXXModify1, XXXModify2, XXXModify3>;

// 2. 辅助模板：解包元组结构
template<typename FamilyTuple>
struct CFieldBizModelAdapter;

template<typename Base, typename... Derives>
struct CFieldBizModelAdapter<std::tuple<Base, std::tuple<Derives...>>> {
    using type = CFieldBizModel<Base, Derives...>;  // 展开派生类参数包
};

// 3. 使用简化别名定义业务模型
class XXXFieldBizModel : public CFieldBizModelAdapter<XXXModifyFamily>::type  // ✅ 单别名调用
{

//    bool IsMatched(std::shared_ptr<XXXModify> modify) override {
//
//    }
//
//    // 自动推导参数类型
//    void Apply(std::variant<XXXModify1, XXXModify2, XXXModify3> modify) override {
//        // 实现逻辑...
//    }
public:
    XXXFieldBizModel() : name(CMutableField<std::string>(this, FieldKeys::name)) {
    }

private:
    CMutableField<std::string> name;

};


//template<class Modify, typename = std::enable_if_t<std::is_base_of_v<IModify, Modify>>, class ...Ts>
//class Modifies : std::variant<Ts...> {
//};

//template<class Modify, typename = std::enable_if_t<std::is_base_of_v<IModify, Modify>>,
//        typename = std::enable_if_t<std::conjunction_v<std::is_same<Modify, Ts>...>>>
//class Modifies : public std::variant<Ts...> {};

//template<class Modify, class... Ts,
//        typename CheckBase = std::enable_if_t<std::is_base_of_v<IModify, Modify>>,
//        typename CheckTs = std::enable_if_t<(std::is_same_v<Modify, Ts> && ...)>>
//class Modifies : public std::variant<Ts...> {};



template<class Modify, class... Ts>
class IModifies : public std::variant<Ts...> {
    static_assert(std::is_base_of_v<IModify, Modify>, "Modify must derive from IModify");
    static_assert((std::is_base_of_v<Modify, Ts> && ...), "All Ts must be exactly Modify");
};

struct XXXModifies : IModifies<XXXModify, XXXModify1, XXXModify2> {
};

//template<class Modify>
//class CFieldBizModel {
//
//public:
//    virtual bool IsMatched(std::shared_ptr<Modify> modify) = 0;
//
////    virtual void Apply(std::shared_ptr<Modify> modify) = 0;
//
////    virtual void Apply(Modifies modify) = 0;
//
//protected:
//    template<class Value>
//    CMutableField<Value> Field(FiledKey<Value> key);
//
//};

//class XXXFieldBizModel : CFieldBizModel<XXXModify> {
//
//
//public:
//    bool IsMatched(std::shared_ptr<XXXModify> modify) override {
//        return false;
//    }
//
//    void Apply(std::shared_ptr<XXXModify> modify) override {
//
//    }
//
//private:
//    CMutableField<std::string> xx;
//
//};