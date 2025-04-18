package com.hyh.model


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

enum class FilterType(val value: Int) {
    BlackList(0),
    WhiteList(1),
}

//data class (
//        val stock : bool,
//        val option;
//        val margin;
//        )


enum class PropType(val value: Int) {
    Category(0),
    TimeType(1),
    OrderType(2),
    TimeInForce(3),
    OrderSideType(4),
    QuantityType(5),
}

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