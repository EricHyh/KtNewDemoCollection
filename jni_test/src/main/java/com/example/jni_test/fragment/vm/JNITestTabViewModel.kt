package com.example.jni_test.fragment.vm

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.paging.*
import com.example.jni_test.model.CPP2NativeItemTest
import com.example.jni_test.model.DataSource
import com.example.jni_test.model.ItemTest
import com.example.jni_test.model.JNITabInfo
import com.example.jni_test.model.Native2CPPItemTest
import com.example.jni_test.model.NativeItemTest
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.withContext


/**
 * TODO: Add Description
 *
 * @author eriche
 * @data 2021/1/13
 */


@ExperimentalPagingApi
class JNITestTabViewModel(
    private val tabInfo: JNITabInfo,
) : ViewModel() {

    private val pager: Pager<Int, ItemTest> =
        Pager(
            config = PagingConfig(10, prefetchDistance = 1, enablePlaceholders = false),
            initialKey = 0,
            remoteMediator = null,
            pagingSourceFactory = {
                JNITestTabPagingSource(tabInfo)
            }
        )

    val items = pager.flow.cachedIn(viewModelScope)

}


class JNITestTabPagingSource(private val tabInfo: JNITabInfo) : PagingSource<Int, ItemTest>() {

    private val dispatcher: CoroutineDispatcher = Dispatchers.IO

    override fun getRefreshKey(state: PagingState<Int, ItemTest>): Int? {
        return state.anchorPosition?.let { anchorPosition ->
            val anchorPage = state.closestPageToPosition(anchorPosition)
            anchorPage?.prevKey?.plus(1) ?: anchorPage?.nextKey?.minus(1)
        }
    }

    override suspend fun load(params: LoadParams<Int>): LoadResult<Int, ItemTest> {
        val pageIndex = params.key ?: 1
        return withContext(dispatcher) {
            delay(100)
            val items = when (tabInfo.dataSource) {
                DataSource.NATIVE -> getNativeList(pageIndex)
                DataSource.NATIVE_TO_CPP -> getNative2CPPList(pageIndex)
                DataSource.CPP_TO_NATIVE -> getCPP2NativeList(pageIndex)
            }
            val prevKey = if (pageIndex <= 1) null else pageIndex - 1
            val nextKey = pageIndex + 1
            LoadResult.Page(
                items,
                prevKey,
                nextKey
            )
        }
    }

    private fun getNativeList(pageIndex: Int): List<ItemTest> {
        val intRange = pageIndex..pageIndex + 50
        return intRange.map { index ->
            NativeItemTest(index)
        }
    }

    private fun getNative2CPPList(pageIndex: Int): List<ItemTest> {
        val intRange = pageIndex..pageIndex + 50
        return intRange.map { index ->
            Native2CPPItemTest(index)
        }
    }

    private fun getCPP2NativeList(pageIndex: Int): List<ItemTest> {
        val intRange = pageIndex..pageIndex + 50
        return intRange.map { index ->
            CPP2NativeItemTest(index)
        }
    }
}