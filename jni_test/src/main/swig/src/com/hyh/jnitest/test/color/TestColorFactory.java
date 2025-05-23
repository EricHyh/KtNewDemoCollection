/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


package com.hyh.jnitest.test.color;




public class TestColorFactory {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public TestColorFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(TestColorFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static long swigRelease(TestColorFactory obj) {
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
        com.hyh.jnitest.test.color.ColorModuleJNI.delete_TestColorFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static void init(ITestColor color) {
    com.hyh.jnitest.test.color.ColorModuleJNI.TestColorFactory_init(ITestColor.getCPtr(color), color);
  }

  public static ITestColor create() {
    long cPtr = com.hyh.jnitest.test.color.ColorModuleJNI.TestColorFactory_create();
    return (cPtr == 0) ? null : new ITestColor(cPtr, true);
  }

  public TestColorFactory() {
    this(com.hyh.jnitest.test.color.ColorModuleJNI.new_TestColorFactory(), true);
  }

}
