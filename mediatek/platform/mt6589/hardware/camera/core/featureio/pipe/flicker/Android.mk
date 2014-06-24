LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES += \
    flicker_hal.cpp
  
LOCAL_C_INCLUDES:= \
    $(TOP)/bionic \
    $(TOP)/external/stlport/stlport \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/algorithm/libflicker \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/drv/imgsensor \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/drv \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/custom/hal/inc \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/custom/hal/inc/aaa \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/custom/hal/inc/isp_tuning \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/aaa/isp_mgr \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/aaa/ae_mgr \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/aaa/af_mgr \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/drv/inc \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/pipe/aaa/ispdrv_mgr \
    $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc/aaa \
    $(TOP)/mediatek/custom/common/kernel/imgsensor/inc \
    $(TOP)/mediatek/custom/mt6589/hal/camera/inc \
    $(TOP)/mediatek/custom/mt6589/hal/inc \
    $(TOP)/mediatek/custom/mt6589/hal/inc/debug_exif/aaa \

    
LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \




    
LOCAL_MODULE := libfeatureiopipe_flk

include $(BUILD_STATIC_LIBRARY)
