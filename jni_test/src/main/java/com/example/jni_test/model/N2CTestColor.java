/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class N2CTestColor extends ITestColor {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  public N2CTestColor(long cPtr, boolean cMemoryOwn) {
    super(JNIItemTestJNI.N2CTestColor_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(N2CTestColor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public void swigSetCMemOwn(boolean own) {
    swigCMemOwnDerived = own;
    super.swigSetCMemOwn(own);
  }

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwnDerived) {
        swigCMemOwnDerived = false;
        JNIItemTestJNI.delete_N2CTestColor(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  protected void swigDirectorDisconnect() {
    swigSetCMemOwn(false);
    delete();
  }

  public void swigReleaseOwnership() {
    swigSetCMemOwn(false);
    JNIItemTestJNI.N2CTestColor_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    JNIItemTestJNI.N2CTestColor_change_ownership(this, swigCPtr, true);
  }

  public int getRandomColor() {
    return (getClass() == N2CTestColor.class) ? JNIItemTestJNI.N2CTestColor_getRandomColor(swigCPtr, this) : JNIItemTestJNI.N2CTestColor_getRandomColorSwigExplicitN2CTestColor(swigCPtr, this);
  }

  public String add(String a, String b) {
    return (getClass() == N2CTestColor.class) ? JNIItemTestJNI.N2CTestColor_add(swigCPtr, this, a, b) : JNIItemTestJNI.N2CTestColor_addSwigExplicitN2CTestColor(swigCPtr, this, a, b);
  }

  public N2CTestColor() {
    this(JNIItemTestJNI.new_N2CTestColor(), true);
    JNIItemTestJNI.N2CTestColor_director_connect(this, swigCPtr, true, true);
  }

}
