package com.example.jni_test.fragment.adapter

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.appcompat.widget.AppCompatTextView
import androidx.databinding.DataBindingUtil
import androidx.paging.PagingDataAdapter
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import com.example.jni_test.R
import com.example.jni_test.databinding.ItemTest1Binding
import com.example.jni_test.fragment.ui.ItemIconGrid
import com.example.jni_test.fragment.ui.ItemIconTitleGrid
import com.example.jni_test.model.wrapper.ItemIcons
import com.example.jni_test.model.wrapper.ItemTag
import com.example.jni_test.model.wrapper.ItemTags
import com.example.jni_test.model.wrapper.TestItemDataWrapper
import com.example.jni_test.utils.DisplayUtil
import com.example.jni_test.widget.horizontal.HorizontalScrollSyncHelper
import com.example.jni_test.widget.horizontal.RecyclerViewScrollLayout
import com.hyh.jnitest.test.item.ITestItem


class JNITestTabAdapter() :
    PagingDataAdapter<TestItemDataWrapper, RecyclerView.ViewHolder>(PROJECT_COMPARATOR) {

    private val horizontalScrollSyncHelper = HorizontalScrollSyncHelper()

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val item = getItem(position) ?: return
        when (item.type) {
            0 -> {
                (holder as ProjectItemHolder).bindDataAndEvent(item.data as ITestItem)
            }

            1 -> {
                (holder as IconsItemHolder).bindDataAndEvent(item.data as ItemIcons)
            }

            2 -> {
                (holder as TagsItemHolder).bindDataAndEvent(item.data as ItemTags)
            }

            else -> {}
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        when (viewType) {
            0 -> {
                val view =
                    LayoutInflater.from(parent.context).inflate(R.layout.item_test1, parent, false)
                return ProjectItemHolder(view)
            }

            1 -> {
                return IconsItemHolder(RecyclerViewScrollLayout(parent.context).also {
                    it.fixedMinWidth = DisplayUtil.dip2px(parent.context, 100f)
                    it.layoutParams = ViewGroup.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        ViewGroup.LayoutParams.WRAP_CONTENT
                    )
                    it.setPadding(
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                    )
                })
            }

            2 -> {
                return TagsItemHolder(RecyclerView(parent.context).also {
                    it.layoutParams = ViewGroup.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        ViewGroup.LayoutParams.WRAP_CONTENT
                    )
                    it.setPadding(
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                        DisplayUtil.dip2px(parent.context, 8f),
                    )
                })
            }

            else -> {
                return object : RecyclerView.ViewHolder(View(parent.context)) {}
            }
        }

    }

    override fun getItemViewType(position: Int): Int {
        val item = getItem(position) ?: return super.getItemViewType(position)
        return item.type
    }

    inner class ProjectItemHolder internal constructor(itemView: View) :
        RecyclerView.ViewHolder(itemView) {

        private val binding: ItemTest1Binding? = DataBindingUtil.bind(itemView)

        fun bindDataAndEvent(testData: ITestItem) {
            binding?.testData = testData
            binding?.root?.setOnClickListener {}
        }
    }

    inner class IconsItemHolder constructor(itemView: View) : RecyclerView.ViewHolder(itemView) {

        private val scrollIconsLayout = itemView as RecyclerViewScrollLayout

        fun bindDataAndEvent(testData: ItemIcons) {
            scrollIconsLayout.bindHorizontalScrollSyncHelper(horizontalScrollSyncHelper)
            scrollIconsLayout.setGrid(
                ItemIconTitleGrid(
                    "图标个数：${testData.icons.size}"
                ),
                testData.icons.mapIndexed { index, itemIcon ->
                    ItemIconGrid(index, itemIcon)
                })
        }
    }

    class TagsItemHolder constructor(itemView: View) : RecyclerView.ViewHolder(itemView) {


        private val adapter: ListAdapter<ItemTag, TagHolder> =
            object : ListAdapter<ItemTag, TagHolder>(TAG_COMPARATOR) {

                override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TagHolder {
                    val textView = AppCompatTextView(parent.context).also {
                        it.layoutParams =
                            ViewGroup.MarginLayoutParams(
                                ViewGroup.LayoutParams.WRAP_CONTENT,
                                ViewGroup.LayoutParams.WRAP_CONTENT
                            ).apply {
                                rightMargin = DisplayUtil.dip2px(parent.context, 4f)
                                topMargin = DisplayUtil.dip2px(parent.context, 4f)
                            }
                        it.setPadding(
                            DisplayUtil.dip2px(parent.context, 8f),
                            DisplayUtil.dip2px(parent.context, 8f),
                            DisplayUtil.dip2px(parent.context, 8f),
                            DisplayUtil.dip2px(parent.context, 8f),
                        )
                        it.textSize = 14F
                    }
                    return TagHolder(textView)
                }

                override fun onBindViewHolder(holder: TagHolder, position: Int) {
                    val tag = currentList[position]
                    holder.textView.setTextColor(tag.color)
                    holder.textView.setBackgroundColor(DisplayUtil.getInverseColor(tag.color))
                    holder.textView.text = tag.tag
                }
            }

        init {
            (itemView as RecyclerView).also {
                it.layoutManager = StaggeredGridLayoutManager(2, StaggeredGridLayoutManager.HORIZONTAL)
                it.adapter = adapter
            }
        }

        fun bindDataAndEvent(testData: ItemTags) {
            adapter.submitList(testData.tags)
        }


        class TagHolder constructor(val textView: TextView) : RecyclerView.ViewHolder(textView)

    }

    companion object {

        val PROJECT_COMPARATOR = object : DiffUtil.ItemCallback<TestItemDataWrapper>() {
            /**
             * areItemsTheSame = true时，执行该函数，判断数据内容是否相同.
             */
            @SuppressLint("DiffUtilEquals")
            override fun areContentsTheSame(oldItem: TestItemDataWrapper, newItem: TestItemDataWrapper): Boolean =
                (oldItem == newItem)

            /**
             * 判断是否为同一条数据.
             */
            override fun areItemsTheSame(oldItem: TestItemDataWrapper, newItem: TestItemDataWrapper): Boolean {
                if (oldItem.type != newItem.type) return false
                return when (oldItem.type) {
                    0 -> {
                        val oldData = oldItem.data as ITestItem
                        val newData = newItem.data as ITestItem
                        oldData.id == newData.id
                    }

                    1 -> {
                        val oldData = oldItem.data as ItemIcons
                        val newData = newItem.data as ItemIcons
                        oldData.index == newData.index
                    }

                    2 -> {
                        val oldData = oldItem.data as ItemTags
                        val newData = newItem.data as ItemTags
                        oldData.index == newData.index
                    }

                    else -> false
                }
            }


            /**
             * areItemsTheSame = true && areContentsTheSame = false 时，执行该函数，
             * 用于获取新旧数据变动的字段.
             */
            override fun getChangePayload(oldItem: TestItemDataWrapper, newItem: TestItemDataWrapper): Any? = null
        }


        val TAG_COMPARATOR = object : DiffUtil.ItemCallback<ItemTag>() {
            /**
             * areItemsTheSame = true时，执行该函数，判断数据内容是否相同.
             */
            @SuppressLint("DiffUtilEquals")
            override fun areContentsTheSame(oldItem: ItemTag, newItem: ItemTag): Boolean =
                (oldItem == newItem)

            /**
             * 判断是否为同一条数据.
             */
            override fun areItemsTheSame(oldItem: ItemTag, newItem: ItemTag): Boolean {
                return (oldItem == newItem)
            }

            /**
             * areItemsTheSame = true && areContentsTheSame = false 时，执行该函数，
             * 用于获取新旧数据变动的字段.
             */
            override fun getChangePayload(oldItem: ItemTag, newItem: ItemTag): Any? = null
        }
    }
}