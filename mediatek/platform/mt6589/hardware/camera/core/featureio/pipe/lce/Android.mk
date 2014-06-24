LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    lce_hal.cpp
  
LOCAL_C_INCLUDES:= \
    $(TOP)/bionic \
    $(TOP)/external/stlport/stlport \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/liblce \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/drv/inc \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/scenario \
    $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \

LOCAL_MODULE := libfeatureiopipe_lce

include $(BUILD_STATIC_LIBRARY)
