/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public class JNIItemTestJNI {
  public final static native long new_StringVector__SWIG_0();
  public final static native long new_StringVector__SWIG_1(long jarg1, StringVector jarg1_);
  public final static native boolean StringVector_isEmpty(long jarg1, StringVector jarg1_);
  public final static native void StringVector_clear(long jarg1, StringVector jarg1_);
  public final static native long new_StringVector__SWIG_2(int jarg1, String jarg2);
  public final static native int StringVector_doCapacity(long jarg1, StringVector jarg1_);
  public final static native void StringVector_doReserve(long jarg1, StringVector jarg1_, int jarg2);
  public final static native int StringVector_doSize(long jarg1, StringVector jarg1_);
  public final static native void StringVector_doAdd__SWIG_0(long jarg1, StringVector jarg1_, String jarg2);
  public final static native void StringVector_doAdd__SWIG_1(long jarg1, StringVector jarg1_, int jarg2, String jarg3);
  public final static native String StringVector_doRemove(long jarg1, StringVector jarg1_, int jarg2);
  public final static native String StringVector_doGet(long jarg1, StringVector jarg1_, int jarg2);
  public final static native String StringVector_doSet(long jarg1, StringVector jarg1_, int jarg2, String jarg3);
  public final static native void StringVector_doRemoveRange(long jarg1, StringVector jarg1_, int jarg2, int jarg3);
  public final static native void delete_StringVector(long jarg1);
  public final static native long new_IItemIconVector__SWIG_0();
  public final static native long new_IItemIconVector__SWIG_1(long jarg1, IItemIconVector jarg1_);
  public final static native boolean IItemIconVector_isEmpty(long jarg1, IItemIconVector jarg1_);
  public final static native void IItemIconVector_clear(long jarg1, IItemIconVector jarg1_);
  public final static native long new_IItemIconVector__SWIG_2(int jarg1, long jarg2, IItemIcon jarg2_);
  public final static native int IItemIconVector_doCapacity(long jarg1, IItemIconVector jarg1_);
  public final static native void IItemIconVector_doReserve(long jarg1, IItemIconVector jarg1_, int jarg2);
  public final static native int IItemIconVector_doSize(long jarg1, IItemIconVector jarg1_);
  public final static native void IItemIconVector_doAdd__SWIG_0(long jarg1, IItemIconVector jarg1_, long jarg2, IItemIcon jarg2_);
  public final static native void IItemIconVector_doAdd__SWIG_1(long jarg1, IItemIconVector jarg1_, int jarg2, long jarg3, IItemIcon jarg3_);
  public final static native long IItemIconVector_doRemove(long jarg1, IItemIconVector jarg1_, int jarg2);
  public final static native long IItemIconVector_doGet(long jarg1, IItemIconVector jarg1_, int jarg2);
  public final static native long IItemIconVector_doSet(long jarg1, IItemIconVector jarg1_, int jarg2, long jarg3, IItemIcon jarg3_);
  public final static native void IItemIconVector_doRemoveRange(long jarg1, IItemIconVector jarg1_, int jarg2, int jarg3);
  public final static native void delete_IItemIconVector(long jarg1);
  public final static native void delete_IItemIcon(long jarg1);
  public final static native String IItemIcon_getName(long jarg1, IItemIcon jarg1_);
  public final static native String IItemIcon_getIcon(long jarg1, IItemIcon jarg1_);
  public final static native long new_IItemIcon();
  public final static native void IItemIcon_director_connect(IItemIcon obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void IItemIcon_change_ownership(IItemIcon obj, long cptr, boolean take_or_release);
  public final static native void delete_ITestItem(long jarg1);
  public final static native String ITestItem_getId(long jarg1, ITestItem jarg1_);
  public final static native String ITestItem_getTitle(long jarg1, ITestItem jarg1_);
  public final static native String ITestItem_getEnvelopePic(long jarg1, ITestItem jarg1_);
  public final static native String ITestItem_getDesc(long jarg1, ITestItem jarg1_);
  public final static native String ITestItem_getNiceDate(long jarg1, ITestItem jarg1_);
  public final static native String ITestItem_getAuthor(long jarg1, ITestItem jarg1_);
  public final static native long ITestItem_getTags(long jarg1, ITestItem jarg1_);
  public final static native long ITestItem_getIcons(long jarg1, ITestItem jarg1_);
  public final static native long new_ITestItem();
  public final static native void ITestItem_director_connect(ITestItem obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void ITestItem_change_ownership(ITestItem obj, long cptr, boolean take_or_release);
  public final static native void delete_IC2NTestItemFactory(long jarg1);
  public final static native long IC2NTestItemFactory_create(long jarg1, IC2NTestItemFactory jarg1_, int jarg2);
  public final static native long new_IC2NTestItemFactory();
  public final static native void IC2NTestItemFactory_director_connect(IC2NTestItemFactory obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void IC2NTestItemFactory_change_ownership(IC2NTestItemFactory obj, long cptr, boolean take_or_release);
  public final static native void C2NTestItemFactory_init(long jarg1, IC2NTestItemFactory jarg1_);
  public final static native long C2NTestItemFactory_create(int jarg1);
  public final static native long new_C2NTestItemFactory();
  public final static native void delete_C2NTestItemFactory(long jarg1);
  public final static native long new_N2CTestItem(int jarg1);
  public final static native void delete_N2CTestItem(long jarg1);
  public final static native String N2CTestItem_getId(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getIdSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getTitle(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getTitleSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getEnvelopePic(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getEnvelopePicSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getDesc(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getDescSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getNiceDate(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getNiceDateSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getAuthor(long jarg1, N2CTestItem jarg1_);
  public final static native String N2CTestItem_getAuthorSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native long N2CTestItem_getTags(long jarg1, N2CTestItem jarg1_);
  public final static native long N2CTestItem_getTagsSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native long N2CTestItem_getIcons(long jarg1, N2CTestItem jarg1_);
  public final static native long N2CTestItem_getIconsSwigExplicitN2CTestItem(long jarg1, N2CTestItem jarg1_);
  public final static native void N2CTestItem_director_connect(N2CTestItem obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void N2CTestItem_change_ownership(N2CTestItem obj, long cptr, boolean take_or_release);
  public final static native long new_N2CItemIcon(int jarg1);
  public final static native String N2CItemIcon_getName(long jarg1, N2CItemIcon jarg1_);
  public final static native String N2CItemIcon_getNameSwigExplicitN2CItemIcon(long jarg1, N2CItemIcon jarg1_);
  public final static native String N2CItemIcon_getIcon(long jarg1, N2CItemIcon jarg1_);
  public final static native String N2CItemIcon_getIconSwigExplicitN2CItemIcon(long jarg1, N2CItemIcon jarg1_);
  public final static native void delete_N2CItemIcon(long jarg1);
  public final static native void N2CItemIcon_director_connect(N2CItemIcon obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void N2CItemIcon_change_ownership(N2CItemIcon obj, long cptr, boolean take_or_release);
  public final static native long N2CTestItem_SWIGSmartPtrUpcast(long jarg1);
  public final static native long N2CItemIcon_SWIGSmartPtrUpcast(long jarg1);

  public static String SwigDirector_IItemIcon_getName(IItemIcon jself) {
    return jself.getName();
  }
  public static String SwigDirector_IItemIcon_getIcon(IItemIcon jself) {
    return jself.getIcon();
  }
  public static String SwigDirector_ITestItem_getId(ITestItem jself) {
    return jself.getId();
  }
  public static String SwigDirector_ITestItem_getTitle(ITestItem jself) {
    return jself.getTitle();
  }
  public static String SwigDirector_ITestItem_getEnvelopePic(ITestItem jself) {
    return jself.getEnvelopePic();
  }
  public static String SwigDirector_ITestItem_getDesc(ITestItem jself) {
    return jself.getDesc();
  }
  public static String SwigDirector_ITestItem_getNiceDate(ITestItem jself) {
    return jself.getNiceDate();
  }
  public static String SwigDirector_ITestItem_getAuthor(ITestItem jself) {
    return jself.getAuthor();
  }
  public static long SwigDirector_ITestItem_getTags(ITestItem jself) {
    return StringVector.getCPtr(jself.getTags());
  }
  public static long SwigDirector_ITestItem_getIcons(ITestItem jself) {
    return IItemIconVector.getCPtr(jself.getIcons());
  }
  public static long SwigDirector_IC2NTestItemFactory_create(IC2NTestItemFactory jself, int index) {
    return ITestItem.getCPtr(jself.create(index));
  }
  public static String SwigDirector_N2CTestItem_getId(N2CTestItem jself) {
    return jself.getId();
  }
  public static String SwigDirector_N2CTestItem_getTitle(N2CTestItem jself) {
    return jself.getTitle();
  }
  public static String SwigDirector_N2CTestItem_getEnvelopePic(N2CTestItem jself) {
    return jself.getEnvelopePic();
  }
  public static String SwigDirector_N2CTestItem_getDesc(N2CTestItem jself) {
    return jself.getDesc();
  }
  public static String SwigDirector_N2CTestItem_getNiceDate(N2CTestItem jself) {
    return jself.getNiceDate();
  }
  public static String SwigDirector_N2CTestItem_getAuthor(N2CTestItem jself) {
    return jself.getAuthor();
  }
  public static long SwigDirector_N2CTestItem_getTags(N2CTestItem jself) {
    return StringVector.getCPtr(jself.getTags());
  }
  public static long SwigDirector_N2CTestItem_getIcons(N2CTestItem jself) {
    return IItemIconVector.getCPtr(jself.getIcons());
  }
  public static String SwigDirector_N2CItemIcon_getName(N2CItemIcon jself) {
    return jself.getName();
  }
  public static String SwigDirector_N2CItemIcon_getIcon(N2CItemIcon jself) {
    return jself.getIcon();
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
