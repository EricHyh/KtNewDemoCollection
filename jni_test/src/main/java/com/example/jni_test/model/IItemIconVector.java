/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class IItemIconVector extends java.util.AbstractList<IItemIcon> implements java.util.RandomAccess {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public IItemIconVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IItemIconVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public static long swigRelease(IItemIconVector obj) {
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
        JNIItemTestJNI.delete_IItemIconVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public IItemIconVector(IItemIcon[] initialElements) {
    this();
    reserve(initialElements.length);

    for (IItemIcon element : initialElements) {
      add(element);
    }
  }

  public IItemIconVector(Iterable<IItemIcon> initialElements) {
    this();
    for (IItemIcon element : initialElements) {
      add(element);
    }
  }

  public IItemIcon get(int index) {
    return doGet(index);
  }

  public IItemIcon set(int index, IItemIcon e) {
    return doSet(index, e);
  }

  public boolean add(IItemIcon e) {
    modCount++;
    doAdd(e);
    return true;
  }

  public void add(int index, IItemIcon e) {
    modCount++;
    doAdd(index, e);
  }

  public IItemIcon remove(int index) {
    modCount++;
    return doRemove(index);
  }

  protected void removeRange(int fromIndex, int toIndex) {
    modCount++;
    doRemoveRange(fromIndex, toIndex);
  }

  public int size() {
    return doSize();
  }

  public int capacity() {
    return doCapacity();
  }

  public void reserve(int n) {
    doReserve(n);
  }

  public IItemIconVector() {
    this(JNIItemTestJNI.new_IItemIconVector__SWIG_0(), true);
  }

  public IItemIconVector(IItemIconVector other) {
    this(JNIItemTestJNI.new_IItemIconVector__SWIG_1(IItemIconVector.getCPtr(other), other), true);
  }

  public boolean isEmpty() {
    return JNIItemTestJNI.IItemIconVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    JNIItemTestJNI.IItemIconVector_clear(swigCPtr, this);
  }

  public IItemIconVector(int count, IItemIcon value) {
    this(JNIItemTestJNI.new_IItemIconVector__SWIG_2(count, IItemIcon.getCPtr(value), value), true);
  }

  private int doCapacity() {
    return JNIItemTestJNI.IItemIconVector_doCapacity(swigCPtr, this);
  }

  private void doReserve(int n) {
    JNIItemTestJNI.IItemIconVector_doReserve(swigCPtr, this, n);
  }

  private int doSize() {
    return JNIItemTestJNI.IItemIconVector_doSize(swigCPtr, this);
  }

  private void doAdd(IItemIcon x) {
    JNIItemTestJNI.IItemIconVector_doAdd__SWIG_0(swigCPtr, this, IItemIcon.getCPtr(x), x);
  }

  private void doAdd(int index, IItemIcon x) {
    JNIItemTestJNI.IItemIconVector_doAdd__SWIG_1(swigCPtr, this, index, IItemIcon.getCPtr(x), x);
  }

  private IItemIcon doRemove(int index) {
    long cPtr = JNIItemTestJNI.IItemIconVector_doRemove(swigCPtr, this, index);
    return (cPtr == 0) ? null : new IItemIcon(cPtr, true);
  }

  private IItemIcon doGet(int index) {
    long cPtr = JNIItemTestJNI.IItemIconVector_doGet(swigCPtr, this, index);
    return (cPtr == 0) ? null : new IItemIcon(cPtr, true);
  }

  private IItemIcon doSet(int index, IItemIcon val) {
    long cPtr = JNIItemTestJNI.IItemIconVector_doSet(swigCPtr, this, index, IItemIcon.getCPtr(val), val);
    return (cPtr == 0) ? null : new IItemIcon(cPtr, true);
  }

  private void doRemoveRange(int fromIndex, int toIndex) {
    JNIItemTestJNI.IItemIconVector_doRemoveRange(swigCPtr, this, fromIndex, toIndex);
  }

}