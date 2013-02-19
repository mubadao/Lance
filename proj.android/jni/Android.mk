LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Common/BuffManager.cpp \
                   ../../Classes/Common/ChanceDecision.cpp \
                   ../../Classes/Common/DataType.cpp \
                   ../../Classes/Common/Devourer.cpp \
                   ../../Classes/Common/ExplodeScore.cpp \
                   ../../Classes/Common/GlobalData.cpp \
                   ../../Classes/Common/InvaderBase.cpp \
                   ../../Classes/Common/InvaderManager.cpp \
                   ../../Classes/Common/SpellSlot.cpp \
                   ../../Classes/Layer/BuyItem.cpp \
                   ../../Classes/Layer/DlgReview.cpp \
                   ../../Classes/Layer/LayerBuy.cpp \
                   ../../Classes/Layer/LayerGame.cpp \
                   ../../Classes/Layer/LayerHelp.cpp \
                   ../../Classes/Layer/LayerMain.cpp \
                   ../../Classes/Layer/LayerMissionClear.cpp \
                   ../../Classes/Layer/LayerPause.cpp \
                   ../../Classes/Layer/LayerResult.cpp \
                   ../../Classes/Layer/LayerStore.cpp \
                   ../../Classes/Layer/NextMission.cpp \
                   ../../Classes/Layer/StoreItem.cpp \
                   ../../Classes/Layer/TableViewStore.cpp \
                   ../../Classes/Layer/TotalGold.cpp \
                   ../../Classes/Layer/DlgQuit.cpp \
                   ../../../../../HBCommon/HBCommon.cpp \
                   ../../../../../HBCommon/android/HBCommon_Android.cpp
                   
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/Common \
                    $(LOCAL_PATH)/../../Classes/Layer \
			  $(LOCAL_PATH)/hellocpp \
			  /Users/limin/Documents/Work/HBCommon \
				   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
LOCAL_CFLAGS := -DCOCOS2D_DEBUG=0 -DNDEBUG
LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=0 -DNDEBUG
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
