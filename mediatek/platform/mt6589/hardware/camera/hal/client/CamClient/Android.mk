################################################################################
#
################################################################################

LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)

#-----------------------------------------------------------
MTKCAM_HAVE_RECORD_CLIENT           ?= '1'  # built-in if '1' ; otherwise not built-in
MTKCAM_HAVE_FD_CLIENT               ?= '1'  # built-in if '1' ; otherwise not built-in
MTKCAM_HAVE_PREVIEWFEATURE_CLIENT   ?= '1'  # built-in if '1' ; otherwise not built-in

#-----------------------------------------------------------
LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(LOCAL_PATH)/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/frameworks-ext/av/include
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/camera/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/camera/inc/common
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/camera/client/CamClient/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common

#-----------------------------------------------------------
LOCAL_CFLAGS += -DMTKCAM_HAVE_RECORD_CLIENT="$(MTKCAM_HAVE_RECORD_CLIENT)"
LOCAL_CFLAGS += -DMTKCAM_HAVE_FD_CLIENT="$(MTKCAM_HAVE_FD_CLIENT)"
LOCAL_CFLAGS += -DMTKCAM_HAVE_PREVIEWFEATURE_CLIENT="$(MTKCAM_HAVE_PREVIEWFEATURE_CLIENT)"

#-----------------------------------------------------------
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.client.camclient.common
#
ifeq "'1'" "$(strip $(MTKCAM_HAVE_RECORD_CLIENT))"
    LOCAL_WHOLE_STATIC_LIBRARIES += libcam.client.camclient.record
endif
#
ifeq "'1'" "$(strip $(MTKCAM_HAVE_FD_CLIENT))"
    LOCAL_WHOLE_STATIC_LIBRARIES += libcam.client.camclient.fd
endif
#
ifeq "'1'" "$(strip $(MTKCAM_HAVE_PREVIEWFEATURE_CLIENT))"
    LOCAL_WHOLE_STATIC_LIBRARIES += libcam.client.camclient.featurebase
endif
#
LOCAL_STATIC_LIBRARIES += 

#-----------------------------------------------------------
LOCAL_MODULE := libcam.client.camclient

#-----------------------------------------------------------
include $(BUILD_STATIC_LIBRARY)


################################################################################
#
################################################################################
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))

