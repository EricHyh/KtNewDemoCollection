/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


package com.hyh.jnitest.test.field;




public class StringLiveData extends ILiveData {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  public StringLiveData(long cPtr, boolean cMemoryOwn) {
    super(com.hyh.jnitest.test.field.FieldModuleJNI.StringLiveData_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(StringLiveData obj) {
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
        com.hyh.jnitest.test.field.FieldModuleJNI.delete_StringLiveData(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public StringLiveData(String value) {
    this(com.hyh.jnitest.test.field.FieldModuleJNI.new_StringLiveData(value), true);
  }

  public String GetValue() {
    return com.hyh.jnitest.test.field.FieldModuleJNI.StringLiveData_GetValue(swigCPtr, this);
  }

  public void AddObserver(StringLiveDataObserver observer, boolean immediately) {
    com.hyh.jnitest.test.field.FieldModuleJNI.StringLiveData_AddObserver(swigCPtr, this, StringLiveDataObserver.getCPtr(observer), observer, immediately);
  }

  public void RemoveObserver(StringLiveDataObserver observer) {
    com.hyh.jnitest.test.field.FieldModuleJNI.StringLiveData_RemoveObserver(swigCPtr, this, StringLiveDataObserver.getCPtr(observer), observer);
  }

}
