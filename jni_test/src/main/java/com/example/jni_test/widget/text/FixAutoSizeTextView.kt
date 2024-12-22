package com.example.jni_test.widget.text

import android.content.Context
import android.util.AttributeSet
import android.util.TypedValue
import androidx.appcompat.widget.AppCompatTextView
import androidx.core.widget.TextViewCompat
import com.example.jni_test.BuildConfig

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
open class FixAutoSizeTextView : AppCompatTextView {
    //region constructor
    constructor(context: Context) : super(context)

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs)

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(context, attrs, defStyleAttr)


    override fun setText(text: CharSequence?, type: BufferType) {
        var minTextSize = 0
        var maxTextSize = 0
        var granularity = 0
        var doHack = TextViewCompat.getAutoSizeTextType(this) != TextViewCompat.AUTO_SIZE_TEXT_TYPE_NONE
        if (doHack) {
            minTextSize = TextViewCompat.getAutoSizeMinTextSize(this)
            maxTextSize = TextViewCompat.getAutoSizeMaxTextSize(this)
            if (minTextSize <= 0 || maxTextSize <= minTextSize) {
                if (BuildConfig.DEBUG)
                    throw  AssertionError("fix FixAutoSizeTextView or child class layout")
                doHack = false
            } else {
                granularity = TextViewCompat.getAutoSizeStepGranularity(this)
                if (granularity < 0)
                    granularity = 1
                TextViewCompat.setAutoSizeTextTypeWithDefaults(this, TextViewCompat.AUTO_SIZE_TEXT_TYPE_NONE)
                setTextSize(TypedValue.COMPLEX_UNIT_PX, maxTextSize.toFloat())
                if (measuredWidth > 0) {
                    measure(
                        MeasureSpec.makeMeasureSpec(0, MeasureSpec.EXACTLY),
                        MeasureSpec.makeMeasureSpec(0, MeasureSpec.EXACTLY)
                    )
                    right = left
                    bottom = top
                    requestLayout()
                }
            }
        }
        super.setText(text, type)
        if (doHack)
            TextViewCompat.setAutoSizeTextTypeUniformWithConfiguration(this, minTextSize, maxTextSize, granularity, TypedValue.COMPLEX_UNIT_PX);
    }
}
