package com.example.jni_test.fragment.adapter

import android.content.Context
import android.os.Bundle
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentStatePagerAdapter
import com.example.jni_test.fragment.JNITestFragment
import com.example.jni_test.model.JNITabInfo

class JNITestTabsAdapter(private val context: Context, fm: FragmentManager) :
    FragmentStatePagerAdapter(fm) {

    private var tabs: List<JNITabInfo>? = null
    fun setProjectData(tabs: List<JNITabInfo>?) {
        this.tabs = tabs
        notifyDataSetChanged()
    }

    override fun getItem(i: Int): Fragment {
        val tabInfo = tabs!![i]
        val bundle = Bundle()
        bundle.putParcelable("JNITabInfo", tabInfo)
        return Fragment.instantiate(
            context,
            JNITestFragment::class.java.getName(), bundle
        )
    }

    override fun getCount(): Int {
        return tabs?.size ?: 0
    }

    override fun getPageTitle(position: Int): CharSequence? {
        return tabs?.get(position)?.name
    }
}