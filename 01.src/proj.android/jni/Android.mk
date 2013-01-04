LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/DlgChallenge.cpp \
                   ../../Classes/DlgReview.cpp \
                   ../../Classes/DlgScore.cpp \
                   ../../Classes/DlgQuit.cpp \
                   ../../Classes/ExplodeScore.cpp \
                   ../../Classes/GlobalData.cpp \
                   ../../Classes/SceneLogo.cpp \
                   ../../Classes/SceneMain.cpp \
                   ../../../../../HBCommon/HBCommon.cpp \
                   ../../../../../HBCommon/android/HBCommon.cpp
                   
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
				   /Users/limin/Documents/Work/HBCommon \
				   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
