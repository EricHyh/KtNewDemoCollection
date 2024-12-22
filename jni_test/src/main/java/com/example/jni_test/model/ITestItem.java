/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class ITestItem {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  public ITestItem(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ITestItem obj) {
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
        JNIItemTestJNI.delete_ITestItem(swigCPtr);
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
    JNIItemTestJNI.ITestItem_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    JNIItemTestJNI.ITestItem_change_ownership(this, swigCPtr, true);
  }

  public String getId() {
    return JNIItemTestJNI.ITestItem_getId(swigCPtr, this);
  }

  public String getTitle() {
    return JNIItemTestJNI.ITestItem_getTitle(swigCPtr, this);
  }

  public String getEnvelopePic() {
    return JNIItemTestJNI.ITestItem_getEnvelopePic(swigCPtr, this);
  }

  public String getDesc() {
    return JNIItemTestJNI.ITestItem_getDesc(swigCPtr, this);
  }

  public String getNiceDate() {
    return JNIItemTestJNI.ITestItem_getNiceDate(swigCPtr, this);
  }

  public String getAuthor() {
    return JNIItemTestJNI.ITestItem_getAuthor(swigCPtr, this);
  }

  public StringVector getTags() {
    return new StringVector(JNIItemTestJNI.ITestItem_getTags(swigCPtr, this), true);
  }

  public IItemIconVector getIcons() {
    return new IItemIconVector(JNIItemTestJNI.ITestItem_getIcons(swigCPtr, this), true);
  }

  public ITestItem() {
    this(JNIItemTestJNI.new_ITestItem(), true);
    JNIItemTestJNI.ITestItem_director_connect(this, swigCPtr, true, true);
  }

}
