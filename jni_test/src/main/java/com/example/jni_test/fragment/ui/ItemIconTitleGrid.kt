package com.example.jni_test.fragment.ui

import android.annotation.SuppressLint
import android.graphics.Color
import android.util.TypedValue
import android.view.Gravity
import android.view.ViewGroup
import android.view.ViewGroup.MarginLayoutParams
import android.widget.TextView
import androidx.appcompat.widget.AppCompatTextView
import androidx.core.widget.TextViewCompat
import com.example.jni_test.utils.DisplayUtil
import com.example.jni_test.widget.horizontal.GridHolder
import com.example.jni_test.widget.horizontal.IGrid

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
class ItemIconTitleGrid(
    private val title: String,
) : IGrid<ItemIconTitleGridHolder> {

    override val gridId: Int = -1
    override val gridViewType: Int
        get() = 1

    override fun getGridHolderFactory(): (parent: ViewGroup) -> ItemIconTitleGridHolder {
        return {
            val textView = AppCompatTextView(it.context).apply {
                setTextSize(TypedValue.COMPLEX_UNIT_SP, 16.0F)
                maxLines = 1
                TextViewCompat.setAutoSizeTextTypeUniformWithConfiguration(
                    this,
                    8,
                    16,
                    1,
                    TypedValue.COMPLEX_UNIT_SP
                )
                gravity = Gravity.LEFT or Gravity.CENTER_VERTICAL
                setTextColor(Color.BLACK)
                setPadding(
                    DisplayUtil.dip2px(context, 8F),
                    0,
                    DisplayUtil.dip2px(context, 8F),
                    0
                )
                layoutParams = MarginLayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT
                )
            }
            ItemIconTitleGridHolder(textView)
        }
    }

    override fun areContentsTheSame(other: IGrid<*>): Boolean {
        if (other !is ItemIconTitleGrid) return false
        return title == other.title
    }

    override fun render(holder: ItemIconTitleGridHolder) {
        holder.bind(title)
    }
}


class ItemIconTitleGridHolder(private val textView: TextView) : GridHolder(textView) {

    @SuppressLint("SetTextI18n")
    fun bind(title: String) {
        textView.text = title
    }
}