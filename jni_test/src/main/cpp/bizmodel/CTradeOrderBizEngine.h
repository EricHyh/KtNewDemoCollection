//
// Created by eriche on 2025/6/5.
//

#pragma once


#include "TradeOrderBizEngine.h"

class CTradeOrderBizEngine : public ITradeOrderBizEngine {

public:
    void Init() override {

    }

    void Apply(std::shared_ptr<IModify> modify) override {
        auto bizModel_it = std::find_if(
                m_bizModel.begin(),
                m_bizModel.end(),
                [&](const std::shared_ptr<IFieldBizModel> &bizModel) {
                    return bizModel->IsMatched(modify);
                });
        if (bizModel_it != m_bizModel.end()) {
            const auto &bizModel = *bizModel_it;
            if (bizModel) {
                bizModel->Apply(modify);
            }
        }
    }

    FieldDataModel GetFieldDataModel() const override { // NOLINT
        return m_dataModel;
    }

private:
    std::vector<std::shared_ptr<IFieldBizModel>> m_bizModel;
    FieldDataModel m_dataModel;
};
