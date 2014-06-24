LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    3DF_hal_base.cpp \
    mav/mav_hal.cpp \
    pano3d/pano3d_hal.cpp

LOCAL_C_INCLUDES:= \
	 $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/3Dfeature/mav \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/3Dfeature/pano3d \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libcore \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libmav \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libwarp \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libmotion \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libpano3d \
	 $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \

LOCAL_MODULE := libcam.featureio.pipe.3DFeature

include $(BUILD_STATIC_LIBRARY)
