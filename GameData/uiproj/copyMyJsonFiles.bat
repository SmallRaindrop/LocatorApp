echo off

set JSON_PATH=%cd%\Json\
echo %JSON_PATH%

set TARGET_PATH=..\debug.win32\assets\ui\

copy %JSON_PATH%ChatMainUI.json %TARGET_PATH%*.json
copy %JSON_PATH%CopyEnd.json %TARGET_PATH%*.json
copy %JSON_PATH%CopyWaveEnd.json %TARGET_PATH%*.json
copy %JSON_PATH%CustomCtrls.json %TARGET_PATH%*.json
copy %JSON_PATH%MainUIFight.json %TARGET_PATH%*.json
copy %JSON_PATH%MainUINormal.json %TARGET_PATH%*.json
copy %JSON_PATH%TeamApplicationList.json %TARGET_PATH%*.json
copy %JSON_PATH%SocialUI.json %TARGET_PATH%*.json
copy %JSON_PATH%WorldMap.json %TARGET_PATH%*.json
copy %JSON_PATH%HeroInfo.json %TARGET_PATH%*.json
copy %JSON_PATH%FightPause.json %TARGET_PATH%*.json
copy %JSON_PATH%CopyDef.json %TARGET_PATH%*.json
copy %JSON_PATH%CopyDestory.json %TARGET_PATH%*.json
copy %JSON_PATH%CopyKill.json %TARGET_PATH%*.json
copy %JSON_PATH%OneStroke.json %TARGET_PATH%*.json
copy %JSON_PATH%OpenLock.json %TARGET_PATH%*.json

pause