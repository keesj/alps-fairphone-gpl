LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    fd_hal_base.cpp \
    fdvt_hal.cpp \
  
LOCAL_C_INCLUDES:= \
	 $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/fdft_hal \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libfdft \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \
	 $(TOP)/$(MTK_ROOT)/hardware/dpframework/inc \

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \

LOCAL_MODULE := libfeatureiopipe_fdft

include $(BUILD_STATIC_LIBRARY)
