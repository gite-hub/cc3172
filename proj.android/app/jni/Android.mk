LOCAL_PATH := $(call my-dir)

# 我加的
# LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(CLEAR_VARS)

LOCAL_MODULE := langxiyou_shared

LOCAL_MODULE_FILENAME := liblangxiyou

LOCAL_ARM_MODE := arm


# 根目录
MY_ROOT := $(LOCAL_PATH)/../../../
MY_CUT := proj.android/app/jni
# 前面有个空格?
MY_ROOT := $(subst $(MY_CUT),,$(LOCAL_PATH))
$(warning $(MY_ROOT))


# 头文件目录 注意斜杠换行对注释也有效
MY_PATHS := classes \
            libcc \
            libtxt \
            libpro \
            libutil \
            libui
# $(MY_ROOT)../.. \
# $(MY_ROOT)../../extensions \
# $(MY_ROOT)../../cocos/editor-support
$(warning $(MY_PATHS))
MY_PATHS := $(MY_PATHS:%=$(MY_ROOT)%)

# 获取相应的源文件
MY_SRCS := main.cpp
MY_SRCS += $(foreach path,$(MY_PATHS), $(wildcard $(path)/*.cpp))
# jpeg .c文件
# MY_SRCS += $(foreach path,$(MY_ROOT)libjpeg, $(wildcard $(path)/*.c))
# 不用相对用绝对路径试试
$(warning $(MY_SRCS:$(MY_ROOT)%=%))


# 赋值给NDK编译系统
LOCAL_C_INCLUDES := $(MY_PATHS)
LOCAL_C_INCLUDES += $(MY_ROOT)libcocos2d
# LOCAL_C_INCLUDES += $(MY_ROOT)..
LOCAL_SRC_FILES  := $(MY_SRCS)


LOCAL_STATIC_LIBRARIES := cc_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, libcocos2d)
# $(call import-add-path, ../../../../../cocos)
# $(call import-module, ../../../../../cocos)



# 源文件后缀名
# MY_FILES_SUFFIX := %.cpp%.c

# 递归遍历目录下的所有的文件
# rwildcard=$(wildcard$1$2)$(foreach d,$(wildcard$1*),$(call rwildcard,$d/,$2))

# 获取相应的源文件
# MY_CPP_PATH := $(LOCAL_PATH)/
# MY_ALL_FILES := $(foreach src_path,$(MY_PATHS),$(call rwildcard,$(src_path),*.*))
# MY_ALL_FILES := $(MY_ALL_FILES:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
# MY_SRCS  := $(filter$(MY_FILES_SUFFIX),$(MY_ALL_FILES))
# MY_SRCS  := $(MY_SRCS:$(LOCAL_PATH)/%=%)


# 去除字串的重复单词
# define uniq =
#  $(eval seen :=)
#  $(foreach _,$1,$(if$(filter$_,${seen}),,$(eval seen += $_)))
#  ${seen}
# endef


# 递归遍历获取所有目录
# MY_ALL_DIRS := $(dir$(foreach src_path,$(MY_PATHS),$(call rwildcard,$(src_path),*/)))
# MY_ALL_DIRS := $(call uniq,$(MY_ALL_DIRS))


# 赋值给NDK编译系统
# LOCAL_SRC_FILES  := $(MY_SRCS)
# LOCAL_C_INCLUDES := $(MY_ALL_DIRS)