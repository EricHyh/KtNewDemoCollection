package com.example.ndkdemo

import android.os.Build.VERSION_CODES.P
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.TextView
import androidx.activity.ComponentActivity
import com.example.ndk_demo_lib.TestJNI
import com.example.ndk_demo_lib1.InnerObserver2Bridge
import com.example.ndk_demo_lib1.SwigCallback
import com.example.ndk_demo_lib1.SwigCallbackData
import com.example.ndk_demo_lib1.SwigCallbackFunction1Bridge
import com.example.ndk_demo_lib1.TestSwigCallback

class MainActivity : ComponentActivity() {


    companion object {

        private const val TAG = "MainActivity_"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val textView = findViewById<TextView>(R.id.tv_content)
        val testJNI = TestJNI<Int>()


        Handler(Looper.getMainLooper()).postDelayed({
            testJNI.test_sort()
        }, 2000)

    }

//    override fun onResume() {
//        super.onResume()
//        Handler().postDelayed({
//
//            val testSwigCallback = TestSwigCallback()
//
//            testSwigCallback.setCallback3(90, object : SwigCallback() {
//                override fun onTest1(data1: SwigCallbackData?) {
//                    Log.d(TAG, "onTest1: ${System.identityHashCode(this)} " + data1?.a)
//                }
//
//                override fun onTest5(a: Int, b: String?, innerCallback: InnerObserver2Bridge?, c: Int) {
//                    Log.d(TAG, "onTest5: ${System.identityHashCode(this)}")
//
//                    Handler(Looper.getMainLooper()).postDelayed({
//                        Log.d(TAG, "innerCallback onCall:")
//                        innerCallback?.onCall(SwigCallbackData(110))
//                        System.gc()
//                        System.gc()
//                    }, 5000)
//
//                    System.gc()
//                    System.gc()
//                }
//            })
//
//            testSwigCallback.setCallback5(object : SwigCallbackFunction1Bridge(){
//                override fun onCall(data: SwigCallbackData?) {
//
//                }
//            })
//
//            System.gc()
//            System.gc()
//        }, 1000L)
//
//
//        Handler().postDelayed({
//            System.gc()
//            System.gc()
//        }, 2000)
//    }


    private fun add(a: Int, b: Int): Int {
        return a + b
    }
}

class TestGc {

    protected fun finalize() {
        Log.d("TestGc", "finalize: TestGc")
    }

}