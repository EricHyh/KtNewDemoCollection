package com.example.jni_test.fragment.adapter

import android.annotation.SuppressLint
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.paging.PagingDataAdapter
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.RecyclerView
import com.example.jni_test.R
import com.example.jni_test.databinding.ItemTest1Binding
import com.example.jni_test.model.ItemTest


class JNITestTabAdapter() :
    PagingDataAdapter<ItemTest, JNITestTabAdapter.ProjectItemHolder>(PROJECT_COMPARATOR) {

    override fun onBindViewHolder(holder: ProjectItemHolder, position: Int) {
        Log.d("ProjectAdapter", "onBindViewHolder -> $position")
        getItem(position)?.let {
            holder.bindDataAndEvent(it)
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ProjectItemHolder {
        val view =
            LayoutInflater.from(parent.context).inflate(R.layout.item_test1, parent, false)
        return ProjectItemHolder(view)
    }

    inner class ProjectItemHolder internal constructor(itemView: View) :
        RecyclerView.ViewHolder(itemView) {

        private val binding: ItemTest1Binding? = DataBindingUtil.bind(itemView)

        fun bindDataAndEvent(testData: ItemTest) {
            binding?.testData = testData
            binding?.root?.setOnClickListener {}
        }
    }

    companion object {

        val PROJECT_COMPARATOR = object : DiffUtil.ItemCallback<ItemTest>() {
            /**
             * areItemsTheSame = true时，执行该函数，判断数据内容是否相同.
             */
            @SuppressLint("DiffUtilEquals")
            override fun areContentsTheSame(oldItem: ItemTest, newItem: ItemTest): Boolean =
                (oldItem == newItem)

            /**
             * 判断是否为同一条数据.
             */
            override fun areItemsTheSame(oldItem: ItemTest, newItem: ItemTest): Boolean =
                oldItem.id == newItem.id

            /**
             * areItemsTheSame = true && areContentsTheSame = false 时，执行该函数，
             * 用于获取新旧数据变动的字段.
             */
            override fun getChangePayload(oldItem: ItemTest, newItem: ItemTest): Any? = null
        }
    }
}