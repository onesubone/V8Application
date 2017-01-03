#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , "V8Application", __VA_ARGS__)

#include "include/libplatform/libplatform.h"
#include "include/v8.h"
#include "TestFunctionTemplate.cpp"
using namespace v8;


extern "C" {

jstring
Java_v8_com_v8application_MainActivity_stringFromV8(
        JNIEnv* env,
        jobject /* this */) {
    char *res = run();
    return env->NewStringUTF(res);
}



}
