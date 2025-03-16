/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class IntLiveDataObserver {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  public IntLiveDataObserver(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IntLiveDataObserver obj) {
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
        JNIItemTestJNI.delete_IntLiveDataObserver(swigCPtr);
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
    JNIItemTestJNI.IntLiveDataObserver_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    JNIItemTestJNI.IntLiveDataObserver_change_ownership(this, swigCPtr, true);
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null || getClass() != obj.getClass()) return false;
    IntLiveDataObserver other = (IntLiveDataObserver) obj;
    return this.isEquals(other);
  }

  @Override
  public int hashCode() {
    return this.calculateHash();
  }

  public IntLiveDataObserver() {
    this(JNIItemTestJNI.new_IntLiveDataObserver(), true);
    JNIItemTestJNI.IntLiveDataObserver_director_connect(this, swigCPtr, true, true);
  }

  public void onCall(int value) {
    JNIItemTestJNI.IntLiveDataObserver_onCall(swigCPtr, this, value);
  }

  private int calculateHash() {
    return JNIItemTestJNI.IntLiveDataObserver_calculateHash(swigCPtr, this);
  }

  private boolean isEquals(IntLiveDataObserver other) {
    return JNIItemTestJNI.IntLiveDataObserver_isEquals(swigCPtr, this, IntLiveDataObserver.getCPtr(other), other);
  }

}
