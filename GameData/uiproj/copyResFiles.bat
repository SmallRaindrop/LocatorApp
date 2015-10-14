echo off

set CUR_PATH=%cd%
set RESFILES_PAHT=%CUR_PATH%\Resources\
set TARGET_PATH=..\debug.win32\assets\ui\

xcopy /Y /S %RESFILES_PAHT%* %TARGET_PATH% 

pause