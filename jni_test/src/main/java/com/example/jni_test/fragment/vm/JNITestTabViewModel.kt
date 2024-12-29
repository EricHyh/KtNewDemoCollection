package com.example.jni_test.fragment.vm

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.paging.*
import com.example.jni_test.model.C2NTestItemFactory
import com.example.jni_test.model.N2CTestItem
import com.example.jni_test.model.wrapper.DataSource
import com.example.jni_test.model.wrapper.ItemIconWithCount
import com.example.jni_test.model.wrapper.ItemIcons
import com.example.jni_test.model.wrapper.ItemTag
import com.example.jni_test.model.wrapper.ItemTags
import com.example.jni_test.model.wrapper.JNITabInfo
import com.example.jni_test.model.wrapper.NativeTestItem
import com.example.jni_test.model.wrapper.TestItemDataWrapper
import com.example.jni_test.model.wrapper.TestItemWithCount
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.withContext
import java.util.Random


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

    private val pager: Pager<Int, TestItemDataWrapper> =
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


class JNITestTabPagingSource(private val tabInfo: JNITabInfo) :
    PagingSource<Int, TestItemDataWrapper>() {

    companion object {
        private const val TAG = "JNITestTabViewModel"
    }


    private val dispatcher: CoroutineDispatcher = Dispatchers.IO
    private val random = Random()

    override fun getRefreshKey(state: PagingState<Int, TestItemDataWrapper>): Int? {
        return state.anchorPosition?.let { anchorPosition ->
            val anchorPage = state.closestPageToPosition(anchorPosition)
            anchorPage?.prevKey?.plus(1) ?: anchorPage?.nextKey?.minus(1)
        }
    }

    override suspend fun load(params: LoadParams<Int>): LoadResult<Int, TestItemDataWrapper> {
        val pageIndex = params.key ?: 1
        Log.d(TAG, "load: $pageIndex")
        return withContext(dispatcher) {
            delay(100)
            val items = when (tabInfo.dataSource) {
                DataSource.NATIVE -> getNativeList(pageIndex, tabInfo.count)
                DataSource.NATIVE_TO_CPP -> getNative2CPPList(pageIndex, tabInfo.count)
                DataSource.CPP_TO_NATIVE -> getCPP2NativeList(pageIndex, tabInfo.count)
            }
            val prevKey = if (pageIndex <= 1) null else pageIndex - 50
            val nextKey = pageIndex + 50
            LoadResult.Page(
                items,
                prevKey,
                nextKey
            )
        }
    }

    private fun getNativeList(pageIndex: Int, count: Int): List<TestItemDataWrapper> {
        val intRange = pageIndex until pageIndex + 50
        return intRange.map { index ->
            TestItemWithCount(NativeTestItem(index), count)
        }.flatMapIndexed { index, item ->
            buildList {
                buildList(this, item, this@JNITestTabPagingSource, index, count)
            }
        }
    }

    private fun getNative2CPPList(pageIndex: Int, count: Int): List<TestItemDataWrapper> {
        val intRange = pageIndex..pageIndex + 50
        return intRange.map { index ->
            TestItemWithCount(N2CTestItem(index), count)
        }.flatMapIndexed { index, item ->
            buildList {
                buildList(this, item, this@JNITestTabPagingSource, index, count)
            }
        }
    }

    private fun getCPP2NativeList(pageIndex: Int, count: Int): List<TestItemDataWrapper> {
        val intRange = pageIndex..pageIndex + 50
        return intRange.map { index ->
            TestItemWithCount(C2NTestItemFactory.create(index), count)
        }.flatMapIndexed { index, item ->
            buildList {
                buildList(this, item, this@JNITestTabPagingSource, index, count)
            }
        }
    }

    private fun buildList(
        testItemDataWrappers: MutableList<TestItemDataWrapper>,
        item: TestItemWithCount,
        jniTestTabPagingSource: JNITestTabPagingSource,
        index: Int,
        count: Int
    ) {
        testItemDataWrappers += TestItemDataWrapper(
            0,
            item
        )

//        val originalIcons = item.icons
//        jniTestTabPagingSource.splitList(originalIcons, 10).forEach { icons ->
//            testItemDataWrappers += TestItemDataWrapper(
//                1, ItemIcons(
//                    index, icons.map { ItemIconWithCount(it, count) }
//                )
//            )
//        }

//        testItemDataWrappers += TestItemDataWrapper(
//            2, ItemTags(
//                index, item.tags.map {
//                    ItemTag(
//                        it,
//                        Color.argb(
//                            255,
//                            random.nextInt(256),
//                            random.nextInt(256),
//                            random.nextInt(256)
//                        ),
//                        count
//                    )
//                }
//            ))
    }

    private fun <T> splitList(
        messagesList: List<T>,
        groupSize: Int
    ): List<List<T>> {
        val length = messagesList.size
        // 计算可以分成多少组
        val num = (length + groupSize - 1) / groupSize
        val newList: MutableList<List<T>> = ArrayList(num)
        for (i in 0 until num) {
            // 开始位置
            val fromIndex = i * groupSize
            // 结束位置
            val toIndex = if ((i + 1) * groupSize < length) (i + 1) * groupSize else length
            newList.add(messagesList.subList(fromIndex, toIndex))
        }
        return newList
    }
}