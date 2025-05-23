/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


package com.hyh.jnitest.test.observer.model;




public class TestStruct2 {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public TestStruct2(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(TestStruct2 obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static long swigRelease(TestStruct2 obj) {
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
        com.hyh.jnitest.test.observer.ObserverModuleJNI.delete_TestStruct2(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setGroupName(String value) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.TestStruct2_groupName_set(swigCPtr, this, value);
  }

  public String getGroupName() {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.TestStruct2_groupName_get(swigCPtr, this);
  }

  public TestStruct2() {
    this(com.hyh.jnitest.test.observer.ObserverModuleJNI.new_TestStruct2(), true);
  }

}
