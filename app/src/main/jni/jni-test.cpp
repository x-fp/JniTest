#include <jni.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "jni-test.h"



jstring get(JNIEnv *env, jobject obj) {

    //定义类的路径
    char *classPath = "com/xc/jnitest/exercise/JniTest";
    //找到类
    jclass jclass1 = env->FindClass(classPath);
    if(jclass1==NULL){
        return JNI_FALSE;
    }

    //定义方法名
    char *methodName ="javaMethod";
    //定义参数和返回值类型
    char *parameter = "(Ljava/lang/String;)V";
    //得到方法ID
    jmethodID methodId = env->GetStaticMethodID(jclass1, methodName, parameter);
    if(methodId==NULL){
        return JNI_FALSE;
    }

    //调用java方法
    jstring str = env->NewStringUTF("This is Jni Call");
    env->CallStaticVoidMethod(jclass1, methodId, str);

    //释放资源
    env->DeleteLocalRef(jclass1);
    env->DeleteLocalRef(str);

    return env->NewStringUTF("Hello from JNI !");
}


void set(JNIEnv *env, jobject obj, jstring string) {
    const char *str = (char *) env->GetStringUTFChars(string, NULL);

    LOGE("hello %s",str);

    env->ReleaseStringUTFChars(string, str);

}

jintArray formatArray(JNIEnv *env, jobject obj, jintArray array) {

    jint nativeArray[5];

    env->GetIntArrayRegion(array, 0, 5, nativeArray);

    for (int i = 0; i < 5; ++i) {
        nativeArray[i] += 5;
    }
    env->SetIntArrayRegion(array, 0, 5, nativeArray);
    return array;

}

//参数映射表
static JNINativeMethod getMethods[] = {
        {"get",         "()Ljava/lang/String;",  (void *) get},
        {"set",         "(Ljava/lang/String;)V", (void *) set},
//        {"formatArray", " ([I)[I",              (void *) formatArray},
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