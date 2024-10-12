package com.hyh.paging3demo

import android.os.Parcel
import android.os.Parcelable
import android.util.Log

/**
 * TODO: Add Description
 *
 * @author eriche 2024/9/13
 */
class TestParcelize() : Parcelable {

    var a: Int = 0

    var b: String? = ""

    constructor(parcel: Parcel) : this() {
        a = parcel.readInt()
        b = parcel.readString()
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeInt(a)
        parcel.writeString(b ?: "")
    }

    override fun describeContents(): Int {
        return 0
    }

    override fun toString(): String {
        return "TestParcelize(a=$a, b=$b)"
    }

    companion object CREATOR : Parcelable.Creator<TestParcelize> {

        private const val TAG = "TestParcelize"

        override fun createFromParcel(parcel: Parcel): TestParcelize {
            Log.d(TAG, "createFromParcel: ")
            return TestParcelize(parcel)
        }

        override fun newArray(size: Int): Array<TestParcelize?> {
            return arrayOfNulls(size)
        }
    }


}