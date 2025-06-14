//
// Created by eriche on 2025/4/22.
//

#pragma once

#include <string>
#include <cstdint>
#include <variant>
#include <vector>
#include <unordered_map>

enum class FINBroker {
};
enum class OptionStrategyType {
};

/**
 * 股票产品信息
 */
struct FINStockProductInfo {
    std::string futuSymbol;
    uint32_t stockId;
    uint32_t instrument;
    uint32_t subInstrument;
    uint32_t instrumentV2;
    uint32_t subInstrumentV2;
    uint32_t marketCode;
    bool isPreMarketAuctionEnabled;
};

/**
 * 组合期权产品信息
 */
struct FINOptionStrategyProductInfo {
    OptionStrategyType strategyType;
};

using FINTradeProductInfo = std::variant<FINStockProductInfo, FINOptionStrategyProductInfo>;

/**
 * 交易产品模型
 */
struct FINTradeProduct {
    int productId;
    FINTradeProductInfo productInfo;
};


/**
 * 可交易参数配置，
 * 应用于更精细化的产品可交易能力判断，例如判断账户的交易能力
 */
struct FINTradableParam {
    FINBroker broker;           // 券商
    bool stockEnabled;          // 支持交易股票（非期权）
    bool optionEnabled;         // 支持交易期权（非组合期权）
    bool optionStrategyEnabled; // 支持交易期权组合
};


namespace fin::transaction::product_ability {

    /**
     * 产品在指定**券商**是否可交易
     *
     * @param broker    券商
     * @param product   产品
     * @return
     */
    bool isTradable(FINBroker broker, FINTradeProduct product);

    /**
     * 产品在指定**可交易参数配置**下是否可交易
     *
     * @param param     可交易参数配置
     * @param product   产品
     * @return
     */
    bool isTradable(FINTradableParam param, FINTradeProduct product);
    
    
    /**
     * 在指定**券商**和**可交易参数配置**下的可以交易产品列表
     *
     * @param broker    券商
     * @param param     可交易参数配置
     * @param product   产品
     * @return
     */
     std::vector<int> GetSupportedProductIds(FINBroker broker, FINTradableParam param);
}

/**
 * 交易时段
 */
enum class FINTradeTimeType {
    Unset,                  // 未设置
    Market,                 // 盘中
    EnablePreAfterMarket,   // 盘前+盘后+盘中
    NightMarket,            // 夜盘
    AllTradingTime,         // 全时段
};

/**
 * 交易类型（对外上层表现的能力）
 */
enum class FINTradeType {
    Unknown
};

/**
 * 订单类型（对应金融平台提供的能力）
 */
enum class FINOrderType {
    Unknown,               // 未知
};


enum class FINTradeDirection {
    Unset,                  // 未指定
    LongOpen,               // 多头开仓
    LongClose,              // 多头平仓
    ShortOpen,              // 空头开仓
    ShortClose,             // 空头平仓
    DesignatedLongClose,    // 指定多头平仓：明确指定平仓多头头寸，常用于限价或条件触发交易
    DesignatedShortClose,   // 指定空头平仓：明确指定平仓空头头寸，常用于风险管理或止损操作
    PositionTransfer,       // 移仓：将持仓从当前合约转移至另一合约，保持头寸方向和数量不变。例如："移仓是相同持仓方向和数量的合约转移"
    PositionReverse,        // 反手：平仓当前头寸的同时反向开仓。例如："反手即平多单开空单，或平空单开多单"
};


/**
 * 订单数量类型
 */
enum class FINQuantityType {
    RoundLots,      // 整手
    OddLots,        // 碎股
    Fractional,     // 小数股
    Amount          // 金额
};


/**
 * 订单期限类型
 */
enum class FINOrderInForceType {
    GTC,  // Good Till Cancel
    IOC,  // Immediate or Cancel
    FOK,  // Fill or Kill
    GTD,  // Good Till Date
};

/**
 * 账户结构类型
 */
enum class FINAccountStructureType {
};


enum class FINAdvancedOrderType {
    Unset,                  // 未设置
    AdditionalOrder,        // 附加订单
    GroupCondition,         // 组合条件单
    OCOOrder,               // OCO订单
};

/**
 * 交易账户信息
 */
struct FINTradeAccount {
    FINBroker broker;                       // 券商
    std::vector<int> enabledProductIds;     // 支持的产品ID列表
};

/**
 * 基础订单信息
 */
struct FINBasicOrderInfo {
    FINTradeTimeType tradeTimeType;         // 交易时段
    FINOrderType orderType;                 // 订单类型
    FINOrderInForceType orderInForceType;   // 订单期限类型
    FINQuantityType quantityType;           // 订单数量类型
};

/**
 * 属性定义
 */
enum class FINTradeAbilityProperty {
    Unset,                  // 未设置
    TradeTimeType,          // 交易时段
    OrderType,              // 订单类型
    OrderInForceType,       // 订单期限类型
    QuantityType,           // 订单数量类型
    TradeDirection,         // 交易方向
    //.....省略其他属性
};

/**
 * 单属性值列表
 */
struct FINTAbilityPropertyValues {
    FINTradeAbilityProperty property;       // 交易能力属性
    std::vector<std::string> values;        // 交易能力属性值
};

/**
 * 属性空间构造器
 */
class FINTAbilityPropertyValuesBuilder {
public:

    void SetTradeTimeType(FINTradeTimeType tradeTimeType);

    void SetOrderType(FINOrderType orderType);

    void SetOrderInForceType(FINOrderInForceType orderInForceType);

    void SetQuantityType(FINQuantityType quantityType);

    //......省略其他属性

    std::vector<FINTAbilityPropertyValues> Build();

private:
    FINTradeTimeType m_tradeTimeType;
    FINOrderType m_orderType;
    FINOrderInForceType m_orderInForceType;
    FINQuantityType m_quantityType;
    //......省略其他属性
};


namespace fin::transaction::basic_order_ability {

    /**
     * 获取支持的交易时段
     * @param accountInfo   交易账户信息
     * @param product       产品信息
     * @param propertyValues 交易能力属性值
     * @param ignoredProperties 忽略的交易能力属性
     * @return
     */
    std::vector<FINTradeTimeType> GetTradeTimeTypes(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::vector<FINTAbilityPropertyValues>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    /**
     * 获取支持的交易类型
     * @param accountInfo   交易账户信息
     * @param product       产品信息
     * @param tradeTimeType 交易能力属性值
     * @return
     */
    std::vector<FINTradeType> GetTradeTypes(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );


    /**
     * 获取支持的期限类型
     * @param accountInfo   交易账户信息
     * @param product       产品信息
     * @param tradeType     交易能力属性值
     * @return
     */
    std::vector<FINOrderInForceType> GetOrderInForceTypes(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );


    /**
     * 获取支持的数量类型
     * @param accountInfo   交易账户信息
     * @param product       产品信息
     * @param tradeType     交易能力属性值
     * @return
     */
    std::vector<FINQuantityType> GetQuantityTypes(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );


    bool isQuantityTypeSupported(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    bool isTimeTypeAndTradeTypeMatched(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            FINTradeTimeType timeType,
            FINTradeType tradeType
    );


    bool isTradeTypeAndOrderInForceMatched(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            FINTradeType tradeType,
            FINOrderInForceType orderInForce
    );

    /**
     * 将交易类型转换为订单类型
     * @param accountInfo   交易账户信息
     * @param product       产品信息
     * @param tradeType     交易类型
     * @param isLimitAlgorithmOrderType 是否限价算法单
     * @return
     */
    FINOrderType GetOrderType(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            FINTradeType tradeType,
            bool isLimitAlgorithmOrderType
    );


}


namespace fin::transaction::advanced_order_ability {

    bool isSupportedAdditionalOrder(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    bool isSupportedGroupCondition(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    bool isSupportedOCOOrder(
            const FINTradeAccount& accountInfo,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& propertyValues,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );
}


namespace fin::transaction::ability_query {

    std::vector<std::string> GetPropertyValues(
            FINBroker broker,
            int productId,
            FINTradeAbilityProperty targetProperty,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& properties,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    bool IsValid(
            FINBroker broker,
            const FINTradeProduct& product,
            const std::unordered_map<FINTradeAbilityProperty, std::string>& properties,
            const std::vector<FINTradeAbilityProperty>& ignoredProperties = {}
    );

    bool IsPropertyMatched(
            FINBroker broker, const FINTradeProduct& product,
            std::pair<FINTradeAbilityProperty, std::string> firstProperty,
            std::pair<FINTradeAbilityProperty, std::string> secondProperty
    );
}


/**
 * 获取最优的交易时段类型
 * @param accountInfo 交易账户信息
 * @param product 产品信息
 * @param specifiedTradeType 指定的交易类型，空值表示不指定
 * @param specifiedTradeTimeTypes 指定的交易时段类型
 * @return 最优的交易时段类型
 */
FINTradeTimeType GetOptimizedTradeTimeType(
        const FINTradeAccount& accountInfo,
        const FINTradeProduct& product,
        std::optional<FINTradeType> specifiedTradeType,
        const std::vector<FINTradeTimeType>& specifiedTradeTimeTypes
) {
    std::vector<FINTradeTimeType> supportedTradeTimeTypes = fin::transaction::basic_order_ability::GetTradeTimeTypes(
            accountInfo,
            product,
            {},
            {}
    );
    if (!specifiedTradeTimeTypes.empty()) {
        auto it = std::find_if(specifiedTradeTimeTypes.begin(), specifiedTradeTimeTypes.end(),
                               [supportedTradeTimeTypes](const FINTradeTimeType& obj) {
                                   auto it = std::find(supportedTradeTimeTypes.begin(), supportedTradeTimeTypes.end(), obj);
                                   return it != supportedTradeTimeTypes.end();
                               });
        if (it != specifiedTradeTimeTypes.end()) {
            return *it;
        }
    }
    return !supportedTradeTimeTypes.empty() ? supportedTradeTimeTypes[0] : FINTradeTimeType::Unset;
}

class IFINAccount{};


/**
 * 获取最优的交易账户，当股票切换时
 * @param currentAccount    当前账户
 * @param newProduct        新股票
 * @param fallbackAccounts  后备的账户列表
 * @return 优先账户
 */
IFINAccount GetOptimizedAccountWhenProductSwitched(
        const IFINAccount& currentAccount,
        const FINTradeProduct& newProduct,
        const std::vector<IFINAccount>& fallbackAccounts,
) {
    FINBroker broker = currentAccount.GetBroker();
    FINTradableParam param = CreateTradableParam(currentAccount);
    std::vector<int> productIds = fin::transaction::product_ability::GetSupportedProductIds(broker, param);
    if (productIds.container(newProduct.productId)) {
        return currentAccount;
    }
    IFINAccount account = std::find_if(fallbackAccounts.begin(), fallbackAccounts.end()) { account ->
        FINBroker broker = account.GetBroker();
        FINTradableParam param = CreateTradableParam(account);
        std::vector<int> productIds = fin::transaction::product_ability::GetSupportedProductIds(
                broker, param);
        return productIds.container(newProduct.productId);
    }
    return account;
}

