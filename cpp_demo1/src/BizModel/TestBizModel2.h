#pragma once

#include <memory>
#include <variant>
#include <type_traits>
#include <iostream>
#include <optional>

// class IModify {
// public:
//     IModify() = default;
//
//     virtual ~IModify() = default;
// };
//
// class XXXModify : public IModify {
// public:
//     XXXModify() = default;
//
//     ~XXXModify() override = default;
// };
//
// class XXXModify1 : public XXXModify {
// public:
//     XXXModify1(): XXXModify() {
//     }
//
//     ~XXXModify1() override = default;
// };
//
// class XXXModify2 : public XXXModify {
// public:
//     XXXModify2(): XXXModify() {
//     }
//
//     ~XXXModify2() override = default;
// };
//
// class XXXModify3 : public XXXModify {
// public:
//     XXXModify3(): XXXModify() {
//     }
//
//     ~XXXModify3() override = default;
// };
//
// class XXXModify4 : public XXXModify {
// public:
//     XXXModify4(): XXXModify() {
//     }
//
//     ~XXXModify4() override = default;
// };
//
//
// template<typename T, typename Modify, typename... Ts>
// struct is_valid_type {
//     static constexpr bool value = std::is_base_of_v<Modify, T> && (std::is_same_v<T, Ts> || ...);
// };
//
// template<class Modify, class... Ts>
// class CFieldBizModel {
//     static_assert(std::is_base_of_v<IModify, Modify>, "Modify must derive from IModify");
//     static_assert((std::is_base_of_v<Modify, Ts> && ...), "All Ts must be exactly Modify");
//
// public:
//     virtual ~CFieldBizModel() = default;
//
//     void Apply(const std::shared_ptr<IModify> &modify) {
//         auto var = make_variant_from_base(modify);
//         if (!var.has_value()) {
//             throw std::logic_error("Modify must not be applied");
//         }
//         std::visit([this](auto &&arg) { this->TypedApply(arg); }, var.value());
//     }
//
// protected:
//     virtual void TypedApply(const std::variant<Ts...> &variant) = 0;
//
// private:
//     static auto make_variant_from_base(const std::shared_ptr<IModify> &base) {
//         using T1 = std::decay_t<decltype(*base)>;
//         auto& id = typeid(*base);
//         std::cout << "Actual type1: " << typeid(*base).name() << std::endl;
//
//         XXXModify4 modify4;
//         IModify& modify4_ref = modify4;
//         std::cout << "Actual type2: " << typeid(modify4_ref).name() << std::endl;
//
//         using T2 = Modify;
//         if (typeid(modify4_ref) == typeid(XXXModify4)) {
//             std::cout << "T1" << std::endl;
//         } else {
//             std::cout << "T2" << std::endl;
//         }
//         if (std::is_same_v<T2, XXXModify>) {
//             std::cout << "T11" << std::endl;
//         } else {
//             std::cout << "T22" << std::endl;
//         }
//         std::optional<std::variant<Ts...> > var;
//         ((void) [&] {
//             if (auto p = std::dynamic_pointer_cast<Ts>(base)) {
//                 var = *p;
//                 return true;
//             }
//             return false;
//         }(), ...);
//         return var;
//     }
// };
//
// class TestFieldBizModel final : public CFieldBizModel<XXXModify, XXXModify1, XXXModify2, XXXModify3> {
// protected:
//     void TypedApply(const std::variant<XXXModify1, XXXModify2, XXXModify3> &variant) override {
//         std::visit([this]([[maybe_unused]] auto &&arg) {
//             using T = std::decay_t<decltype(arg)>;
//             if constexpr (std::is_same_v<T, XXXModify1>) {
//                 std::cout << "XXXModify1" << std::endl;
//             } else if constexpr (std::is_same_v<T, XXXModify2>) {
//                 std::cout << "XXXModify2" << std::endl;
//             } else if constexpr (std::is_same_v<T, XXXModify3>) {
//                 std::cout << "XXXModify3" << std::endl;
//             }
//         }, variant);
//     }
// };
