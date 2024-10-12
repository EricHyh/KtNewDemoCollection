//
// Created by eriche on 2024/10/12.
//

#ifndef KTDEMOCOLLECTION_BASETEST_H
#define KTDEMOCOLLECTION_BASETEST_H



#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <android/log.h>

class Base {
public:
    virtual ~Base() = default;
    virtual std::string getName() const = 0;

    static void registerSubclass(const std::string& name, std::unique_ptr<Base> (*creator)()) {
        getRegistry()[name] = creator;
    }

    static std::vector<std::string> getSubclassNames() {
        std::vector<std::string> names;
        for (const auto& pair : getRegistry()) {
            names.push_back(pair.first);
        }
        return names;
    }

    static std::unique_ptr<Base> create(const std::string& name) {
        auto it = getRegistry().find(name);
        if (it != getRegistry().end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    static std::map<std::string, std::unique_ptr<Base> (*)()>& getRegistry() {
        static std::map<std::string, std::unique_ptr<Base> (*)()> registry;
        return registry;
    }
};

#define REGISTER_SUBCLASS(Base, Subclass) \
    namespace { \
        struct Subclass##Registrar { \
            Subclass##Registrar() { \
                Base::registerSubclass(#Subclass, []() -> std::unique_ptr<Base> { \
                    return std::make_unique<Subclass>(); \
                }); \
            } \
        }; \
        Subclass##Registrar Subclass##RegistrarInstance; \
    }

class Derived1 : public Base {
public:
    std::string getName() const override { return "Derived1"; }
};

class Derived2 : public Base {
public:
    std::string getName() const override { return "Derived2"; }
};

REGISTER_SUBCLASS(Base, Derived1)
REGISTER_SUBCLASS(Base, Derived2)


namespace {
    Derived2 derived2;
}


#endif //KTDEMOCOLLECTION_BASETEST_H
