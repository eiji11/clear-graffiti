LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/plugin/publish)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ImageIOAndroid.cpp \
				   PhotoCaptureAndroid.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/custom_nodes/VandalNode.cpp \
                   ../../Classes/game/Game.cpp \
                   ../../Classes/game/Player.cpp \
                   ../../Classes/game/Vandal.cpp \
                   ../../Classes/game/VandalCell.cpp \
				   ../../Classes/managers_caches/AssortedUtils.cpp \
				   ../../Classes/managers_caches/EventCustomMapped.cpp \
				   ../../Classes/managers_caches/ObserverManager.cpp \
				   ../../Classes/managers_caches/UILockManager.cpp \
                   ../../Classes/nodes_layers_scenes/AboutMenu.cpp \
                   ../../Classes/nodes_layers_scenes/AboutEquipments.cpp \
                   ../../Classes/nodes_layers_scenes/AboutPage.cpp \
                   ../../Classes/nodes_layers_scenes/AlertBox.cpp \
                   ../../Classes/nodes_layers_scenes/ComicsScene.cpp \
                   ../../Classes/nodes_layers_scenes/ConfirmExitDialog.cpp \
                   ../../Classes/nodes_layers_scenes/ChapterCover.cpp \
                   ../../Classes/nodes_layers_scenes/GameScene.cpp \
                   ../../Classes/nodes_layers_scenes/HowToPlayScene.cpp \
                   ../../Classes/nodes_layers_scenes/InGameItemSelectorDialog.cpp \
                   ../../Classes/nodes_layers_scenes/LeaderBoardDialog.cpp \
                   ../../Classes/nodes_layers_scenes/LeaderBoardDialogEntry.cpp \
                   ../../Classes/nodes_layers_scenes/LevelSelectDialog.cpp \
                   ../../Classes/nodes_layers_scenes/MainMenu.cpp \
                   ../../Classes/nodes_layers_scenes/PauseDialog.cpp \
                   ../../Classes/nodes_layers_scenes/PlayMenu.cpp \
                   ../../Classes/nodes_layers_scenes/PostGame.cpp \
                   ../../Classes/nodes_layers_scenes/PreGame.cpp \
                   ../../Classes/nodes_layers_scenes/SettingsDialog.cpp \
                   ../../Classes/nodes_layers_scenes/ShopDialog.cpp \
                   ../../Classes/nodes_layers_scenes/ShopDialogEntry.cpp \
                   ../../Classes/utils/GeneralUtils.cpp
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../libs \
$(LOCAL_PATH)/../../cocos2d/external

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += spritebuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,extensions)
$(call import-module,editor-support/spritebuilder)
$(call import-module,editor-support/cocostudio)
$(call import-module,plugin/protocols/proj.android/jni)

# $(call import-module,network)
