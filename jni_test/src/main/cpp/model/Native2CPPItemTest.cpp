//
// Created by eriche on 2024/12/20.
//

#include "Native2CPPItemTest.h"
#include <sstream>
#include <iostream>


namespace {

    template<typename... Args>
    std::string concat(Args &&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        return oss.str();
    }

}

Native2CPPItemTest::Native2CPPItemTest(int index) {
    this->id = std::to_string(index);
    this->title = concat("这是第", index, "条数据的标题");
    this->envelopePic = "https://www.wanandroid.com/blogimgs/9fc6e10c-b3e8-46bb-928b-05ccd2147335.png";
    this->desc = concat("这是第", index, "条数据的描述", "，这是第", index, "条数据的描述", "，这是第", index,
                        "条数据的描述。");
    this->niceDate = concat("这是第", index, "条数据的日期");
    this->author = concat("这是第", index, "条数据的作者");
}
