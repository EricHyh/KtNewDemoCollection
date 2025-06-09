#pragma once

#include <memory>
#include <variant>
#include <type_traits>
#include <iostream>
#include <optional>
#include <sstream>

class IModify {
public:
    IModify() = default;

    virtual ~IModify() = default;
};

class XXXModify : public IModify {
public:
    XXXModify() = default;

    ~XXXModify() override = default;
};

class XXXModify1 : public XXXModify {
public:
    XXXModify1(): XXXModify() {
    }

    ~XXXModify1() override = default;
};

class XXXModify2 : public XXXModify {
public:
    XXXModify2(): XXXModify() {
    }

    ~XXXModify2() override = default;
};

class XXXModify3 : public XXXModify {
public:
    XXXModify3(): XXXModify() {
    }

    ~XXXModify3() override = default;
};

class XXXModify4 : public XXXModify {
public:
    XXXModify4(): XXXModify() {
    }

    ~XXXModify4() override = default;
};


template<typename T, typename Modify, typename... Ts>
struct is_valid_type {
    static constexpr bool value = std::is_base_of_v<Modify, T> && (std::is_same_v<T, Ts> || ...);
};

template<class Modify, class... Ts>
class CFieldBizModel {
    static_assert(std::is_base_of_v<IModify, Modify>, "Modify must derive from IModify");
    static_assert((std::is_base_of_v<Modify, Ts> && ...), "All Ts must be exactly Modify");

public:
    virtual ~CFieldBizModel() = default;

    void Apply(const IModify& modify) {
        auto var = MakeVariantFromBase(modify);
        if (!var.has_value()) {
            std::ostringstream oss;
            oss << "Modify[" << typeid(modify).name() << "], must not be applied";
            // 抛出异常
            throw std::logic_error(oss.str());
        }
        std::visit([this](auto&& arg) { this->TypedApply(arg); }, var.value());
    }

protected:
    virtual void TypedApply(const std::variant<Ts...>& variant) = 0;

private:
    static auto MakeVariantFromBase(const IModify& base) {
        std::optional<std::variant<Ts...> > var;
        ([&] {
            if (typeid(base) == typeid(Ts)) {
                var = dynamic_cast<const Ts&>(base);
                return true; // 匹配成功返回true触发短路
            }
            return false;
        }() || ...);
        return var;
    }
};

class TestFieldBizModel final : public CFieldBizModel<XXXModify, XXXModify1, XXXModify2, XXXModify3> {
protected:
    void TypedApply(const std::variant<XXXModify1, XXXModify2, XXXModify3>& variant) override {
        std::visit([this]([[maybe_unused]] auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, XXXModify1>) {
                std::cout << "XXXModify1" << std::endl;
            } else if constexpr (std::is_same_v<T, XXXModify2>) {
                std::cout << "XXXModify2" << std::endl;
            } else if constexpr (std::is_same_v<T, XXXModify3>) {
                std::cout << "XXXModify3" << std::endl;
            }
        }, variant);
    }
};
