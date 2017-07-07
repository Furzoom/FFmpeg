#include <jni.h>
#include <string>
#include <sstream>
#include <iomanip>

extern "C" {
#include <libavcodec/avcodec.h>
#include "libavformat/avformat.h"
#include <libavfilter/avfilter.h>

#ifdef ANDROID
#include <android/log.h>
#define LOGE(format, ...) __android_log_print(ANDROID_LOG_ERROR, "FFmpeg", format, ##__VA_ARGS__)
#else
#define LOGE(format, ...) (void)(0)
#endif

struct URLProtocol;
JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_avformatinfo(JNIEnv *env, jobject instance) {
    std::stringstream ss;
    av_register_all();
    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);

    // Input
    while (if_temp) {
        ss << "[In ][" << std::setw(23) << if_temp->name << "]\n";
        if_temp = if_temp->next;
    }
    ss << "\n";

    // Output
    while (of_temp) {
        ss << "[Out][" << std::setw(23) << of_temp->name << "]\n";
        of_temp = of_temp->next;
    }
    return env->NewStringUTF(ss.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_avcodecinfo(JNIEnv *env, jobject instance) {
    std::stringstream ss;
    av_register_all();
    AVCodec *codec = av_codec_next(NULL);

    while (codec) {
        if (codec->decode) {
            ss << "[Dec]";
        } else {
            ss << "[Enc]";
        }

        switch (codec->type) {
            case AVMEDIA_TYPE_VIDEO:
                ss << "[Video]";
                break;
            case AVMEDIA_TYPE_AUDIO:
                ss << "[Audio]";
                break;
            default:
                ss << "[Other]";
                break;
        }
        ss << "[" << std::setw(17) << codec->name << "]\n";
        codec = codec->next;
    }
    return env->NewStringUTF(ss.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_avfilterinfo(JNIEnv *env, jobject instance) {
    std::stringstream ss;
    avfilter_register_all();
    LOGE("%s", "in native avfilterinfo");
    const AVFilter *filter = avfilter_next(NULL);
    while (filter) {
        ss << "[" << std::setw(17) << filter->name << "]\n";
        LOGE("%s", filter->name);
        filter = filter->next;
    }
    LOGE("%s", ss.str().c_str());
    return env->NewStringUTF(ss.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_configure(JNIEnv *env, jobject instance) {
    av_register_all();
    std::string info(avcodec_configuration());
    return env->NewStringUTF(info.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_urlprotocolinfo(JNIEnv *env, jobject instance) {
    std::stringstream ss;
    const char *p = NULL;
    av_register_all();
    struct URLProtocol *pup = NULL;

    // Input
    struct URLProtocol **p_temp = &pup;
    p = avio_enum_protocols((void **)p_temp, 0);
    while ((*p_temp) != NULL) {
        if (p) {
            ss << "[In ][" << std::setw(10) << p << "]\n";
        }
        p = avio_enum_protocols((void**)p_temp, 0);
    }
    ss << "\n";
    // Output
    pup = NULL;
    p = avio_enum_protocols((void**)p_temp, 1);
    while ((*p_temp) != NULL) {
        if (p) {
            ss << "[Out][" << std::setw(10) << p << "]\n";
        }
        p = avio_enum_protocols((void**)p_temp, 1);
    }

    return env->NewStringUTF(ss.str().c_str());
}

JNIEXPORT jstring JNICALL
Java_com_furzoom_lab_ffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

}
