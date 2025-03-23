/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


package com.hyh.jnitest.test.observer;




public class IObserverManager {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public IObserverManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IObserverManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static long swigRelease(IObserverManager obj) {
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
        com.hyh.jnitest.test.observer.ObserverModuleJNI.delete_IObserverManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_change_ownership(this, swigCPtr, true);
  }

  public void addObserver(TestObserverBridge observer) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_addObserver(swigCPtr, this, TestObserverBridge.getCPtr(observer), observer);
  }

  public void removeObserver(TestObserverBridge observer) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_removeObserver(swigCPtr, this, TestObserverBridge.getCPtr(observer), observer);
  }

  public void addObserver2(ITestObserver2Bridge observer) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_addObserver2(swigCPtr, this, ITestObserver2Bridge.getCPtr(observer), observer);
  }

  public void removeObserver2(ITestObserver2Bridge observer) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_removeObserver2(swigCPtr, this, ITestObserver2Bridge.getCPtr(observer), observer);
  }

  public long add1(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add1(swigCPtr, this, a, b);
  }

  public long add11(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add11(swigCPtr, this, a, b);
  }

  public long add2(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add2(swigCPtr, this, a, b);
  }

  public long add22(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add22(swigCPtr, this, a, b);
  }

  public long add3(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add3(swigCPtr, this, a, b);
  }

  public long add33(long a, long b) {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_add33(swigCPtr, this, a, b);
  }

  public void byteTest1(byte[] byteArray) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_byteTest1(swigCPtr, this, byteArray);
  }

  public void byteTest2(byte[] byteArray) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_byteTest2(swigCPtr, this, byteArray);
  }

  public byte[] byteTest3() {
    return com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_byteTest3(swigCPtr, this);
  }

  public void setTestObserver2List(TestObserver2Vector arg0) {
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_setTestObserver2List(swigCPtr, this, TestObserver2Vector.getCPtr(arg0), arg0);
  }

  public TestEnum1 optionalEnum33() {
    return TestEnum1.swigToEnum(com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_optionalEnum33(swigCPtr, this));
  }

  public IObserverManager() {
    this(com.hyh.jnitest.test.observer.ObserverModuleJNI.new_IObserverManager(), true);
    com.hyh.jnitest.test.observer.ObserverModuleJNI.IObserverManager_director_connect(this, swigCPtr, true, true);
  }

}
