package com.example.jni_test

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.example.jni_test.fragment.JNITestTabsFragment

class MainActivity : AppCompatActivity() {

    init {
        JNITest.load()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_main)
    }

    fun onClick(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                JNITestTabsFragment::class.java,
                Bundle()
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }
}
