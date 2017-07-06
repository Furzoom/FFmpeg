cmake_minimum_required(VERSION 3.4.1)

include_directories(libs/include)

find_library(log-lib log)

set(LIBS "../../../../libs")

# avutil
add_library(avutil-55
            SHARED
            IMPORTED)
set_target_properties(avutil-55
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libavutil-55.so)

# swresample
add_library(swresample-2
            SHARED
            IMPORTED)
set_target_properties(swresample-2
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libswresample-2.so)

# avcodec
add_library(avcodec-57
            SHARED
            IMPORTED)
set_target_properties(avcodec-57
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libavcodec-57.so)

# avfilter
add_library(avfilter-6
            SHARED
            IMPORTED)
set_target_properties(avfilter-6
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libavfilter-6.so)

# swscale
add_library(swscale-4
            SHARED
            IMPORTED)
set_target_properties(swscale-4
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libswscale-4.so)

# avdevice
add_library(avdevice-57
            SHARED
            IMPORTED)
set_target_properties(avdevice-57
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libavdevice-57.so)

# avformat
add_library(avformat-57
            SHARED
            IMPORTED)
set_target_properties(avformat-57
                      PROPERTIES IMPORTED_LOCATION
                      ${LIBS}/${ANDROID_ABI}/libavformat-57.so)


add_library(native-lib
            SHARED
            src/main/cpp/native-lib.cpp )

target_link_libraries(native-lib
                      avcodec-57 avdevice-57 avfilter-6 avformat-57
                      avutil-55 swresample-2 swscale-4 ${log-lib} )