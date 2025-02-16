package com.example.jni_test

import com.example.jni_test.model.C2NTestItemFactory
import com.example.jni_test.model.IC2NTestItemFactory
import com.example.jni_test.model.IObserverManager
import com.example.jni_test.model.ITestItem
import com.example.jni_test.model.ObserverManager
import com.example.jni_test.model.TestColorFactory
import com.example.jni_test.model.TestObserverBridge
import com.example.jni_test.model.wrapper.NativeTestColor
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

    private val testColor = NativeTestColor()

    fun load() {
        C2NTestItemFactory.init(factory)
        TestColorFactory.init(testColor)
        ObserverManager.init(ObserverManagerImpl)
    }
}

object ObserverManagerImpl : IObserverManager() {


    private val observers: MutableSet<TestObserverBridge> = mutableSetOf()

    private var num = 0;

    override fun addObserver(observer: TestObserverBridge?) {
        observer ?: return
        observers.add(observer)
    }

    override fun removeObserver(observer: TestObserverBridge?) {
        observer ?: return
        observers.remove(observer)
    }

    fun notifyEvent() {
        num++
        observers.forEach {
            it.onCall(num)
        }
    }
}