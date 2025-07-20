package com.hyh.jnitest.basic.infrastructure.test

import androidx.lifecycle.LiveData
import androidx.lifecycle.Observer
import com.hyh.jnitest.test.field.ILiveData
import com.hyh.jnitest.test.field.IntLiveData
import com.hyh.jnitest.test.field.IntLiveDataObserver
import com.hyh.jnitest.test.field.StringLiveData
import com.hyh.jnitest.test.field.StringLiveDataObserver
import kotlin.reflect.KClass

/**
 * TODO
 *
 * @author eriche 2025/7/20
 */
object FlowExt {


    fun test() {
//        IntLiveData
    }


//    inline fun <reified T> StateFlow<T>.toFINLiveData() {
//        this.asLiveData()
//        StateFlow<Int>{}
//        MutableLiveData<Int>().asFlow()
//        when (T::class) {
//            Int::class -> {
//
//            }
//        }
//    }
}


class ILiveDataWrapper<T : Any>(
    private val valueType: KClass<T>,
    private val liveData: ILiveData
) : LiveData<T>() {

    companion object {

        private fun <T : Any> getLiveDataValue(
            type: KClass<T>,
            liveData: ILiveData
        ): T {
            return when (type) {
                Int::class -> {
                    (liveData as IntLiveData).GetValue()
                }

                String::class -> {
                    (liveData as StringLiveData).GetValue()
                }

                else -> {
                    (liveData as IntLiveData).GetValue()
                }
            } as T
        }

        private fun <T : Any> AddObserver(
            type: KClass<T>,
            liveData: ILiveData,
            observer: Observer<T>
        ): Any {
            when (type) {
                Int::class -> {
                    val intLiveDataObserver = object : IntLiveDataObserver() {
                        override fun onCall(value: Int) {
                            observer.onChanged(value as T)
                        }
                    }
                    (liveData as IntLiveData).AddObserver(intLiveDataObserver, false)
                    return intLiveDataObserver
                }

                String::class -> {
                    val stringLiveDataObserver = object : StringLiveDataObserver() {
                        override fun onCall(value: String) {
                            observer.onChanged(value as T)
                        }
                    }
                    (liveData as StringLiveData).AddObserver(stringLiveDataObserver, false)
                    return stringLiveDataObserver
                }

                else -> {
                    (liveData as IntLiveData).GetValue()
                    return Any()
                }
            }
        }

        private fun <T : Any> RemoveObserver(
            type: KClass<T>,
            liveData: ILiveData,
            observer: Any
        ) {
            when (type) {
                Int::class -> {
                    (liveData as IntLiveData).RemoveObserver(observer as IntLiveDataObserver)
                }

                String::class -> {
                    (liveData as StringLiveData).GetValue()
                }

                else -> {

                }
            }
        }
    }

    init {

    }


}


//inline fun <reified T : Any> ILiveData.asNonNullStateFlow(): StateFlow<T> {
////    val stateFlow = MutableStateFlow(value!!)
////    return StateFlowWrapper(this, stateFlow)
//}
//
//
//
//@OptIn(DelicateCoroutinesApi::class)
//fun <T> LiveData<T>.asFlow(): Flow<T> = flow {
//    val channel = Channel<T>(Channel.CONFLATED)
//    val observer = Observer<T> {
//        channel.trySend(it)
//    }
//    withContext(Dispatchers.Main.immediate) {
//        observeForever(observer)
//    }
//    try {
//        for (value in channel) {
//            emit(value)
//        }
//    } finally {
//        GlobalScope.launch(Dispatchers.Main.immediate) {
//            removeObserver(observer)
//        }
//    }
//}
//
//
//fun <T : Any> LiveData<T>.asNonNullStateFlow(): StateFlow<T> {
//    val stateFlow = MutableStateFlow(value!!)
//    return StateFlowWrapper(this, stateFlow)
//}
//
//fun <T : Any> LiveData<T?>.asNullableStateFlow(): StateFlow<T?> {
//    val stateFlow = MutableStateFlow(value)
//    return StateFlowWrapper(this, stateFlow)
//}
//
//class StateFlowWrapper<T>(
//    private val liveData: LiveData<T>,
//    private val real: MutableStateFlow<T>,
//) : StateFlow<T> by real {
//
//    private val scope = CoroutineScope(Dispatchers.Main.immediate)
//
//    private val observer = Observer<T> {
//        real.value = it
//    }
//
//    init {
//        scope.launch {
//            real.subscriptionCount.collectLatest { count ->
//                if (count > 0) {
//                    liveData.observeForever(observer)
//                } else {
//                    liveData.removeObserver(observer)
//                }
//            }
//        }
//    }
//}