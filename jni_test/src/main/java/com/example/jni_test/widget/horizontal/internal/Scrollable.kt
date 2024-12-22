package com.example.jni_test.widget.horizontal.internal

import com.example.jni_test.widget.horizontal.ScrollState


/**
 * 可滑动控件接口描述
 *
 * @author eriche 2021/12/28
 */
interface Scrollable<ScrollingData : IScrollingData, ScrolledData : IScrolledData> {

    fun getScrollingData(): ScrollingData

    fun getScrolledData(): ScrolledData

    fun scroll(scrollState: ScrollState, scrollingData: ScrollingData)

    fun scrollTo(scrolledData: ScrolledData)

    fun resetScroll()

    fun stopScroll()

}


interface IScrollingData : Cloneable {

    public override fun clone(): IScrollingData

    fun copy(other: Any): Boolean

}

interface IScrolledData : Cloneable {

    public override fun clone(): IScrolledData

    fun copy(other: Any): Boolean

}


