package com.xc.jnitest.exercise;

import android.util.Log;

public class JniTest {

    static {
        System.loadLibrary("jni-test");
    }

    public native String get();

    public native void set(String str);

    public native int[] formatArray(int[] array);


    public static void staticMethod(String str) {
        Log.e("jniTest", str);
    }

    public void javaMethod(String str){
        Log.e("jniTest", str);
    }
}
