/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.example.jni_test.model;

public enum TestEnum1 {
  AllTradingTime(JNIItemTestJNI.TestEnum1_AllTradingTime_get()),
  UsPreMarketAfter(JNIItemTestJNI.TestEnum1_UsPreMarketAfter_get());

  public final int swigValue() {
    return swigValue;
  }

  public static TestEnum1 swigToEnum(int swigValue) {
    TestEnum1[] swigValues = TestEnum1.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (TestEnum1 swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + TestEnum1.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private TestEnum1() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private TestEnum1(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private TestEnum1(TestEnum1 swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

