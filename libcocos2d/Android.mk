LOCAL_PATH := $(call my-dir)
$(warning $(LOCAL_PATH))

include $(CLEAR_VARS)

LOCAL_MODULE := cc_core

LOCAL_MODULE_FILENAME := libcc_core

LOCAL_ARM_MODE := arm

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
MATHNEONFILE := math/MathUtil.cpp.neon
else
MATHNEONFILE := math/MathUtil.cpp
endif

# ͷ�ļ�Ŀ¼
MY_PATHS := 2d \
            base \
            deprecated \
            math \
            platform \
            renderer

MY_PATHS := $(MY_PATHS:%=$(LOCAL_PATH)/%)

# ��ȡ��Ӧ��Դ�ļ�
MY_SRCS := $(LOCAL_PATH)/base/ccFPSImages.c
MY_SRCS += $(foreach path,$(MY_PATHS), $(wildcard $(path)/*.cpp))
MY_SRCS := $(MY_SRCS:$(LOCAL_PATH)/%=%)

MY_EXTERNAL_SRCS := \
ConvertUTF/ConvertUTFWrapper.cpp \
ConvertUTF/ConvertUTF.c \
md5/md5.c \
tinyxml2/tinyxml2.cpp \
unzip/ioapi_mem.cpp \
unzip/ioapi.cpp \
unzip/unzip.cpp \
edtaa3func/edtaa3func.cpp \
xxhash/xxhash.c \
poly2tri/common/shapes.cc \
poly2tri/sweep/advancing_front.cc \
poly2tri/sweep/cdt.cc \
poly2tri/sweep/sweep_context.cc \
poly2tri/sweep/sweep.cc \
clipper/clipper.cpp

# MATHNEONFILE �������д
LOCAL_SRC_FILES := $(MY_EXTERNAL_SRCS:%=external/%)
LOCAL_SRC_FILES += $(MY_SRCS)
LOCAL_SRC_FILES += $(MATHNEONFILE)
$(warning $(LOCAL_SRC_FILES))
# LOCAL_SRC_FILES := $(LOCAL_SRC_FILES:%=$(LOCAL_PATH)/%)

# chipmunk/include/chipmunk
# bullet/include/bullet
# nslog
# uv/include
# tinyxml2
# unzip
# xxhash
# poly2tri
# clipper
MY_EXTERNAL := \
poly2tri/common \
poly2tri/sweep

MY_PATHS := $(MY_EXTERNAL:%=$(LOCAL_PATH)/external/%)
MY_PATHS += $(LOCAL_PATH)
MY_PATHS += $(LOCAL_PATH)/.
MY_PATHS := $(LOCAL_PATH)/external



LOCAL_EXPORT_C_INCLUDES := $(MY_PATHS)
# LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)/..


LOCAL_C_INCLUDES := $(MY_PATHS)
# LOCAL_C_INCLUDES += $(LOCAL_PATH)/external/edtaa3func
# LOCAL_C_INCLUDES += $(LOCAL_PATH)/external/ConvertUTF


LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -landroid

LOCAL_STATIC_LIBRARIES := ext_freetype2
LOCAL_STATIC_LIBRARIES += ext_png
LOCAL_STATIC_LIBRARIES += ext_jpeg
LOCAL_STATIC_LIBRARIES += ext_tiff
# LOCAL_STATIC_LIBRARIES += ext_webp
# LOCAL_STATIC_LIBRARIES += ext_chipmunk 
LOCAL_STATIC_LIBRARIES += ext_zlib
# LOCAL_STATIC_LIBRARIES += ext_ssl
# LOCAL_STATIC_LIBRARIES += ext_recast
# LOCAL_STATIC_LIBRARIES += ext_bullet

LOCAL_WHOLE_STATIC_LIBRARIES := ccandroid
LOCAL_WHOLE_STATIC_LIBRARIES += cpufeatures

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CFLAGS   +=  -fexceptions

# Issues #9968
#ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
#    LOCAL_CFLAGS += -DHAVE_NEON=1
#endif

LOCAL_CPPFLAGS := -Wno-deprecated-declarations
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations

include $(BUILD_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE := cc_static
LOCAL_MODULE_FILENAME := libcc

LOCAL_STATIC_LIBRARIES := cc_core
# LOCAL_STATIC_LIBRARIES := ccs
# LOCAL_STATIC_LIBRARIES += ccb
# LOCAL_STATIC_LIBRARIES += cc3d
# LOCAL_STATIC_LIBRARIES += ccnet
LOCAL_STATIC_LIBRARIES += audio
LOCAL_STATIC_LIBRARIES += ccds
# LOCAL_STATIC_LIBRARIES += spine
LOCAL_STATIC_LIBRARIES += ccui

include $(BUILD_STATIC_LIBRARY)
#==============================================================
$(call import-module,android/cpufeatures)
$(call import-module,freetype2/prebuilt/android)
$(call import-module,platform/android)
$(call import-module,png/prebuilt/android)
$(call import-module,zlib/prebuilt/android)
$(call import-module,jpeg/prebuilt/android)
$(call import-module,tiff/prebuilt/android)
# $(call import-module,webp/prebuilt/android)
# $(call import-module,chipmunk/prebuilt/android)
# $(call import-module,3d)
$(call import-module,audio/android)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,editor-support/spine)
# $(call import-module,network)
$(call import-module,ui)
# $(call import-module,extensions)
# $(call import-module,Box2D/prebuilt/android)
# $(call import-module,bullet/prebuilt/android)
# $(call import-module,recast)
# $(call import-module,curl/prebuilt/android)
# $(call import-module,websockets/prebuilt/android)
# $(call import-module,openssl/prebuilt/android)
# $(call import-module,flatbuffers)
# $(call import-module,uv/prebuilt/android)
