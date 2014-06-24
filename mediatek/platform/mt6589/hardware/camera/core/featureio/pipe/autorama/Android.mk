LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    autorama_hal_base.cpp \
    autorama/autorama_hal.cpp \
  
LOCAL_C_INCLUDES:= \
	 $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/autorama/autorama \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libautopano \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libmotion \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \

LOCAL_MODULE := libcam.featureio.pipe.panorama

include $(BUILD_STATIC_LIBRARY)
