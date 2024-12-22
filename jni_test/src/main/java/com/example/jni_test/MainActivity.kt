package com.example.jni_test

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.example.jni_test.fragment.JNITestTabsFragment
import com.example.jni_test.model.wrapper.DataSource

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_main)
    }

    fun onClickNative(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                JNITestTabsFragment::class.java,
                Bundle().apply {
                    putSerializable("DataSource", DataSource.NATIVE)
                }
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }

    fun onClickJ2C(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                JNITestTabsFragment::class.java,
                Bundle().apply {
                    putSerializable("DataSource", DataSource.NATIVE_TO_CPP)
                }
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }

    fun onClickJ2C2J(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                JNITestTabsFragment::class.java,
                Bundle().apply {
                    putSerializable("DataSource", DataSource.CPP_TO_NATIVE)
                }
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }
}
