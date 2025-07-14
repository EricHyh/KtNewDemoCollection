package com.example.jni_test

import android.annotation.SuppressLint
import android.app.Application
import android.content.Context

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
class AppContext : Application() {

    companion object {
        @SuppressLint("StaticFieldLeak")
        lateinit var context: Context;
    }

    init {
        context = this;
    }

    override fun attachBaseContext(base: Context?) {
        super.attachBaseContext(base)
    }

    override fun onCreate() {
        super.onCreate()
        JNITest.load()
    }

}

class Test {
    fun test(n: Int) {
        val a = 10
        if (a == 10) {
            val b = 10 // 局部变量 b 在此处声明
        } // b 的作用域到此结束
    }

    fun test2(n: Int) {
        val a = 10
        if (a == 10) {
            val b = 10 // 局部变量 b 在此处声明
        } // b 的作用域到此结束
    }
}