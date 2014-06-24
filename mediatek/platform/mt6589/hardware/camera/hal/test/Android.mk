################################################################################
#
################################################################################
LOCAL_PATH := $(call my-dir)

################################################################################
# camera test
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/frameworks-ext/av/include \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc/drv \
                    $(MTK_PATH_CUSTOM)/hal/inc/aaa \
                    $(MTK_PATH_CUSTOM)/hal/inc/isp_tuning \
                    $(MTK_PATH_CUSTOM)/hal/inc/camera_feature \
                    $(MTK_PATH_CUSTOM)/hal/inc/debug_exif/aaa \
                    $(MTK_PATH_CUSTOM)/hal/inc \
                    $(MTK_PATH_CUSTOM)/hal/camera \
                    $(MTK_PATH_CUSTOM)/kernel/imgsensor/inc \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc/drv \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc/common \
                    $(MTK_PATH_PLATFORM)/hardware/camera/inc/drv \
                    $(MTK_PATH_PLATFORM)/hardware/camera/core/drv/imgsensor \
                    $(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/inc

#-----------------------------------------------------------
LOCAL_MODULE := camtest
#LOCAL_MODULE_TAGS := test
LOCAL_MODULE_TAGS := eng
LOCAL_PRELINK_MODULE := false

LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES += libgui
LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES += libcamera_client
LOCAL_SHARED_LIBRARIES += libfeatureio

include $(BUILD_EXECUTABLE)
#-------------------------------------------------------------------------------
