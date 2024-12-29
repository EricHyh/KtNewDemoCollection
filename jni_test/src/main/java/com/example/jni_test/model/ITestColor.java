/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class ITestColor {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  public ITestColor(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ITestColor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public void swigSetCMemOwn(boolean own) {
    swigCMemOwn = own;
  }

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        JNIItemTestJNI.delete_ITestColor(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigSetCMemOwn(false);
    delete();
  }

  public void swigReleaseOwnership() {
    swigSetCMemOwn(false);
    JNIItemTestJNI.ITestColor_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    JNIItemTestJNI.ITestColor_change_ownership(this, swigCPtr, true);
  }

  public int getRandomColor() {
    return JNIItemTestJNI.ITestColor_getRandomColor(swigCPtr, this);
  }

  public String add(String a, String b) {
    return JNIItemTestJNI.ITestColor_add(swigCPtr, this, a, b);
  }

  public ITestColor() {
    this(JNIItemTestJNI.new_ITestColor(), true);
    JNIItemTestJNI.ITestColor_director_connect(this, swigCPtr, true, true);
  }

}
