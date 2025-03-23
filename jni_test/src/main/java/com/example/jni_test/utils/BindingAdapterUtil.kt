package com.example.jni_test.utils

import android.widget.ImageView
import androidx.databinding.BindingAdapter
import com.bumptech.glide.Glide
import com.bumptech.glide.load.engine.DiskCacheStrategy
import com.example.jni_test.R


/**
 * TODO
 *
 * @author eriche 2024/12/22
 */
object BindingAdapterUtil {

    @JvmStatic
    @BindingAdapter("app:imageUrl")
    fun setImageUrl(imageView: ImageView, url: String?) {
        Glide.with(imageView.context)
            .load(url)
            .centerCrop()
            .diskCacheStrategy(DiskCacheStrategy.ALL)
            .placeholder(R.drawable.img_default)
            .error(R.drawable.img_default)
            .into(imageView)
    }

    //scrollIcons
//    @JvmStatic
//    @BindingAdapter("app:scrollIcons")
//    fun setScrollIcons(layout: RecyclerViewScrollLayout, icons: List<IItemIcon>) {
//        layout.setGrid(
//            ItemIconTitleGrid("${icons.size}"),
//            icons.mapIndexed { index, itemIcon ->
//                ItemIconGrid(index, itemIcon)
//            }
//        )
//    }
}