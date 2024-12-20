package com.example.ndk_demo_lib

import android.util.Log

/**
 * TODO: Add Description
 *
 * @author eriche 2024/10/8
 */
class TestJNI<T> {
    companion object {
        private const val TAG = "TestJNI"

        init {
            System.loadLibrary("native-lib");
        }
    }

    fun test() {
        test(100)

        test(1000)

        test(10000)

        test(100000)

        test(1000000)

        test(10000000)

        test(100000000)
    }

    private fun test(num: Int) {
        val start1 = System.currentTimeMillis()
        for (i in 0..num) {
            java_add()
        }
        val end1 = System.currentTimeMillis()
        Log.d(TAG, "test_java_add ${num}: use time: ${end1 - start1}")

        val start2 = System.currentTimeMillis()
        for (i in 0..num) {
            add()
        }
        val end2 = System.currentTimeMillis()
        Log.d(TAG, "test c_add ${num}: use time: ${end2 - start2}")

        test_java_add(num)
    }

    external fun test_java_add(num: Int)

    external fun add()

    fun java_add() {

    }

    external fun test_sort()
}


class TestData1 constructor(
    val value1: Int,
    val value2: String,
)

class TestData2 constructor(
    val value1: Int,
    val value2: String,
)


fun interface TestCallbackJni<T> {

    fun onTest(data: T)

}