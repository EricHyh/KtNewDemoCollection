package com.hyh.feeds

import android.util.Log
import kotlinx.coroutines.flow.Flow
import java.lang.reflect.InvocationHandler
import java.lang.reflect.Method
import java.lang.reflect.Proxy
import java.util.*

/**
 * TODO: Add Description
 *
 * 1.可读性
 * 2.拓展性
 * 3.可用性
 * 4.约束性
 * <br>
 *
 *
 * @author eriche
 * @data 2020/12/1
 */
interface EventChannelFactory {
}

interface ClickEventFactory<T> : EventChannelFactory {
    fun getClickEventChannel(): IEventChannel<T>
}

interface DeleteEventFactory<T> : EventChannelFactory {
    fun getDeleteEventChannel(): IEventChannel<T>
}

interface ClickAndDeleteEventFactory<T1, T2> : ClickEventFactory<T1>, DeleteEventFactory<T2>


inline fun <reified T : EventChannelFactory> EventChannelFactory.asTyped(): T? {
    return if (this is T) this else null
}

inline fun <reified T : EventChannelFactory> createEventChannelFactory(): T {
    return Proxy.newProxyInstance(
        EventChannelFactory::class.java.classLoader,
        arrayOf(T::class.java),
        null
    ) as T
}

interface IEventChannel<T> {

    fun send(t: T)

    fun asFlow(): Flow<T>

}

class EventData(val data: Any? = null) {
    inline fun <reified T> getTypedData(): T? {
        return if (data is T) {
            data as T
        } else {
            null
        }
    }
}

class EventInvocationHandler : InvocationHandler {

    companion object {
        //用于保证返回值为基础数据类型时，不返回null
        private val PRIMITIVE_DEFAULT_VALUE: MutableMap<Class<*>?, Any> = HashMap(8)

        init {
            PRIMITIVE_DEFAULT_VALUE[Byte::class.javaPrimitiveType] = 0.toByte()
            PRIMITIVE_DEFAULT_VALUE[Short::class.javaPrimitiveType] = 0.toShort()
            PRIMITIVE_DEFAULT_VALUE[Int::class.javaPrimitiveType] = 0
            PRIMITIVE_DEFAULT_VALUE[Long::class.javaPrimitiveType] = 0L
            PRIMITIVE_DEFAULT_VALUE[Float::class.javaPrimitiveType] = 0.0f
            PRIMITIVE_DEFAULT_VALUE[Double::class.javaPrimitiveType] = 0.0
            PRIMITIVE_DEFAULT_VALUE[Boolean::class.javaPrimitiveType] = false
            PRIMITIVE_DEFAULT_VALUE[Char::class.javaPrimitiveType] = '\u0000'
        }
    }

    override fun invoke(proxy: Any, method: Method, args: Array<out Any>): Any? {
        val returnType = method.returnType
        val genericReturnType = method.genericReturnType

        return PRIMITIVE_DEFAULT_VALUE[returnType]
    }
}