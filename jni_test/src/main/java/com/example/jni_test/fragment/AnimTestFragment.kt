package com.example.jni_test.fragment

import android.animation.ValueAnimator
import android.animation.ValueAnimator.REVERSE
import android.content.Context
import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.Path
import android.graphics.PathMeasure
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.ViewGroup.LayoutParams
import android.view.animation.AccelerateDecelerateInterpolator
import android.widget.RadioGroup
import androidx.core.animation.doOnEnd
import androidx.core.animation.doOnStart
import com.example.jni_test.R
import com.example.jni_test.model.wrapper.NativeTestColor
import com.example.jni_test.model.wrapper.TestColorWrapper
import com.example.jni_test.utils.DisplayUtil
import com.hyh.jnitest.test.color.ITestColor
import com.hyh.jnitest.test.color.N2CTestColor
import com.hyh.jnitest.test.color.TestColorFactory
import java.util.Random
import kotlin.math.min

/**
 * TODO
 *
 * @author eriche 2024/12/29
 */
class AnimTestFragment() : CommonBaseFragment() {

    private var fragmentContent: ViewGroup? = null
    private var animTestView1: AnimTestView? = null
    private var animTestView2: AnimTestView? = null

    private var type = 0
    private var count: Int = 0

    override fun getContentView(inflater: LayoutInflater, container: ViewGroup?): View {
        return inflater.inflate(R.layout.fragment_anim_test, container, false)
    }

    override fun initView(contentView: View) {
        fragmentContent = contentView.findViewById<ViewGroup>(R.id.fragment_content)
        animTestView1 = AnimTestView(contentView.context)
        animTestView2 = AnimTestView(contentView.context)
        contentView.findViewById<RadioGroup>(R.id.rg_type).setOnCheckedChangeListener { group, checkedId ->
            when (checkedId) {
                R.id.rb_type_native -> type = 0
                R.id.rb_type_native2cpp -> type = 1
                R.id.rb_type_cpp2native -> type = 2
                else -> 0
            }
            startAnim()
        }
        contentView.findViewById<View>(R.id.btn_stop).setOnClickListener {
            animTestView1?.stopAnim()
            animTestView2?.stopAnim()
        }
        val views = listOf<View>(
            contentView.findViewById<View>(R.id.btn_1),
            contentView.findViewById<View>(R.id.btn_10),
            contentView.findViewById<View>(R.id.btn_100),
            contentView.findViewById<View>(R.id.btn_200),
            contentView.findViewById<View>(R.id.btn_500),
            contentView.findViewById<View>(R.id.btn_1000),
        )

        var selected: View = views.first()
        selected.isSelected = true

        views.forEach { view ->
            view.setOnClickListener {
                if (selected != it) {
                    selected.isSelected = false
                }
                selected = it
                it.isSelected = true
                count = it.tag.toString().toInt()
                startAnim()
            }
        }
    }

    override fun initData() {}

    private fun startAnim() {
        animTestView1?.setTestColorWrapper(TestColorWrapper(getTestColor(), count))
        animTestView1?.startAnim(
            fragmentContent, false,
        )
        animTestView2?.startAnim(
            fragmentContent, true,
        )
    }

    private fun getTestColor(): ITestColor {
        return when (type) {
            0 -> NativeTestColor()
            1 -> N2CTestColor()
            2 -> TestColorFactory.create()
            else -> NativeTestColor()
        }
    }
}


class AnimTestView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : View(context, attrs, defStyleAttr) {


    private val paint = Paint()
    private val random = Random()
    private var animator: ValueAnimator? = null
    private var testColorWrapper: TestColorWrapper? = null

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        paint.color = getColor()
        canvas.drawCircle(
            width / 2.0f,
            height / 2.0f,
            min(width, height) / 2.0f,
            paint
        )
    }

    private fun getColor(): Int {
        return testColorWrapper?.getRandomColor() ?: DisplayUtil.getRandomColor(random)
    }

    fun setTestColorWrapper(testColorWrapper: TestColorWrapper) {
        this.testColorWrapper = testColorWrapper
    }

    fun startAnim(container: ViewGroup?, reverse: Boolean) {
        container ?: return
        this.removeFromParent()

        val width = container.width.toFloat()
        val height = container.height.toFloat()
        val size = DisplayUtil.dip2px(context, 60F)

        val path = Path()
        if (reverse) {
            path.moveTo(width - size, 0F)
            path.cubicTo(
                width * 0.75F, height * 0.75F,
                width * 0.25F, height * 0.25F,
                0F, height - size
            )
        } else {
            path.moveTo(0F, 0F)
            path.cubicTo(
                width * 0.25F, height * 0.75F,
                width * 0.75F, height * 0.25F,
                width - size, height - size
            )
        }


        val pm = PathMeasure(path, false)

        val pos = FloatArray(2)

        val animator = ValueAnimator.ofFloat(0F, pm.length).also {
            animator = it
        }
        animator.interpolator = AccelerateDecelerateInterpolator()
        animator.duration = 500
        animator.repeatMode = REVERSE
        animator.repeatCount = 50

        animator.addUpdateListener {
            val distance = it.animatedValue as Float
            evaluateBezier(distance, pm, pos)
            translationX = pos[0]
            translationY = pos[1]
            this@AnimTestView.invalidate()
        }

        animator.doOnStart {
            container.addView(this@AnimTestView, LayoutParams(size, size))
        }

        animator.doOnEnd {
            this@AnimTestView.removeFromParent()
        }

        animator.start()
    }

    fun stopAnim() {
        this.removeFromParent()
    }

    private fun evaluateBezier(distance: Float, pm: PathMeasure, pos: FloatArray) {
        pm.getPosTan(distance, pos, null)
    }

    private fun View.removeFromParent() {
        val parent = this.parent as? ViewGroup ?: return
        parent.removeView(this)
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        animator?.removeAllListeners()
        animator?.removeAllUpdateListeners()
        animator?.cancel()
        animator = null
    }
}