#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , "V8Application", __VA_ARGS__)

#include "include/libplatform/libplatform.h"
#include "include/v8.h"
using namespace v8;


extern "C" {
char* test(int argc, char* argv[]) {
    char *res;
    // Initialize V8.
//    V8::InitializeICUDefaultLocation(nullptr);
//    V8::InitializeExternalStartupData(nullptr);
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    // Create a new Isolate and make it the current one.
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
            v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    LOGW("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    Isolate* isolate = Isolate::New(create_params);
    LOGW("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
    {
        Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);

        // Create a new context.
        Local<Context> context = Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);

        // Create a string containing the JavaScript source code.
        Local<String> source =
                String::NewFromUtf8(isolate, "'Hello , World!'",
                                    NewStringType::kNormal).ToLocalChecked();

        // Compile the source code.
        Local<Script> script = Script::Compile(context, source).ToLocalChecked();

        // Run the script to get the result.
        Local<Value> result = script->Run(context).ToLocalChecked();

        // Convert the result to an UTF8 string and print it.
        String::Utf8Value utf8(result);
        LOGW("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCC %s\n", *utf8);
        int length = utf8.length();
        res = new char[length + 1];
        res[length] = '\0';
        strcpy(res, *utf8);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
    delete create_params.array_buffer_allocator;
    return res;
}


jstring
Java_v8_com_v8application_MainActivity_stringFromV8(
        JNIEnv* env,
        jobject /* this */) {
    char *res = test(0, nullptr);
    return env->NewStringUTF(res);
}



}
