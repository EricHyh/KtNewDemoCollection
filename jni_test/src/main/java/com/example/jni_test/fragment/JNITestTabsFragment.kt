package com.example.jni_test.fragment

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.lifecycle.ViewModelProvider
import androidx.viewpager.widget.ViewPager
import com.example.jni_test.R
import com.example.jni_test.fragment.adapter.JNITestTabsAdapter
import com.example.jni_test.fragment.vm.JNITestTabsViewModel
import com.google.android.material.tabs.TabLayout

class JNITestTabsFragment : CommonBaseFragment() {

    private var tabsViewModel: JNITestTabsViewModel? = null

    private var tabLayout: TabLayout? = null

    private var viewPager: ViewPager? = null


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        tabsViewModel = ViewModelProvider(this)[JNITestTabsViewModel::class.java]
    }

    override fun getContentView(inflater: LayoutInflater, container: ViewGroup?): View {
        return inflater.inflate(R.layout.fragment_tabs, container, false)
    }

    override fun initView(contentView: View) {
        val jniTestTabsAdapter = JNITestTabsAdapter(
            contentView.context,
            childFragmentManager
        )
        viewPager = contentView.findViewById(R.id.view_pager)
        viewPager?.adapter = jniTestTabsAdapter
        viewPager?.offscreenPageLimit = 1

        tabsViewModel?.mutableLiveData?.observe(
            this
        ) { tabs ->
            jniTestTabsAdapter.setProjectData(tabs)
        }
        tabLayout = contentView.findViewById(R.id.tab_layout)
        tabLayout?.setupWithViewPager(viewPager)
    }

    override fun initData() {
        tabsViewModel?.loadData()
    }
}