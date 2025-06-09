package com.example.java_test;

import java.lang.reflect.Field;
import java.nio.charset.StandardCharsets;

public class MyClass {


    public static void main(String[] args) throws Exception {
        System.out.println("Hellow, world!");
        String str1 = "145";
        String str2 = "123";

        System.out.println(str1);
        System.out.println(str2);

        str2 = str1;
        modifyStr(str1);

        System.out.println(str1);
        System.out.println(str2);

        System.out.println("145");

        char c;
        byte b;
        short s;
        int i;
        long l;
        boolean bool;
        float f;
        double d;

    }


    public static void modifyStr(String original) throws Exception {
//        System.out.println(original); // 输出: 原始内容

        // 1. 获取内部存储字段
        Field valueField = String.class.getDeclaredField("value");
        Field coderField = String.class.getDeclaredField("coder");
        valueField.setAccessible(true);
        coderField.setAccessible(true);

        // 2. 读取当前编码标识 (0:LATIN1, 1:UTF16)
        byte coder = (byte) coderField.get(original);
        byte[] bytes = (byte[]) valueField.get(original);

        // 3. 按编码规则修改字节数组
        String newContent = "0";
        byte[] newBytes = encodeByCoder(newContent, coder);
        System.arraycopy(newBytes, 0, bytes, 0, newBytes.length);

//        System.out.println(original); // 输出: 修改内容
    }

    // 按 coder 标识编码新内容
    private static byte[] encodeByCoder(String str, byte coder) {
        return (coder == 0) ?
                str.getBytes(StandardCharsets.ISO_8859_1) : // LATIN1
                str.getBytes(StandardCharsets.UTF_16);      // UTF16
    }

}