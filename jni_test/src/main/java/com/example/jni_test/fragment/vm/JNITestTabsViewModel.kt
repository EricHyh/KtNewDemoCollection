package com.example.jni_test.fragment.vm

import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import com.example.jni_test.model.DataSource
import com.example.jni_test.model.JNITabInfo

class JNITestTabsViewModel : ViewModel() {

    val mutableLiveData: MutableLiveData<List<JNITabInfo>> = MutableLiveData()

    fun loadData() {
        mutableLiveData.postValue(
            listOf(
                JNITabInfo("原生", DataSource.NATIVE),
                JNITabInfo("原生调用C++", DataSource.NATIVE_TO_CPP),
                JNITabInfo("C++调用原生", DataSource.CPP_TO_NATIVE),
            )
        )
    }
}