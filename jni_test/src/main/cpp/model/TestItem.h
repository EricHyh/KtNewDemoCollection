//
// Created by eriche on 2024/12/20.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ItemIcon.h"

class ITestItem {
public:

    virtual ~ITestItem() = default;

    virtual std::string getId() = 0;

    virtual std::string getTitle() = 0;

    virtual std::string getEnvelopePic() = 0;

    virtual std::string getDesc() = 0;

    virtual std::string getNiceDate() = 0;

    virtual std::string getAuthor() = 0;

    virtual std::vector<std::string> getTags() = 0;

    virtual std::vector<std::shared_ptr<IItemIcon>> getIcons() = 0;

};

class IC2NTestItemFactory {

public:
    virtual ~IC2NTestItemFactory() = default;

    virtual std::shared_ptr<ITestItem> create(int index) = 0;

};

class C2NTestItemFactory {

public:
    static void init(IC2NTestItemFactory* factory);
    static std::shared_ptr<ITestItem> create(int index);


private:
    static IC2NTestItemFactory *s_factory;
};