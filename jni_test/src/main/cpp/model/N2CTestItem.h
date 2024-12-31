//
// Created by eriche on 2024/12/20.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../TestUtil.h"
#include "ItemIcon.h"
#include "TestItem.h"


class N2CTestItem : public ITestItem {

public:
    N2CTestItem(int index);

    ~N2CTestItem() = default;

    std::string getId() override {
//        LOGI("getId: %s", this->id.c_str());
        return this->id;
    }

    std::string getTitle() override {
//        LOGI("getTitle: %s", this->title.c_str());
        return this->title;
    }

    std::string getEnvelopePic() override {
//        LOGI("getEnvelopePic: %s", this->envelopePic.c_str());
        return this->envelopePic;
    }

    std::string getDesc() override {
//        LOGI("getDesc: %s", this->desc.c_str());
        return this->desc;
    }

    std::string getNiceDate() override {
//        LOGI("getNiceDate: %s", this->niceDate.c_str());
        return this->niceDate;
    }

    std::string getAuthor() override {
//        LOGI("getAuthor: %s", this->author.c_str());
        return this->author;
    }

    std::vector <std::string> getTags() override {
//        LOGI("getTags");
        return this->tags;
    }

    std::vector <std::shared_ptr<IItemIcon>> getIcons() override {
//        LOGI("getIcons");
        return this->icons;
    }

private:
    std::string id;
    std::string title;
    std::string envelopePic;
    std::string desc;
    std::string niceDate;
    std::string author;
    std::vector <std::string> tags;
    std::vector <std::shared_ptr<IItemIcon>> icons;
};
