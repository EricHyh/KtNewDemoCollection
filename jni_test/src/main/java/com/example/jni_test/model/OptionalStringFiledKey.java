/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class OptionalStringFiledKey extends BaseFiledKey {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  public OptionalStringFiledKey(long cPtr, boolean cMemoryOwn) {
    super(JNIItemTestJNI.OptionalStringFiledKey_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(OptionalStringFiledKey obj) {
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
        JNIItemTestJNI.delete_OptionalStringFiledKey(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public int getKey() {
    return JNIItemTestJNI.OptionalStringFiledKey_getKey(swigCPtr, this);
  }

  public String getDefaultValue() {
    return JNIItemTestJNI.OptionalStringFiledKey_getDefaultValue(swigCPtr, this);
  }

}
