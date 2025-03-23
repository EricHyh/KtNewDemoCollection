package com.example.jni_test.fragment

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.RadioGroup
import android.widget.TextView
import com.example.jni_test.R
import com.example.jni_test.model.wrapper.NativeTestColor
import com.hyh.jnitest.test.color.ITestColor
import com.hyh.jnitest.test.color.N2CTestColor
import com.hyh.jnitest.test.color.TestColorFactory
import kotlin.system.measureTimeMillis

/**
 * TODO
 *
 * @author eriche 2024/12/29
 */
class FunctionTestFragment() : CommonBaseFragment() {

    private var fragmentContent: ViewGroup? = null

    private var type = 0
    private var count: Int = 0

    override fun getContentView(inflater: LayoutInflater, container: ViewGroup?): View {
        return inflater.inflate(R.layout.fragment_function_test, container, false)
    }

    @SuppressLint("SetTextI18n")
    override fun initView(contentView: View) {
        fragmentContent = contentView.findViewById<ViewGroup>(R.id.fragment_content)
        contentView.findViewById<RadioGroup>(R.id.rg_type).setOnCheckedChangeListener { group, checkedId ->
            when (checkedId) {
                R.id.rb_type_native -> type = 0
                R.id.rb_type_native2cpp -> type = 1
                R.id.rb_type_cpp2native -> type = 2
                else -> 0
            }
        }

        val editText = contentView.findViewById<EditText>(R.id.edt_number)
        val duration = contentView.findViewById<TextView>(R.id.tv_duration)

        contentView.findViewById<View>(R.id.btn_execute).setOnClickListener {

            val testColor = getTestColor()

            val num = editText.text?.toString()?.toIntOrNull() ?: 1

            val timeMillis = measureTimeMillis {
                (0 until num).forEach { _ ->
                    testColor.add("100", "-100")
                }
            }

            duration.text = "调用次数：$num | 总耗时：$timeMillis ms"
        }
    }

    override fun initData() {}

    private fun getTestColor(): ITestColor {
        return when (type) {
            0 -> NativeTestColor()
            1 -> N2CTestColor()
            2 -> TestColorFactory.create()
            else -> NativeTestColor()
        }
    }
}