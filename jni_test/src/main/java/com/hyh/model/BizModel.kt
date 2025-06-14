package com.hyh.model

import android.view.WindowInsets.Side.all
import com.hyh.base.RefreshStrategy


interface IPredefineFilter {

    val filterType: FilterType

    val props: List<PropType>

    fun filter(params: Map<PropType, Int>): Boolean

}


data class BasicTradeAbility(
    val category: List<Int>,
    val timeType: List<Int>,
    val orderType: List<Int>,
    val timeInForce: List<Int>,
    val orderSideType: List<Int>,
    val quantityType: List<Int>,
)

enum class PropType(val value: Int) {
    Category(0),
    TimeType(1),
    OrderType(2),
    TimeInForce(3),
    OrderSideType(4),
    QuantityType(5),
}

data class BasicTradeAbility2(
    val map: Map<PropType, List<Int>>
)


enum class FilterType(val value: Int) {
    BlackList(0),
    WhiteList(1),
}

enum class OptionStrategyType {}

//data class (
//        val stock : bool,
//        val option;
//        val margin;
//        )


data class Filter(
    val filterType: FilterType,
    val propsAndValues: Map<PropType, List<Int>>,
    val filterPropsAndValues: Map<PropType, List<Int>>,
)


class TradeAbilitySpace(
    private val abilities: List<BasicTradeAbility>,
    private val filters: List<Filter>
) {

//    fun getOrderType(category: Int): List<Int> {
//
//        // 1. 找到 abilities 中符合 category 的能力，得到一个列表 A
//        // 2.
//
//
////        val filter = filters.find { filter ->
////            filter.filterPropsAndValues.all { (key, value) ->
////                key == PropType.Category && value.all { it in abilities[0].category }
////            }
////        }
////        if (filter != null) {
////            return abilities.filter {
////                it.category.contains(category)
////            }.flatMap { ability ->
////                ability.orderType.filterNot {
////                    it in (filter.propsAndValues[PropType.Category] ?: emptyList())
////                }
////            }.distinct()
////        }
////
////        return abilities.filter {
////            it.category.contains(category)
////        }.flatMap { ability ->
////            ability.orderType
////        }.distinct()
//
//
////        abilities.filter {
////            it.category.contains(category)
////        }.flatMap { ability ->
////
////
////
////            val filter = filters.find { filter ->
////                filter.filterPropsAndValues.all { (key, value) ->
////                    ability.category.contains(key) && value.all { it in ability.category }
////                }
////            }
////            if (filter != null) {
////                ability.orderType.filterNot {
////                    it in (filter.propsAndValues[category] ?: emptyList())
////                }
////            } else {
////                ability.orderType
////            }
////        }.distinct().let {
////            return it
////        }
//    }


}


fun combine(abilities: List<BasicTradeAbility>) {

}

interface MapMidd{

}

interface IBizAbility<Int> {

    fun getSupportedAbilities(target:Int, params: Map<Int, String>): List<Int>{
//        val all: list<int> = all();
//        all.filter{};
    }

    fun isMatched(params: Map<Int, String>): Boolean // 产品集、行情大类、行情小类

}

fun xx(a:IBizAbility<*>){
    a.getSupportedAbilities({100000 to 16});
}

std::vector<FINTradeTimeType> GetTradeTimeTypes(
    const FINAccount& account,
    const FINTradeProduct& product,
    const FINTAbilityPropertyValues relationProperty;
){
//    val futuSymbol: String,
//    val stockId: Long,
//    val instrument: Int,
//    val subInstrument: Int,
//    val instrumentV2: Int,
//    val subInstrumentV2: Int,
//    val marketCode: Int
    val ability: IBizAbility;
    // account - broker;
    map[{0 , account.broker}, {100002, product.futuSymbol}...];
    val result :List<int> = ability.GetSupportedAbilities(100000, map);

    // 综合账户
    // DVP
    // JP融资
    // JP现金
    result.filter{};
}

interface IAccountBizAbility<Int> {

    fun getSupportedAbilities(): List<Int>{

    fun isMatched(账户类型, 订单类型): Boolean

    fun isMatched(账户类型, 品类): Boolean

}


//data class TradeAbility(
//    val enableOption: Boolean,
//    val enableOptionStrategy: Boolean,
//    val enableMargin: Boolean,
//    val enableSellShort: Boolean,
//    val enableLotOrder: Boolean,
//    val enableAmountOrder: Boolean
//)

interface ProductData

data class Product(
    val productId: Int,
    val productData: ProductData
)

data class StockProduct(
    val futuSymbol: String,
    val stockId: Long,
    val instrument: Int,
    val subInstrument: Int,
    val instrumentV2: Int,
    val subInstrumentV2: Int,
    val marketCode: Int
) : ProductData

data class OptionStrategyProduct(
    val strategyType: OptionStrategyType
) : ProductData


interface IBrokerProductAbility {

    fun isSupported(product: Product): Boolean

}


interface BlackList {
    fun isInList(properties: List<PropType>): Boolean

}

interface Visitor {

};
