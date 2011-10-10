LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/pvmf_omx_videodec_factory.cpp \
 	src/pvmf_omx_videodec_node.cpp


LOCAL_MODULE := libpvomxvideodecnode

LOCAL_CFLAGS :=  $(PV_CFLAGS)

#BEGIN Motorola, p40005, 3-08-2010, IKMAP-7192
ifndef OMX_TI_OMAP_TIER_LEVEL
    LOCAL_CFLAGS += -DOMX_TI_MAX_RESOLUTION=0 # play everything
endif
ifeq ($(OMX_TI_OMAP_TIER_LEVEL),30)
    LOCAL_CFLAGS += -DOMX_TI_MAX_RESOLUTION=0 # play everything
endif
ifeq ($(OMX_TI_OMAP_TIER_LEVEL),20)
    LOCAL_CFLAGS += -DOMX_TI_MAX_RESOLUTION=307200 # VGA resolution 640x480
endif
ifeq ($(OMX_TI_OMAP_TIER_LEVEL),10)
    LOCAL_CFLAGS += -DOMX_TI_MAX_RESOLUTION=153600 # HVGA resolution 480x320
endif
# END IKMAP-7192

LOCAL_STATIC_LIBRARIES := 

LOCAL_SHARED_LIBRARIES := 

LOCAL_C_INCLUDES := \
	$(PV_TOP)/nodes/pvomxvideodecnode/src \
 	$(PV_TOP)/nodes/pvomxvideodecnode/include \
 	$(PV_TOP)/extern_libs_v2/khronos/openmax/include \
 	$(PV_TOP)/codecs_v2/video/wmv_vc1/dec/src \
 	$(PV_TOP)/baselibs/threadsafe_callback_ao/src \
 	$(PV_TOP)/nodes/pvomxbasedecnode/include \
 	$(PV_TOP)/nodes/pvomxbasedecnode/src \
 	$(PV_INCLUDES)

LOCAL_COPY_HEADERS_TO := $(PV_COPY_HEADERS_TO)

LOCAL_COPY_HEADERS := \
 	include/pvmf_omx_videodec_factory.h

include $(BUILD_STATIC_LIBRARY)
