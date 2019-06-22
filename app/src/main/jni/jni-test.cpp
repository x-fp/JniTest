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
    if (jclass1 == NULL) {
        return JNI_FALSE;
    }

    /**调用java的static方法**/
    //定义方法名
    char *static_methodName = "staticMethod";
    //定义参数和返回值类型
    char *static_parameter = "(Ljava/lang/String;)V";
    //得到静态方法ID
    jmethodID static_methodId = env->GetStaticMethodID(jclass1, static_methodName,
                                                       static_parameter);
    if (static_methodId == NULL) {
        return JNI_FALSE;
    }

    //调用java static 方法
    jstring static_str = env->NewStringUTF("Call static method from Java");
    env->CallStaticVoidMethod(jclass1, static_methodId, static_str);

    //释放资源
    env->DeleteLocalRef(static_str);

    /**调用java的 非static 方法**/
    //定义方法名
    char *methodName = "javaMethod";
    //定义参数和返回值
    char *parameter = "(Ljava/lang/String;)V";
    //得到方法ID
    jmethodID methodId = env->GetMethodID(jclass1, methodName, parameter);

    //定义构造方法名
    char *constructor_methodName = "<init>";
    jmethodID construtor_methodId = env->GetMethodID(jclass1, constructor_methodName, "()V");
    if (construtor_methodId == NULL) {
        return JNI_FALSE;
    }

    //得到object对象
    jobject jobject1 = env->NewObject(jclass1, construtor_methodId, NULL);

    //调用java 非static 方法
    jstring str = env->NewStringUTF("Call non-static method from java");
    env->CallVoidMethod(jobject1, methodId, str);

    //释放资源
    env->DeleteLocalRef(jclass1);
    env->DeleteLocalRef(jobject1);
    env->DeleteLocalRef(str);

    return env->NewStringUTF("Hello from JNI !");
}


void set(JNIEnv *env, jobject obj, jstring string) {
    const char *str = (char *) env->GetStringUTFChars(string, NULL);

    LOGE("hello %s", str);

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
        {"get", "()Ljava/lang/String;",  (void *) get},
        {"set", "(Ljava/lang/String;)V", (void *) set},
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