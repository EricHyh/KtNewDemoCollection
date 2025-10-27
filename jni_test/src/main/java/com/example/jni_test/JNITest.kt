package com.example.jni_test

import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.Toast
import com.example.jni_test.model.wrapper.NativeTestColor
import com.example.jni_test.model.wrapper.NativeTestItem
import com.hyh.jnitest.test.color.TestColorFactory
import com.hyh.jnitest.test.item.C2NTestItemFactory
import com.hyh.jnitest.test.item.IC2NTestItemFactory
import com.hyh.jnitest.test.item.ITestItem
import com.hyh.jnitest.test.observer.IObserverManager
import com.hyh.jnitest.test.observer.ITestObserver2Bridge
import com.hyh.jnitest.test.observer.ObserverManager
import com.hyh.jnitest.test.observer.TestEnum1
import com.hyh.jnitest.test.observer.TestObserver2Vector
import com.hyh.jnitest.test.observer.TestObserverBridge
import com.hyh.jnitest.test.observer.TestStructVariantBridge

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

    private const val TAG = "ObserverManagerImpl"


    private val observers: MutableSet<TestObserverBridge> = mutableSetOf()
    private val observer2s: MutableSet<ITestObserver2Bridge> = mutableSetOf()

    private var num = 0;

    override fun addObserver(observer: TestObserverBridge?) {
        observer ?: return
        observers.add(observer)
    }

    override fun removeObserver(observer: TestObserverBridge?) {
        observer ?: return
        observers.remove(observer)
    }

    override fun addObserver2(observer: ITestObserver2Bridge?) {
        observer ?: return
        observer2s.add(observer)
    }

    override fun removeObserver2(observer: ITestObserver2Bridge?) {
        observer ?: return
        observer2s.remove(observer)
    }

    override fun add1(a: Long, b: Long): Long {
        return a + b
    }

    override fun add11(a: Long, b: Long): Long {
        return a + b
    }

    override fun add2(a: Long, b: Long): Long {
        return a + b
    }

    override fun add22(a: Long, b: Long): Long {
        return a + b
    }

    override fun add3(a: Long, b: Long): Long {
        return a + b
    }

    override fun add33(a: Long, b: Long): Long {
        return a + b
    }

    override fun byteTest1(byteArray: ByteArray?) {
        byteArray ?: return
        byteArray.forEach {
            Log.d(TAG, "byteTest1: $it")
        }
    }

    override fun byteTest2(byteArray: ByteArray?) {
        byteArray ?: return
        byteArray.forEach {
            Log.d(TAG, "byteTest2: $it")
        }
    }

    override fun byteTest3(): ByteArray {
        return byteArrayOf(20, 21, 22, 23)
    }

    override fun setTestObserver2List(arg0: TestObserver2Vector?) {
//        super.setTestObserver2List(arg0)
    }

    override fun optionalEnum33(): TestEnum1 {
        System.gc()
        System.runFinalization()
//        Thread.sleep(5000)
        return TestEnum1.AllTradingTime
    }

    override fun getObserver2(): ITestObserver2Bridge {
        return object : ITestObserver2Bridge() {
            override fun onCall(data: Int) {
                Handler(Looper.getMainLooper()).post {
                    Toast.makeText(AppContext.context, "$data", Toast.LENGTH_SHORT).show()
                }
            }

            override fun onCall2(variant: TestStructVariantBridge?) {
            }
        }
    }

    override fun test_bool_3(d: Boolean?) {
        super.test_bool_3(d)
    }

    override fun test_bool_1(d: Boolean?) {
        super.test_bool_1(d)
    }

    override fun test_double_1(d: Double?): Double? {
        return super.test_double_1(d)
    }

    override fun test_bool_2(): Boolean? {
        return super.test_bool_2()
    }

    fun notifyEvent() {
        num++
        observers.forEach {
            it.onCall(num)
        }
        observer2s.forEach {
            it.onCall(num)
        }
    }
}