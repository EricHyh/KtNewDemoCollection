//
// Created by eriche on 2024/12/21.
//

#include "TestItem.h"

IC2NTestItemFactory *C2NTestItemFactory::s_factory = nullptr;

void C2NTestItemFactory::init(IC2NTestItemFactory *factory) {
    C2NTestItemFactory::s_factory = factory;
}

std::shared_ptr<ITestItem> C2NTestItemFactory::create(int index) {
    return C2NTestItemFactory::s_factory->create(index);
}
