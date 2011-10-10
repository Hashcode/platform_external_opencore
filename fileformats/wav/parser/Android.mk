LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/pvwavfileparser.cpp \
	gsm-1.0-pl13/src/add.c \
	gsm-1.0-pl13/src/decode.c \
	gsm-1.0-pl13/src/long_term.c \
	gsm-1.0-pl13/src/lpc.c \
	gsm-1.0-pl13/src/preprocess.c \
	gsm-1.0-pl13/src/rpe.c \
	gsm-1.0-pl13/src/gsm_destroy.c \
	gsm-1.0-pl13/src/gsm_create.c \
	gsm-1.0-pl13/src/gsm_decode.c \
	gsm-1.0-pl13/src/gsm_option.c \
	gsm-1.0-pl13/src/short_term.c \
	gsm-1.0-pl13/src/table.c


LOCAL_MODULE := libpvwav

#-DSASR says that we have signed arithmetic shift operations.  (-1 >> 1 == -1)
#-DWAV49 says that we're using WAV file compatible format for the codec
LOCAL_CFLAGS :=  $(PV_CFLAGS) -DSASR -DWAV49


LOCAL_STATIC_LIBRARIES := 

LOCAL_SHARED_LIBRARIES := 

LOCAL_C_INCLUDES := \
	$(PV_TOP)/fileformats/wav/parser/src \
	$(PV_TOP)/fileformats/wav/parser/include \
	$(PV_TOP)/fileformats/wav/parser/gsm-1.0-pl13/inc \
	$(PV_INCLUDES)

LOCAL_COPY_HEADERS_TO := $(PV_COPY_HEADERS_TO)

LOCAL_COPY_HEADERS := \
	include/pvwavfileparser.h

include $(BUILD_STATIC_LIBRARY)
