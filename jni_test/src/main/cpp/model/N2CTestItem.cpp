//
// Created by eriche on 2024/12/20.
//

#include "N2CTestItem.h"
#include "N2CItemIcon.h"

using namespace test_util;

N2CTestItem::N2CTestItem(int index) {
    this->id = std::to_string(index);
    this->title = concat("这是第", index, "条数据的标题");
    this->envelopePic = "https://www.wanandroid.com/resources/image/pc/default_project_img.jpg";
    this->desc = concat("这是第", index, "条数据的描述", "，这是第", index, "条数据的描述", "，这是第", index,
                        "条数据的描述。");
    this->niceDate = concat("这是第", index, "条数据的日期");
    this->author = concat("这是第", index, "条数据的作者");

    std::vector<std::string> temp_tags;
    temp_tags.reserve(40);  // 预分配空间以提高效率

    for (int i = 0; i < 40; ++i) {
        temp_tags.push_back("这是标签-" + std::to_string(i));
    }
    this->tags = temp_tags;

    unsigned int size = test_util::icons.size();
    std::vector <std::shared_ptr<IItemIcon>> temp_icons;
    temp_icons.reserve(size);
    for (int i = 0; i < size; ++i) {
        const std::shared_ptr<IItemIcon> &ptr = std::make_shared<N2CItemIcon>(N2CItemIcon(i));
        temp_icons.push_back(ptr);
    }
    
    this->icons = temp_icons;

}
