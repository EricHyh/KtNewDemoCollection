/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.ndk_demo_lib1;

public class SwigCallbackFunction1Bridge {
  private transient long swigCPtr;
  private transient boolean swigCMemOwn;

  public SwigCallbackFunction1Bridge(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(SwigCallbackFunction1Bridge obj) {
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
        SwigCallbackDemoJNI.delete_SwigCallbackFunction1Bridge(swigCPtr);
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
    SwigCallbackDemoJNI.SwigCallbackFunction1Bridge_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    SwigCallbackDemoJNI.SwigCallbackFunction1Bridge_change_ownership(this, swigCPtr, true);
  }

  public void onCall(SwigCallbackData data) {
    SwigCallbackDemoJNI.SwigCallbackFunction1Bridge_onCall(swigCPtr, this, SwigCallbackData.getCPtr(data), data);
  }

  public SwigCallbackFunction1Bridge() {
    this(SwigCallbackDemoJNI.new_SwigCallbackFunction1Bridge(), true);
    SwigCallbackDemoJNI.SwigCallbackFunction1Bridge_director_connect(this, swigCPtr, true, true);
  }

}
