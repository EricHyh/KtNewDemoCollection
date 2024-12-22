package com.example.jni_test.model.wrapper

import com.example.jni_test.model.IItemIcon

abstract class ItemIcon : IItemIcon() {

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as ItemIcon

        if (name != other.name) return false
        if (icon != other.icon) return false

        return true
    }

    override fun hashCode(): Int {
        var result = name.hashCode()
        result = 31 * result + icon.hashCode()
        return result
    }
}

class NativeItemIcon(
    private val name: String,
    private val icon: String
) : ItemIcon() {


    override fun getName(): String {
        return name
    }

    override fun getIcon(): String {
        return icon
    }
}