################################################################################

LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)

#-----------------------------------------------------------
MTKCAM_HAVE_CAMFEATURE ?= '1'   # built-in if '1' ; otherwise not built-in
MTKCAM_HAVE_SENSOR_HAL ?= '1'   # built-in if '1' ; otherwise not built-in

#-----------------------------------------------------------
LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/hardware/camera/common/paramsmgr/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/hardware/camera/common/paramsmgr/feature/inc
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/frameworks-ext/av/include
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/hardware/camera/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_ROOT)/hardware/camera/inc/common
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc
#

#-----------------------------------------------------------
ifeq "'1'" "$(strip $(MTKCAM_HAVE_SENSOR_HAL))"
LOCAL_CFLAGS += -DMTKCAM_HAVE_SENSOR_HAL="$(MTKCAM_HAVE_SENSOR_HAL)"
endif

#-----------------------------------------------------------
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.paramsmgr.feature.common
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.paramsmgr.feature.custom
#
LOCAL_STATIC_LIBRARIES += 

#-----------------------------------------------------------
LOCAL_MODULE := libcam.paramsmgr.feature

#-----------------------------------------------------------
ifeq "'1'" "$(strip $(MTKCAM_HAVE_CAMFEATURE))"
include $(BUILD_STATIC_LIBRARY)
endif

################################################################################
#
################################################################################
ifeq "'1'" "$(strip $(MTKCAM_HAVE_CAMFEATURE))"
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))
endif

