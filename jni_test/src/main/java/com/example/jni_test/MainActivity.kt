package com.example.jni_test

import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentManager.FragmentLifecycleCallbacks
import com.example.jni_test.fragment.AnimTestFragment
import com.example.jni_test.fragment.FunctionTestFragment
import com.example.jni_test.fragment.JNITestTabsFragment
import com.example.jni_test.model.JNITestEntrance
import com.example.jni_test.model.ObserverManager
import com.example.jni_test.model.wrapper.DataSource
import org.json.JSONObject

class MainActivity : AppCompatActivity() {


    companion object {
        private const val TAG = "MainActivity"
    }

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


        val json = JSONObject().apply {
            put("num", "9999999999999999999999999")
        }

        val optInt = json.optInt("num", Int.MAX_VALUE)

        try {
            val toInt = "9999999999999999999999999".toDouble().toInt()

            val parseInt = Integer.parseInt("9999999999999999999999999")

            Log.d(TAG, "onCreate: NumberFormatException $parseInt")

        } catch (ignored: NumberFormatException) {
            Log.d(TAG, "onCreate: NumberFormatException")
        }

        Log.d(TAG, "onCreate: $json , $optInt")

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

    fun onAddObserver(view: View) {
        for (index in 1..10) {
            JNITestEntrance.testAddObserver(index)
        }
    }

    fun onRemoveObserver(view: View) {
        for (index in 6..10) {
            JNITestEntrance.testRemoveObserver(index)
        }
    }

    fun onNotifyObservers(view: View) {
        ObserverManagerImpl.notifyEvent()

        ObserverManager.byteTest1(byteArrayOf(1, 2, 3, 4))
        ObserverManager.byteTest2(byteArrayOf(5, 6, 7, 8))
        val byteTest3 = ObserverManager.byteTest3()
        byteTest3.forEach {
            Log.d(TAG, "onNotifyObservers: byte $it")
        }
    }
}
