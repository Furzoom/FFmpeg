#include <jni.h>
#include <string>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_urlprotocolinfo(JNIEnv *env, jobject instance) {
    av_register_all();
    char info[1000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());

    return env->NewStringUTF(info);
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


}
