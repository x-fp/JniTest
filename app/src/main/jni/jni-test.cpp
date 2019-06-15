#include <jni.h>
#include <stdio.h>
#include <assert.h>

#include "jni-test.h"

jstring get(JNIEnv *env, jobject obj) {
    return env->NewStringUTF("Hello from JNI !");
}


void set(JNIEnv *env, jobject obj, jstring string) {
    char *str = (char *) env->GetStringUTFChars(string, NULL);
    env->ReleaseStringUTFChars(string, str);
}

//参数映射表
static JNINativeMethod getMethods[] = {
        {"get", "()Ljava/lang/String;", (void *) get},
        {"set", "(Ljava/lang/String;)V", (void *) set},
};

//native类路径
static const char *className = "com/xc/jnitest/exercise/JniTest";

//注册native方法
static int registerNatives(JNIEnv *engv) {
    jclass clazz;
    clazz = engv->FindClass(className);   //找到native类
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //int len = sizeof(methods) / sizeof(methods[0]);
    if (engv->RegisterNatives(clazz, getMethods,
                              sizeof(getMethods) / sizeof(getMethods[0])) <
        0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    assert(env != NULL);
    //为了方便管理我们将不同java类中的native方法分别注册
    if (registerNatives(env) < 0) {  //注册native方法
        return result;
    }
    //如果还有别的native类，可继续在此进行注册

    return JNI_VERSION_1_6;
}