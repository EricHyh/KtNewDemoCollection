package com.example.jni_test

import android.app.Application

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
class AppContext : Application() {

    override fun onCreate() {
        super.onCreate()
        JNITest.load()
    }
}