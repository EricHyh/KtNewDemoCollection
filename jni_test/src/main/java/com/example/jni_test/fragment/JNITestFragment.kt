package com.example.jni_test.fragment


import android.graphics.Rect
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.viewModels
import androidx.lifecycle.*
import androidx.paging.ExperimentalPagingApi
import androidx.paging.LoadState
import androidx.recyclerview.widget.ConcatAdapter
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout
import com.example.jni_test.R
import com.example.jni_test.fragment.adapter.JNITestTabAdapter
import com.example.jni_test.fragment.adapter.JNITestTabLoadStateAdapter
import com.example.jni_test.fragment.vm.JNITestTabViewModel
import com.example.jni_test.model.JNITabInfo
import com.example.jni_test.utils.DisplayUtil
import kotlinx.coroutines.flow.*


class JNITestFragment : CommonBaseFragment() {

    private var refreshLayout: SwipeRefreshLayout? = null

    private var recyclerView: RecyclerView? = null

    private val adapter: JNITestTabAdapter = JNITestTabAdapter()

    @ExperimentalPagingApi
    private val viewModel: JNITestTabViewModel by viewModels {
        object : AbstractSavedStateViewModelFactory(this, null) {
            override fun <T : ViewModel> create(
                key: String,
                modelClass: Class<T>,
                handle: SavedStateHandle
            ): T {
                val arguments = arguments!!
                val tabInfo = arguments.getParcelable<JNITabInfo>("JNITabInfo")!!
                @Suppress("UNCHECKED_CAST")
                return JNITestTabViewModel(tabInfo) as T
            }
        }
    }


    override fun getContentView(inflater: LayoutInflater, container: ViewGroup?): View {
        return inflater.inflate(R.layout.fragment_tab, container, false)
    }

    override fun initView(contentView: View) {
        refreshLayout = contentView.findViewById(R.id.swipe_refresh_layout)
        recyclerView = contentView.findViewById(R.id.recycler_view)
        recyclerView?.apply {
            layoutManager = LinearLayoutManager(context, LinearLayoutManager.VERTICAL, false)
            addItemDecoration(object : RecyclerView.ItemDecoration() {
                override fun getItemOffsets(
                    outRect: Rect,
                    view: View,
                    parent: RecyclerView,
                    state: RecyclerView.State
                ) {
                    outRect.bottom = DisplayUtil.dip2px(view.context, 8F)
                }
            })
        }


        val concatAdapter: ConcatAdapter = adapter.withLoadStateHeaderAndFooter(
            header = JNITestTabLoadStateAdapter(adapter),
            footer = JNITestTabLoadStateAdapter(adapter)
        )
        recyclerView?.adapter = concatAdapter

        refreshLayout?.setOnRefreshListener {
            adapter.refresh() //执行刷新操作
        }
        lifecycleScope.launchWhenCreated {
            adapter.loadStateFlow.collectLatest { loadStates ->
                loadStates.refresh  //获取当前刷新状态
                loadStates.prepend  //获取当前加载上一页状态
                loadStates.append   //获取当前加载下一页状态

                //通常来说，如果我们配合 SwipeRefreshLayout 控件实现下拉刷新，只需要添加以下代码即可
                refreshLayout?.isRefreshing = loadStates.refresh is LoadState.Loading
            }
        }
        // FIXME: 2021/5/10  

        lifecycleScope.launchWhenCreated {
            adapter.loadStateFlow
                // Only emit when REFRESH LoadState for RemoteMediator changes.
                .distinctUntilChangedBy { it.refresh }
                // Only react to cases where Remote REFRESH completes i.e., NotLoading.
                .filter { it.refresh is LoadState.NotLoading }
                .collect { recyclerView?.scrollToPosition(0) }
        }
    }

    @ExperimentalPagingApi
    override fun initData() {
        lifecycleScope.launchWhenCreated {
            viewModel.items.collectLatest {
                adapter.submitData(it)
            }
        }
    }
}









