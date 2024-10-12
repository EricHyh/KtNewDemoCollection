package com.hyh.paging3demo

import android.hardware.biometrics.BiometricManager
import android.os.Build
import android.os.Bundle
import android.os.Parcel
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.huawei.facerecognition.FaceManager
import com.huawei.facerecognition.HwFaceManagerFactory
import com.hyh.paging3demo.anim.toByteArray
import com.hyh.paging3demo.base.Global
import com.hyh.paging3demo.fragment.ProjectsFragment

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        /*val manager = BiometricManager.from(this)
        val canAuthenticate = manager.canAuthenticate()
        Log.d("TAG_HYH", "onCreate: canAuthenticate = $canAuthenticate")*/



        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            val manager: BiometricManager = getSystemService(BiometricManager::class.java)
            val canAuthenticate = manager.canAuthenticate()
            /*val canAuthenticate1 = manager.canAuthenticate(Authenticators.BIOMETRIC_STRONG)
            val canAuthenticate2 = manager.canAuthenticate(Authenticators.BIOMETRIC_WEAK)
            val canAuthenticate3 = manager.canAuthenticate(Authenticators.DEVICE_CREDENTIAL)*/

            /*Log.d("TAG_HYH", "onCreate: canAuthenticate BIOMETRIC_STRONG = $canAuthenticate1")
            Log.d("TAG_HYH", "onCreate: canAuthenticate BIOMETRIC_WEAK = $canAuthenticate2")
            Log.d("TAG_HYH", "onCreate: canAuthenticate DEVICE_CREDENTIAL = $canAuthenticate3")*/
        }

        /*val faceManager: FaceManager = HwFaceManagerFactory.getFaceManager(applicationContext)

        val hasEnrolledTemplates = faceManager.hasEnrolledTemplates()

        Log.d("TAG_HYH", "onCreate: canAuthenticate hasEnrolledTemplates = $hasEnrolledTemplates")*/
    }

    fun openPagingSourceType(view: View) {
        openList(Global.PAGING_SOURCE_TYPE)
    }

    fun openPrevPageType(view: View) {
        openList(Global.SUPPORT_PREV_PAGE_TYPE)
    }

    fun openRemoteMediatorType(view: View) {
        openList(Global.REMOTE_MEDIATOR_TYPE)
    }

    private fun openList(type: Int) {
        Global.sourceType = type

        val testParcelize = TestParcelize().also {
            it.a = 10
            it.b = "100"
        }

        val bundle = Bundle().also {
            it.putParcelable("testParcelize", testParcelize)
        }
        val obtain = Parcel.obtain()
        bundle.writeToParcel(obtain, 0)

        Log.d("XXXMainActivity", "openList xxx: ${System.identityHashCode(testParcelize)}")

        supportFragmentManager
            .beginTransaction()
            .add(
                android.R.id.content,
                ProjectsFragment::class.java,
                Bundle().apply {
                    readFromParcel(obtain)
                })
            .addToBackStack(null)
            .commitAllowingStateLoss()
    }
}