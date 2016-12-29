#include <jni.h>
#include <string>

extern "C"
jstring
Java_v8_com_v8application_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
