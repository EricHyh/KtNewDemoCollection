package com.example.ndkdemo

import android.os.Build.VERSION_CODES.P
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.widget.TextView
import androidx.activity.ComponentActivity
import com.example.ndk_demo_lib.TestJNI
import com.example.ndk_demo_lib1.SwigCallback
import com.example.ndk_demo_lib1.SwigCallbackData
import com.example.ndk_demo_lib1.SwigCallbackFunction1Bridge
import com.example.ndk_demo_lib1.SwigCallbackFunctionBridge
import com.example.ndk_demo_lib1.TestSwigCallback

class MainActivity : ComponentActivity() {


    companion object{

        private const val TAG = "MainActivity_"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val textView = findViewById<TextView>(R.id.tv_content)
        val testJNI = TestJNI<Int>()
        TestGc()

//        testSwig.testCallback(object : TestCallbackWrapper() {
//            override fun call(value: Double) {
//                Toast.makeText(applicationContext, "$value", Toast.LENGTH_LONG).show()
//            }
//        })


//        val l = LegacyClass()
//        l.set_property("Hello World!")
//        Toast.makeText(applicationContext, "good:${l._property}", Toast.LENGTH_LONG).show()

//        TestJavaCpp.TestJavaCppClass().test(object :TestJavaCpp.TestJavaCppCallback(){
//            override fun call(value: Int): Boolean {
//                Toast.makeText(applicationContext, "good:${value}", Toast.LENGTH_LONG).show()
//                return true
//            }
//        })



    }

    override fun onResume() {
        super.onResume()
        Handler().postDelayed({

            val testSwigCallback = TestSwigCallback()


//            testSwigCallback.setCallback1(object : SwigCallback() {
//                override fun onTest1(data1: SwigCallbackData?) {
//                    Log.d(TAG, "onTest1: ${System.identityHashCode(this)} " + data1?.a)
//                }
//
//                override fun onTest2(data2: SwigCallbackData?) {
//                    Log.d(TAG, "onTest2: ${System.identityHashCode(this)} " + data2?.a)
//                }
//            })

//            testSwigCallback.setCallback2(object : SwigCallback() {
//                override fun onTest1(data1: SwigCallbackData?) {
//                    Log.d(TAG, "onTest1: ${System.identityHashCode(this)} " + data1?.a)
//                }
//
//                override fun onTest2(data2: SwigCallbackData?) {
//                    Log.d(TAG, "onTest2: ${System.identityHashCode(this)} " + data2?.a)
//                }
//            })
//
//            testSwigCallback.setCallback3(90, object : SwigCallback() {
//                override fun onTest1(data1: SwigCallbackData?) {
//                    Log.d(TAG, "onTest1: ${System.identityHashCode(this)} " + data1?.a)
//                }
//
//                override fun onTest2(data2: SwigCallbackData?) {
//                    Log.d(TAG, "onTest2: ${System.identityHashCode(this)} " + data2?.a)
//                }
//            })
//
//            testSwigCallback.setCallback4(object : SwigCallbackFunctionBridge() {
//                override fun onCall(param: SwigCallbackData?) {
//                    Log.d(TAG, "onCall: ${System.identityHashCode(this)} " + param?.a)
//                }
//            })

            testSwigCallback.setCallback5(object : SwigCallbackFunction1Bridge() {
                override fun onCall(param: SwigCallbackData?) {
                    Log.d(TAG, "onCall: ${System.identityHashCode(this)} " + param?.a)
                }
            })

//            System.gc()
//            System.gc()
        }, 1000L)


        Handler().postDelayed({
            System.gc()
            System.gc()
        }, 2000)
    }

}

class TestGc {

    protected fun finalize() {
        Log.d("TestGc", "finalize: TestGc")
    }

}