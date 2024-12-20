package com.example.jni_test.model

/**
 * 数据接口
 *
 * @author eriche 2024/12/20
 */
interface ItemTest {
    companion object {
        private const val TAG = "ItemTest1"
    }

    val id: String

    val title: String

    val envelopePic: String

    val desc: String

    val niceDate: String

    val author: String

}

class NativeItemTest(index: Int) : ItemTest {

    override val id: String = index.toString()

    override val title: String = "这是第${index}条数据的标题"

    override val envelopePic: String =
        "https://www.wanandroid.com/blogimgs/9fc6e10c-b3e8-46bb-928b-05ccd2147335.png"

    override val desc: String =
        "这是第${index}条数据的描述，这是第${index}条数据的描述，这是第${index}条数据的描述。"

    override val niceDate: String = "这是第${index}条数据的日期"

    override val author: String = "这是第${index}条数据的作者"
}

class Native2CPPItemTest(private val index: Int) : ItemTest {

    @Transient
    private var ptr: Long = Native2CPPItemTestJNI.createNative2CPPItemTest(index)

    override val id: String
        get() = Native2CPPItemTestJNI.getId(ptr)
    override val title: String
        get() = Native2CPPItemTestJNI.getTitle(ptr)
    override val envelopePic: String
        get() = Native2CPPItemTestJNI.getEnvelopePic(ptr)
    override val desc: String
        get() = Native2CPPItemTestJNI.getDesc(ptr)
    override val niceDate: String
        get() = Native2CPPItemTestJNI.getNiceDate(ptr)
    override val author: String
        get() = Native2CPPItemTestJNI.getAuthor(ptr)

    protected fun finalize() {
        if (ptr != 0L) return
        Native2CPPItemTestJNI.releaseNative2CPPItemTest(ptr)
        ptr = 0L
    }
}


object Native2CPPItemTestJNI {

    external fun createNative2CPPItemTest(index: Int): Long

    external fun releaseNative2CPPItemTest(ptr: Long)

    external fun getId(ptr: Long): String

    external fun getTitle(ptr: Long): String

    external fun getEnvelopePic(ptr: Long): String

    external fun getDesc(ptr: Long): String

    external fun getNiceDate(ptr: Long): String

    external fun getAuthor(ptr: Long): String

}


class CPP2NativeItemTest(private val index: Int) : ItemTest {

    private val nativeItemTest: NativeItemTest = NativeItemTest(index)

    @Transient
    private var ptr: Long = CPP2NativeItemTestJNI.createCPP2NativeItemTest(index)

    override val id: String
        get() = CPP2NativeItemTestJNI.getId(ptr)
    override val title: String
        get() = CPP2NativeItemTestJNI.getTitle(ptr)
    override val envelopePic: String
        get() = CPP2NativeItemTestJNI.getEnvelopePic(ptr)
    override val desc: String
        get() = CPP2NativeItemTestJNI.getDesc(ptr)
    override val niceDate: String
        get() = CPP2NativeItemTestJNI.getNiceDate(ptr)
    override val author: String
        get() = CPP2NativeItemTestJNI.getAuthor(ptr)

    protected fun finalize() {
        if (ptr != 0L) return
        CPP2NativeItemTestJNI.releaseCPP2NativeItemTest(ptr)
        ptr = 0L
    }

}


object CPP2NativeItemTestJNI {

    external fun createCPP2NativeItemTest(index: Int): Long

    external fun releaseCPP2NativeItemTest(ptr: Long)

    external fun getId(ptr: Long): String

    external fun getTitle(ptr: Long): String

    external fun getEnvelopePic(ptr: Long): String

    external fun getDesc(ptr: Long): String

    external fun getNiceDate(ptr: Long): String

    external fun getAuthor(ptr: Long): String

    private fun _getId(nativeItemTest: NativeItemTest) = nativeItemTest.id
    private fun _getTitle(nativeItemTest: NativeItemTest) = nativeItemTest.title
    private fun _getEnvelopePic(nativeItemTest: NativeItemTest) = nativeItemTest.envelopePic
    private fun _getDes(nativeItemTest: NativeItemTest) = nativeItemTest.desc
    private fun _getNiceDate(nativeItemTest: NativeItemTest) = nativeItemTest.niceDate
    private fun _getAuthor(nativeItemTest: NativeItemTest) = nativeItemTest.author

}