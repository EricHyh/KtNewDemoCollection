package com.example.jni_test.model.wrapper

import com.example.jni_test.model.IItemIcon
import com.example.jni_test.model.IItemIconVector
import com.example.jni_test.model.ITestItem
import com.example.jni_test.model.StringVector


/**
 * 数据接口
 *
 * @author eriche 2024/12/20
 */
abstract class TestItem : ITestItem() {
    companion object {
        private const val TAG = "ItemTest1"
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as TestItem

        if (id != other.id) return false
        if (title != other.title) return false
        if (envelopePic != other.envelopePic) return false
        if (desc != other.desc) return false
        if (niceDate != other.niceDate) return false
        if (author != other.author) return false
        if (tags != other.tags) return false
        if (icons != other.icons) return false

        return true
    }

    override fun hashCode(): Int {
        return id.hashCode()
    }
}


class ItemIconWithCount(
    private val original: IItemIcon,
    private val count: Int
) : IItemIcon() {

    override fun getName(): String {
        (0 until count).forEach { _ ->
            original.name
        }
        return original.name
    }

    override fun getIcon(): String {
        (0 until count).forEach { _ ->
            original.icon
        }
        return original.icon
    }
}

class TestItemWithCount(
    private val original: ITestItem,
    private val count: Int
) : TestItem() {

    override fun getId(): String {
        (0 until count).forEach { _ ->
            original.id
        }
        return original.id
    }

    override fun getTitle(): String {
        (0 until count).forEach { _ ->
            original.title
        }
        return original.title
    }

    override fun getEnvelopePic(): String {
        (0 until count).forEach { _ ->
            original.envelopePic
        }
        return original.envelopePic
    }

    override fun getDesc(): String {
        (0 until count).forEach { _ ->
            original.desc
        }
        return original.desc
    }

    override fun getNiceDate(): String {
        (0 until count).forEach { _ ->
            original.niceDate
        }
        return original.niceDate
    }

    override fun getAuthor(): String {
        (0 until count).forEach { _ ->
            original.author
        }
        return original.author
    }

    override fun getTags(): StringVector {
        (0 until count).forEach { _ ->
            original.tags
        }
        return original.tags
    }

    override fun getIcons(): IItemIconVector {
        (0 until count).forEach { _ ->
            original.icons
        }
        return original.icons
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as TestItemWithCount

        if (original != other.original) return false
        if (count != other.count) return false

        return true
    }

    override fun hashCode(): Int {
        var result = original.hashCode()
        result = 31 * result + count
        return result
    }
}


class NativeTestItem(private val index: Int) : TestItem() {


    override fun getId(): String {
        return index.toString()
    }

    override fun getTitle(): String {
        return "这是第${index}条数据的标题"
    }

    override fun getEnvelopePic(): String {
        return "https://www.wanandroid.com/resources/image/pc/default_project_img.jpg"
    }

    override fun getDesc(): String {
        return "这是第${index}条数据的描述，这是第${index}条数据的描述，这是第${index}条数据的描述。"
    }

    override fun getNiceDate(): String {
        return "这是第${index}条数据的日期"
    }

    override fun getAuthor(): String {
        return "这是第${index}条数据的作者"
    }

    private val _tags: StringVector = (0 until 40).mapTo(StringVector()) { "这是标签-${it}" }

    override fun getTags(): StringVector {
        return _tags
    }

    private val _icons: IItemIconVector = IItemIconVector().apply {
        addAll(
            listOf(
                NativeItemIcon(
                    "WanAndroid基础-$index",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"
                ),
                NativeItemIcon(
                    "Gradle Plugin-$index",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"
                ),
                NativeItemIcon(
                    "Material Design-$index",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"
                ),
                NativeItemIcon(
                    "MVI-Dispatcher-$index",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"
                ),
                NativeItemIcon(
                    "出行防疫App-$index",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"
                ),
                NativeItemIcon(
                    "北京公交-$index",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"
                ),
                NativeItemIcon(
                    "wechat_flutter-$index",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"
                ),
                NativeItemIcon(
                    "WanAndroid-$index",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"
                ),
                NativeItemIcon(
                    "Piko-$index",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"
                ),
                NativeItemIcon(
                    "Android组件化-$index",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"
                ),

                NativeItemIcon(
                    "WanAndroid基础-$index",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"
                ),
                NativeItemIcon(
                    "Gradle Plugin-$index",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"
                ),
                NativeItemIcon(
                    "Material Design-$index",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"
                ),
                NativeItemIcon(
                    "MVI-Dispatcher-$index",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"
                ),
                NativeItemIcon(
                    "出行防疫App-$index",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"
                ),
                NativeItemIcon(
                    "北京公交-$index",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"
                ),
                NativeItemIcon(
                    "wechat_flutter-$index",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"
                ),
                NativeItemIcon(
                    "WanAndroid-$index",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"
                ),
                NativeItemIcon(
                    "Piko-$index",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"
                ),
                NativeItemIcon(
                    "Android组件化-$index",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"
                ),

                NativeItemIcon(
                    "WanAndroid基础-$index",
                    "https://www.wanandroid.com/blogimgs/6888e512-12cb-4443-8032-026d3cfb5d5d.png"
                ),
                NativeItemIcon(
                    "Gradle Plugin-$index",
                    "https://www.wanandroid.com/blogimgs/cdf0b3a3-a1bb-4d02-8485-756c7d351194.png"
                ),
                NativeItemIcon(
                    "Material Design-$index",
                    "https://wanandroid.com/blogimgs/e1123cd4-d156-4378-85b3-51c10c838911.png"
                ),
                NativeItemIcon(
                    "MVI-Dispatcher-$index",
                    "https://wanandroid.com/blogimgs/a580b742-6ccb-46cc-abf5-ba19505ba2d5.png"
                ),
                NativeItemIcon(
                    "出行防疫App-$index",
                    "https://www.wanandroid.com/blogimgs/30af673f-f3b3-47e3-82de-8919159c534b.png"
                ),
                NativeItemIcon(
                    "北京公交-$index",
                    "https://www.wanandroid.com/blogimgs/fef2efaa-5581-4e8c-8cd1-05d5898f79db.png"
                ),
                NativeItemIcon(
                    "wechat_flutter-$index",
                    "https://www.wanandroid.com/blogimgs/8f49deef-c65e-4d3c-8675-48a5e92c07f2.png"
                ),
                NativeItemIcon(
                    "WanAndroid-$index",
                    "https://www.wanandroid.com/blogimgs/d7bbe689-7bab-4db4-938f-24d5e4854302.png"
                ),
                NativeItemIcon(
                    "Piko-$index",
                    "https://www.wanandroid.com/blogimgs/2218b5df-46bc-4f5e-b667-888ccc7ee135.png"
                ),
                NativeItemIcon(
                    "Android组件化-$index",
                    "https://www.wanandroid.com/blogimgs/e3ee00d6-3332-4b86-abf1-2a6ff0a78ae6.png"
                ),
            )
        )
    }

    override fun getIcons(): IItemIconVector {
        return _icons
    }
}
