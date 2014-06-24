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
LOCAL_STATIC_LIBRARIES += 
#
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.camadapter.scenario.shot
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.camadapter.scenario.hwscenario
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.camadapter.scenario.videosnapshot
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.vssimgtrans


LOCAL_SHARED_LIBRARIES += \
     libJpgEncPipe \

#-----------------------------------------------------------
LOCAL_MODULE := libcam.camadapter.scenario

#-----------------------------------------------------------
include $(BUILD_STATIC_LIBRARY) 


################################################################################
#
################################################################################
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))

