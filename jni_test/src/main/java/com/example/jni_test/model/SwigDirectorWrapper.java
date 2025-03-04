/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class SwigDirectorWrapper {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public SwigDirectorWrapper(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(SwigDirectorWrapper obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static long swigRelease(SwigDirectorWrapper obj) {
    long ptr = 0;
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new RuntimeException("Cannot release ownership as memory is not owned");
      ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.delete();
    }
    return ptr;
  }

  @SuppressWarnings({"deprecation", "removal"})
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        JNIItemTestJNI.delete_SwigDirectorWrapper(swigCPtr);
      }
      swigCPtr = 0;
    }
  }


  @SuppressWarnings("all")
  public <T> T acquire(IDirectorConstructor<T> constructor){
    if (IsJObject()) {
      return (T) GetJObject();
    } else {
      long cPtr = GetCPtr();
      return (cPtr == 0) ? null : constructor.create(cPtr);
    }
  }

  interface IDirectorConstructor<T> {
    T create(long cPtr);
  }

  public SwigDirectorWrapper(SwigDirectorWrapper arg0) {
    this(JNIItemTestJNI.new_SwigDirectorWrapper(SwigDirectorWrapper.swigRelease(arg0), arg0), true);
  }

  private boolean IsJObject() {
    return JNIItemTestJNI.SwigDirectorWrapper_IsJObject(swigCPtr, this);
  }

  private boolean IsCPtr() {
    return JNIItemTestJNI.SwigDirectorWrapper_IsCPtr(swigCPtr, this);
  }

  private Object GetJObject() {
    return JNIItemTestJNI.SwigDirectorWrapper_GetJObject(swigCPtr, this);
  }

  private long GetCPtr() {
    return JNIItemTestJNI.SwigDirectorWrapper_GetCPtr(swigCPtr, this);
  }

}
