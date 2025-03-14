//
// Created by eriche on 2025/3/12.
//

#pragma once

#include <memory>
#include <unordered_set>

enum Market1 {
};

enum Market2 {
};

class XXX {
};


namespace eric::good::test1 {

    class IFINBrokerCapabilityConfig {
    public:
        virtual ~IFINBrokerCapabilityConfig() = default;

        /**
         * @brief   获取支持的市场
         * @return  std::unordered_set
         */
        virtual std::unordered_set<Market1> GetSupportEnableMarkets() const = 0;
    };


    /**
     * @brief   获取券商能力配置
     * @notice  此接口多线程安全
     * @param   brokerType 券商类型
     * @return  std::shared_ptr
     */
    std::shared_ptr<const IFINBrokerCapabilityConfig> GetBrokerCapabilityConfig(Market2 brokerType);

    std::shared_ptr<XXX> GetBrokerCapabilityConfig2(Market2 brokerType);

};


template<class Value>
struct FiledKey {
public:
    const uint32_t id;

    const Value defaultValue;

    FiledKey() = delete;

    FiledKey(uint32_t id, const Value &value) : id(id), defaultValue(value) {}
};

namespace FiledKeys {

    extern const FiledKey<int> price;

    extern const FiledKey<std::string> quantity;

}
