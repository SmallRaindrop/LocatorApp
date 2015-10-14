call config.bat


set WORK_PATH=%cd%\..\protocol
set DES_PATH=%cd%\..\client\Classes\Net
set ERL_DES_PATH=%cd%\..\gameserver

"%JDK_PATH%\java.exe" -jar MakeProtocol.jar "%cd%" "%DES_PATH%" "%ERL_DES_PATH%"



pause