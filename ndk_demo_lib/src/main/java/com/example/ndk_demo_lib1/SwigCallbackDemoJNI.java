/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.2.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.ndk_demo_lib1;

public class SwigCallbackDemoJNI {
  public final static native void delete_SwigCallbackFunctionBridge(long jarg1);
  public final static native void SwigCallbackFunctionBridge_onCall(long jarg1, SwigCallbackFunctionBridge jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native long new_SwigCallbackFunctionBridge();
  public final static native void SwigCallbackFunctionBridge_director_connect(SwigCallbackFunctionBridge obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void SwigCallbackFunctionBridge_change_ownership(SwigCallbackFunctionBridge obj, long cptr, boolean take_or_release);
  public final static native void delete_SwigCallbackFunction1Bridge(long jarg1);
  public final static native void SwigCallbackFunction1Bridge_onCall(long jarg1, SwigCallbackFunction1Bridge jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native long new_SwigCallbackFunction1Bridge();
  public final static native void SwigCallbackFunction1Bridge_director_connect(SwigCallbackFunction1Bridge obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void SwigCallbackFunction1Bridge_change_ownership(SwigCallbackFunction1Bridge obj, long cptr, boolean take_or_release);
  public final static native void delete_InnerObserver2Bridge(long jarg1);
  public final static native void InnerObserver2Bridge_onCall(long jarg1, InnerObserver2Bridge jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native long new_InnerObserver2Bridge();
  public final static native void InnerObserver2Bridge_director_connect(InnerObserver2Bridge obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void InnerObserver2Bridge_change_ownership(InnerObserver2Bridge obj, long cptr, boolean take_or_release);
  public final static native void delete_InnerObserver3Bridge(long jarg1);
  public final static native void InnerObserver3Bridge_onCall(long jarg1, InnerObserver3Bridge jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native long new_InnerObserver3Bridge();
  public final static native void InnerObserver3Bridge_director_connect(InnerObserver3Bridge obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void InnerObserver3Bridge_change_ownership(InnerObserver3Bridge obj, long cptr, boolean take_or_release);
  public final static native void delete_InnerObserver(long jarg1);
  public final static native void InnerObserver_onTest1(long jarg1, InnerObserver jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native long new_InnerObserver();
  public final static native void InnerObserver_director_connect(InnerObserver obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void InnerObserver_change_ownership(InnerObserver obj, long cptr, boolean take_or_release);
  public final static native void SwigCallback_onTest1(long jarg1, SwigCallback jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native void SwigCallback_onTest2(long jarg1, SwigCallback jarg1_, long jarg2, SwigCallbackData jarg2_);
  public final static native void SwigCallback_onTest3(long jarg1, SwigCallback jarg1_, long jarg2, InnerObserver jarg2_);
  public final static native long SwigCallback_onTest4(long jarg1, SwigCallback jarg1_, int jarg2);
  public final static native void SwigCallback_onTest5(long jarg1, SwigCallback jarg1_, int jarg2, String jarg3, long jarg4, InnerObserver2Bridge jarg4_, int jarg5);
  public final static native void SwigCallback_onTest6(long jarg1, SwigCallback jarg1_, int jarg2, String jarg3, long jarg4, InnerObserver2Bridge jarg4_, long jarg5, InnerObserver3Bridge jarg5_, int jarg6);
  public final static native void delete_SwigCallback(long jarg1);
  public final static native long new_SwigCallback();
  public final static native void SwigCallback_director_connect(SwigCallback obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void SwigCallback_change_ownership(SwigCallback obj, long cptr, boolean take_or_release);
  public final static native void FINFeatureFlagVariant_name_set(long jarg1, FINFeatureFlagVariant jarg1_, String jarg2);
  public final static native String FINFeatureFlagVariant_name_get(long jarg1, FINFeatureFlagVariant jarg1_);
  public final static native void FINFeatureFlagVariant_payload_set(long jarg1, FINFeatureFlagVariant jarg1_, String jarg2);
  public final static native String FINFeatureFlagVariant_payload_get(long jarg1, FINFeatureFlagVariant jarg1_);
  public final static native long new_FINFeatureFlagVariant();
  public final static native void delete_FINFeatureFlagVariant(long jarg1);
  public final static native void FINFeatureFlagModel_id_set(long jarg1, FINFeatureFlagModel jarg1_, String jarg2);
  public final static native String FINFeatureFlagModel_id_get(long jarg1, FINFeatureFlagModel jarg1_);
  public final static native void FINFeatureFlagModel_variant_set(long jarg1, FINFeatureFlagModel jarg1_, long jarg2, FINFeatureFlagVariant jarg2_);
  public final static native long FINFeatureFlagModel_variant_get(long jarg1, FINFeatureFlagModel jarg1_);
  public final static native long new_FINFeatureFlagModel();
  public final static native void delete_FINFeatureFlagModel(long jarg1);
  public final static native void SwigCallbackData_a_set(long jarg1, SwigCallbackData jarg1_, int jarg2);
  public final static native int SwigCallbackData_a_get(long jarg1, SwigCallbackData jarg1_);
  public final static native long new_SwigCallbackData(int jarg1);
  public final static native void delete_SwigCallbackData(long jarg1);
  public final static native void TestSwigCallback_setCallback1(long jarg1, TestSwigCallback jarg1_, long jarg2, SwigCallback jarg2_);
  public final static native void TestSwigCallback_setCallback2(long jarg1, TestSwigCallback jarg1_, long jarg2, SwigCallback jarg2_);
  public final static native void TestSwigCallback_setCallback3(long jarg1, TestSwigCallback jarg1_, int jarg2, long jarg3, SwigCallback jarg3_);
  public final static native void TestSwigCallback_setCallback4(long jarg1, TestSwigCallback jarg1_, long jarg2, SwigCallbackFunctionBridge jarg2_);
  public final static native void TestSwigCallback_setCallback5(long jarg1, TestSwigCallback jarg1_, long jarg2, SwigCallbackFunction1Bridge jarg2_);
  public final static native long new_TestSwigCallback();
  public final static native void delete_TestSwigCallback(long jarg1);

  public static void SwigDirector_SwigCallbackFunctionBridge_onCall(SwigCallbackFunctionBridge jself, long data) {
    jself.onCall((data == 0) ? null : new SwigCallbackData(data, true));
  }
  public static void SwigDirector_SwigCallbackFunction1Bridge_onCall(SwigCallbackFunction1Bridge jself, long data) {
    jself.onCall((data == 0) ? null : new SwigCallbackData(data, true));
  }
  public static void SwigDirector_InnerObserver2Bridge_onCall(InnerObserver2Bridge jself, long data) {
    jself.onCall((data == 0) ? null : new SwigCallbackData(data, true));
  }
  public static void SwigDirector_InnerObserver3Bridge_onCall(InnerObserver3Bridge jself, long data) {
    jself.onCall((data == 0) ? null : new SwigCallbackData(data, true));
  }
  public static void SwigDirector_InnerObserver_onTest1(InnerObserver jself, long data1) {
    jself.onTest1((data1 == 0) ? null : new SwigCallbackData(data1, true));
  }
  public static void SwigDirector_SwigCallback_onTest1(SwigCallback jself, long data1) {
    jself.onTest1((data1 == 0) ? null : new SwigCallbackData(data1, true));
  }
  public static void SwigDirector_SwigCallback_onTest2(SwigCallback jself, long data2) {
    jself.onTest2((data2 == 0) ? null : new SwigCallbackData(data2, true));
  }
  public static void SwigDirector_SwigCallback_onTest3(SwigCallback jself, long innerCallback) {
    jself.onTest3((innerCallback == 0) ? null : new InnerObserver(innerCallback, true));
  }
  public static long SwigDirector_SwigCallback_onTest4(SwigCallback jself, int gg) {
    return SwigCallbackData.getCPtr(jself.onTest4(gg));
  }
  public static void SwigDirector_SwigCallback_onTest5(SwigCallback jself, int a, String b, long innerCallback, int c) {
    jself.onTest5(a, b, (innerCallback == 0) ? null : new InnerObserver2Bridge(innerCallback, true), c);
  }
  public static void SwigDirector_SwigCallback_onTest6(SwigCallback jself, int a, String b, long innerCallback2, long innerCallback3, int c) {
    jself.onTest6(a, b, (innerCallback2 == 0) ? null : new InnerObserver2Bridge(innerCallback2, true), (innerCallback3 == 0) ? null : new InnerObserver3Bridge(innerCallback3, true), c);
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
