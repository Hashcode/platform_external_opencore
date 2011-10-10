LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

MOT_PV_TOP := $(LOCAL_PATH)/../../../motorola/external/opencore

LOCAL_SRC_FILES := \
    metadatadriver.cpp \
    playerdriver.cpp \
    thread_init.cpp \
    pvmediascanner.cpp \
    android_surface_output.cpp \
    android_audio_output.cpp \
    android_audio_stream.cpp \
    android_audio_mio.cpp \
    android_audio_output_threadsafe_callbacks.cpp \
    extension_handler_registry.cpp \
    PVPlayerExtHandler.cpp \
    android_audio_raw_output.cpp

LOCAL_CFLAGS := $(PV_CFLAGS_MINUS_VISIBILITY)
LOCAL_C_INCLUDES := $(PV_INCLUDES) \
    $(PV_TOP)/engines/common/include \
    $(PV_TOP)/fileformats/mp4/parser/include \
    $(PV_TOP)/pvmi/media_io/pvmiofileoutput/include \
    $(PV_TOP)/nodes/pvmediaoutputnode/include \
    $(PV_TOP)/nodes/pvmediainputnode/include \
    $(PV_TOP)/nodes/pvmp4ffcomposernode/include \
    $(PV_TOP)/engines/player/include \
    $(PV_TOP)/nodes/common/include \
    $(PV_TOP)/fileformats/pvx/parser/include \
    motorola/frameworks/base/media/metainfo/utility \
	$(PV_TOP)/nodes/pvprotocolenginenode/download_protocols/common/src \
    motorola/external/opencore \
    libs/drm/mobile1/include \
    include/graphics \
    external/skia/include/corecg \
    $(call include-path-for, graphics corecg) \
    external/tremolo/Tremolo

LOCAL_MODULE := libandroidpv

LOCAL_SHARED_LIBRARIES := libui libutils libbinder libsurfaceflinger_client libcamera_client
LOCAL_STATIC_LIBRARIES := libosclbase libosclerror libosclmemory libosclutil

LOCAL_LDLIBS +=

include $(BUILD_STATIC_LIBRARY)

