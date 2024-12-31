package com.example.jni_test

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentManager.FragmentLifecycleCallbacks
import com.example.jni_test.fragment.AnimTestFragment
import com.example.jni_test.fragment.FunctionTestFragment
import com.example.jni_test.fragment.JNITestTabsFragment
import com.example.jni_test.model.wrapper.DataSource

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_main)
        supportFragmentManager.registerFragmentLifecycleCallbacks(
            object : FragmentLifecycleCallbacks() {
                override fun onFragmentDetached(fm: FragmentManager, f: Fragment) {
                    super.onFragmentDetached(fm, f)
                    if (fm.backStackEntryCount == 0) {
                        setTitle(R.string.app_name)
                    }
                }
            }, true
        )
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

    fun onClickAnim(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                AnimTestFragment::class.java,
                Bundle()
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }

    fun onClickTest(view: View) {
        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                FunctionTestFragment::class.java,
                Bundle()
            )
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }
}
