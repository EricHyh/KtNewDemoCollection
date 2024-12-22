package com.example.jni_test.fragment.ui

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import com.example.jni_test.R
import com.example.jni_test.databinding.ItemIconBinding
import com.example.jni_test.model.IItemIcon
import com.example.jni_test.widget.horizontal.GridHolder
import com.example.jni_test.widget.horizontal.IGrid

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
class ItemIconGrid(
    private val index: Int,
    private val icon: IItemIcon
) : IGrid<ItemIconGridHolder> {

    override val gridId: Int = index
    override val gridViewType: Int
        get() = 2

    override fun getGridHolderFactory(): (parent: ViewGroup) -> ItemIconGridHolder {
        return {
            val view = LayoutInflater.from(it.context).inflate(R.layout.item_icon, it, false)
            ItemIconGridHolder(view)
        }
    }

    override fun areContentsTheSame(other: IGrid<*>): Boolean {
        if (other !is ItemIconGrid) return false
        return icon.name == other.icon.name && icon.icon == other.icon.icon
    }

    override fun render(holder: ItemIconGridHolder) {
        holder.bind(icon)
    }
}


class ItemIconGridHolder(view: View) : GridHolder(view) {

    private val binding: ItemIconBinding? = DataBindingUtil.bind(view)

    fun bind(icon: IItemIcon) {
        binding?.itemIcon = icon
    }
}