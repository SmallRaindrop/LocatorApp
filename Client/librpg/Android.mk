LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := rpg_static

LOCAL_MODULE_FILENAME := librpg

LOCAL_SRC_FILES := \
FileDownloadAsync.cpp \
Map/AStar.cpp \
Map/Camera.cpp \
Map/MapEffect.cpp \
Map/MapMask.cpp \
Map/MapObject.cpp \
Map/MapObjectManager.cpp \
Map/map_io.cpp \
Map/Region.cpp \
Map/RegionManager.cpp \
Map/Terrain.cpp \
Map/TileManager.cpp \
Map/TileMap.cpp \
Map/TileMapLoader.cpp \
MemoryMonitor.cpp \
ResBase.cpp \
ResPlist.cpp \
ResPlistManager.cpp \
Role/ArmatureManager.cpp \
Role/Effect.cpp \
Role/MoveMonitor.cpp \
Role/Role.cpp \
Role/RoleData.cpp \
Role/RoleEffect.cpp \
Role/RoleModel.cpp \
Role/RoleState_Idle.cpp \
Role/RoleState_Move.cpp \
Role/RoleState_Ready.cpp \
ShaderSprite.cpp \
StringConverter.cpp \
StringUtil.cpp \
VersionManager.cpp \
ZipUncompressAsync.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../cocos2d/cocos \
					$(LOCAL_PATH)/../cocos2d/cocos/2d \
					$(LOCAL_PATH)/../cocos2d/cocos/2d/render \
					$(LOCAL_PATH)/../cocos2d/cocos/base \
					$(LOCAL_PATH)/../cocos2d/cocos/ui \
					$(LOCAL_PATH)/../cocos2d/cocos/physics \
					$(LOCAL_PATH)/../cocos2d/cocos/editor-support \
					$(LOCAL_PATH)/../cocos2d/cocos/audio \
					$(LOCAL_PATH)/../cocos2d/cocos/audio/include \
					$(LOCAL_PATH)/../cocos2d/cocos/math/kazmath \
					$(LOCAL_PATH)/../cocos2d/external \
					$(LOCAL_PATH)/../cocos2d/cocos/2d/platform/android \
					$(LOCAL_PATH)/../libzm \
					$(LOCAL_PATH)/../libzm/include \
					$(LOCAL_PATH)/../third-libs/include \
					$(LOCAL_PATH)/../third-libs/include/zlib \
					$(LOCAL_PATH)/../third-libs/include/libmpg123

include $(BUILD_STATIC_LIBRARY)

