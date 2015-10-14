echo off

set JSON_PATH=%cd%\Json\
echo %JSON_PATH%

set TARGET_PATH=..\debug.win32\assets\ui\

for /f "tokens=*" %%i in ('dir /s /b %JSON_PATH%*.json') do (
copy %%i %TARGET_PATH%*.json
)
pause