package com.example.jni_test

import com.example.jni_test.model.C2NTestItemFactory
import com.example.jni_test.model.IC2NTestItemFactory
import com.example.jni_test.model.ITestItem
import com.example.jni_test.model.wrapper.NativeTestItem

/**
 * TODO: Add Description
 *
 * @author eriche 2024/12/20
 */
object JNITest {

    init {
        System.loadLibrary("JNITest");
    }

    private val factory = object : IC2NTestItemFactory() {
        override fun create(index: Int): ITestItem {
            return NativeTestItem(index)
        }
    }

    fun load() {
        C2NTestItemFactory.init(factory)
    }
}