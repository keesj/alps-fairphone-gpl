ifeq ($(MTK_PLATFORM),$(filter $(MTK_PLATFORM),MT6589))

LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    bandwidth_control.cpp \
    bandwidth_control_port.cpp
    

LOCAL_C_INCLUDES:= \
  $(MTK_PATH_SOURCE)/hardware/bwc/inc \
  $(TOP)/$(MTK_PATH_PLATFORM)/kernel/core/include/mach \


LOCAL_SHARED_LIBRARIES := \
     libcutils \
     liblog \
     libnetutils
 
 
LOCAL_MODULE := libbwc

LOCAL_MODULE_TAGS := eng

#LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
#include $(call all-makefiles-under,$(LOCAL_PATH))


endif


