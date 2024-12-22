package com.example.jni_test.model.wrapper

import android.os.Parcelable
import kotlinx.parcelize.Parcelize

/**
 * TODO: Add Description
 *
 * @author eriche 2024/12/20
 */


enum class DataSource {

    NATIVE,

    NATIVE_TO_CPP,

    CPP_TO_NATIVE,

}

@Parcelize
data class JNITabInfo(
    val name: String,
    val dataSource: DataSource,
    val count: Int
) : Parcelable