@echo off

echo 开始执行Windows打包程序 ...

set SOURCE_PATH=%cd%\
set BUILD_PATH_WIN32=E:\jymf_prj\client\proj.win32\Debug.win32\

set TARGET_PATH_WIN32=E:\jymf_version\jymf-win32\
set TARGET_PATH_ANDROID=E:\jymf_prj\client\proj.android\assets\
set TARGET_PATH_IOS=E:\jymf_version\jymf-ios\


::echo 资源目录：%SOURCE_PATH%
::echo 版本目录：%TARGET_PATH%

::将最新生成的客户端及调试信息备份
xcopy /f /y %SOURCE_PATH%*.dll %TARGET_PATH_WIN32%
xcopy /f /y %SOURCE_PATH%Microsoft.DTfW.DHL.manifest %TARGET_PATH_WIN32%
xcopy /f /y %BUILD_PATH_WIN32%client.exe %TARGET_PATH_WIN32%
xcopy /f /y %BUILD_PATH_WIN32%client.pdb %TARGET_PATH_WIN32%

echo 正在打包资源 ...
mpq pack assets %TARGET_PATH_WIN32%data.mpq

::Windows
xcopy /f /y %SOURCE_PATH%localVersion.xml %TARGET_PATH_WIN32%
xcopy /f /y %SOURCE_PATH%update\*.* %TARGET_PATH_WIN32%\update\*.*

::Android
xcopy /f /y %SOURCE_PATH%localVersion.xml %TARGET_PATH_ANDROID%
xcopy /f /y %SOURCE_PATH%update\*.* %TARGET_PATH_ANDROID%\update\*.*
xcopy /f /y %TARGET_PATH_WIN32%data.mpq %TARGET_PATH_ANDROID%

::Ios
xcopy /f /y %SOURCE_PATH%localVersion.xml %TARGET_PATH_IOS%
xcopy /f /y %SOURCE_PATH%update\*.* %TARGET_PATH_IOS%\update\*.*
xcopy /f /y %TARGET_PATH_WIN32%data.mpq %TARGET_PATH_IOS%

pause