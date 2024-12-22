package com.example.jni_test.model.wrapper

/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
data class TestItemDataWrapper(
    val type: Int,
    val data: Any
) {

    var parent: Any? = null

}