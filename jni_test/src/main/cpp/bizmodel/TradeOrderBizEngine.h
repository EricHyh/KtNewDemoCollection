//
// Created by eriche on 2025/6/5.
//

#pragma once

#include <memory>
#include "FieldBizModel.h"


class ITradeOrderBizEngine {

public:
    virtual ~ITradeOrderBizEngine() = default;

    virtual void Init() = 0;

    virtual void Apply(std::shared_ptr<IModify> modify) = 0;

    virtual FieldDataModel GetFieldDataModel() const = 0;

};
