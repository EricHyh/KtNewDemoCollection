package com.example.jni_test.model.wrapper

import com.example.jni_test.utils.DisplayUtil
import com.hyh.jnitest.test.color.ITestColor

/**
 * TODO
 *
 * @author eriche 2024/12/29
 */
class TestColorWrapper(
    private val testColor: ITestColor,
    private val count: Int
) {


    fun getRandomColor(): Int {
        (0 until count).forEach { _ ->
            testColor.randomColor
        }
        return testColor.randomColor
    }

}

class NativeTestColor : ITestColor() {

    private val random = java.util.Random()

    override fun getRandomColor(): Int {
        return DisplayUtil.getRandomColor(random)
    }

    override fun add(a: String?, b: String?): String {
        val a_num = a?.toInt() ?: 0
        val b_num = b?.toInt() ?: 0
        return (a_num + b_num).toString()
    }
}