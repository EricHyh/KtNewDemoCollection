/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


package com.hyh.jnitest.test.item;
import com.hyh.jnitest.basic.infrastructure.*;



public class N2CTestItem extends ITestItem {
  private transient long swigCPtr;
  private transient boolean swigCMemOwnDerived;

  public N2CTestItem(long cPtr, boolean cMemoryOwn) {
    super(com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_SWIGSmartPtrUpcast(cPtr), true);
    swigCMemOwnDerived = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(N2CTestItem obj) {
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
        com.hyh.jnitest.test.item.ItemModuleJNI.delete_N2CTestItem(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  protected void swigDirectorDisconnect() {
    swigSetCMemOwn(false);
    delete();
  }

  public void swigReleaseOwnership() {
    swigSetCMemOwn(false);
    com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigSetCMemOwn(true);
    com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_change_ownership(this, swigCPtr, true);
  }

  public N2CTestItem(int index) {
    this(com.hyh.jnitest.test.item.ItemModuleJNI.new_N2CTestItem(index), true);
    com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_director_connect(this, swigCPtr, true, true);
  }

  public String getId() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getId(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getIdSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public String getTitle() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getTitle(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getTitleSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public String getEnvelopePic() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getEnvelopePic(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getEnvelopePicSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public String getDesc() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getDesc(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getDescSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public String getNiceDate() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getNiceDate(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getNiceDateSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public String getAuthor() {
    return (getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getAuthor(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getAuthorSwigExplicitN2CTestItem(swigCPtr, this);
  }

  public StringVector getTags() {
    return new StringVector((getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getTags(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getTagsSwigExplicitN2CTestItem(swigCPtr, this), true);
  }

  public IItemIconVector getIcons() {
    return new IItemIconVector((getClass() == N2CTestItem.class) ? com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getIcons(swigCPtr, this) : com.hyh.jnitest.test.item.ItemModuleJNI.N2CTestItem_getIconsSwigExplicitN2CTestItem(swigCPtr, this), true);
  }

}
