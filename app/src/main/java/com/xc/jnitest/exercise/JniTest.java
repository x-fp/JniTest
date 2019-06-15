package com.xc.jnitest.exercise;

public class JniTest {

    static{
        System.loadLibrary("jni-test");
    }

    public  native String get();

    public native void set(String str);
}
