################################################################################
#
################################################################################

LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)

#-----------------------------------------------------------
LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += 

#-----------------------------------------------------------
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.utils.common
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.utils.platform
#
LOCAL_STATIC_LIBRARIES += 

#-----------------------------------------------------------
#LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcamera_client
#
ifeq "yes" "$(strip $(MTK_MMPROFILE_SUPPORT))"
LOCAL_SHARED_LIBRARIES += libmmprofile
endif

#-----------------------------------------------------------
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libcam.utils

#-----------------------------------------------------------
include $(BUILD_SHARED_LIBRARY)


################################################################################
#
################################################################################
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))

