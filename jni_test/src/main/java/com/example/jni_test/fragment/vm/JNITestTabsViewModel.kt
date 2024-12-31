package com.example.jni_test.fragment.vm

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.jni_test.model.wrapper.DataSource
import com.example.jni_test.model.wrapper.JNITabInfo

class JNITestTabsViewModel(private val dataSource: DataSource) : ViewModel() {

    val mutableLiveData: MutableLiveData<List<JNITabInfo>> = MutableLiveData()

    fun loadData() {
        mutableLiveData.postValue(
            listOf(
                JNITabInfo("1倍", dataSource, 0),
                JNITabInfo("10倍", dataSource, 10),
                JNITabInfo("100倍", dataSource, 100),
                JNITabInfo("200倍", dataSource, 200),
                JNITabInfo("500倍", dataSource, 500),
                JNITabInfo("1000倍", dataSource, 1000),
            )
        )
    }
}