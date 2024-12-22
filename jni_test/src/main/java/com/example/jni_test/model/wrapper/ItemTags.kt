package com.example.jni_test.model.wrapper


/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
data class ItemTags(
    val index: Int,
    val tags: List<ItemTag>
)


data class ItemTag(
    private val _tag: String,
    private val _color: Int,
    private val count: Int
) {
    val tag: String
        get() {
            (0 until count).forEach { _ ->
                _tag
            }
            return _tag
        }

    val color: Int
        get() {
            (0 until count).forEach { _ ->
                _color
            }
            return _color
        }
}