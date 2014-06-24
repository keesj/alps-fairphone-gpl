LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    hdr_hal_base.cpp \
    hdr/hdr_hal.cpp \
  
LOCAL_C_INCLUDES:= \
	 $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/hdr/hdr \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libhdr \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libmav \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \

LOCAL_MODULE := libfeatureiopipe_hdr

include $(BUILD_STATIC_LIBRARY)
