LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ffmpegkit
LOCAL_SRC_FILES := ffmpeg.c cmdutils.c ffmpeg_opt.c ffmpeg_filter.c metadata.c coffeecatch.c coffeejni.c myexception.cpp com_weezlabs_ffmpegkit_FFmpegKit.cpp
LOCAL_LDLIBS := -llog -ljnigraphics -lz -landroid
LOCAL_SHARED_LIBRARIES := libavdevice libavformat libavcodec libswscale libavutil libswresample libavfilter libx264 libpostproc
#local path to ffmpeg(2.6.2) should be there
LOCAL_C_INCLUDES := C:\android-ndk-r10d\sources\ffmpeg-2.6.2\

include $(BUILD_SHARED_LIBRARY)
include $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/Android.mk
