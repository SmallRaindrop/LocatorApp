#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "vld.h"
#include "GameScene/GameManager.h"
#include "VersionManager.h"
USING_NS_CC;

// google-breakpad引用
#include "client/windows/crash_generation/client_info.h"
#include "client/windows/crash_generation/crash_generation_server.h"
#include "client/windows/handler/exception_handler.h"
#include "client/windows/common/ipc_protocol.h"
#include "client/windows/tests/crash_generation_app/abstract_class.h" 
using namespace google_breakpad;
#pragma comment(lib, "breakpad_common.lib")
#pragma comment(lib, "crash_generation_client.lib")
#pragma comment(lib, "crash_generation_server.lib")
#pragma comment(lib, "exception_handler.lib")

bool onMinidumpDumped(const wchar_t* dump_path,
					  const wchar_t* minidump_id,
					  void* context,
					  EXCEPTION_POINTERS* exinfo,
					  MDRawAssertionInfo* assertion,
					  bool succeeded)
{
	LOGE("Dump generation request %s.",succeeded ? "succeeded" : "failed");
	gLog->Close();
	return succeeded;
}

void runApp()
{	
	AppDelegate app;
	Application::getInstance()->run();
	gGameManager->Exit();
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// google-breakpad引用
	HANDLE pipe_handle = NULL;
	google_breakpad::ExceptionHandler *pCrashHandler = new google_breakpad::ExceptionHandler(L"./log",
		NULL,
		onMinidumpDumped,
		NULL,
		google_breakpad::ExceptionHandler::HANDLER_ALL,
		MiniDumpNormal,
		pipe_handle,
		NULL);

	// 运行游戏
	runApp();

	if ( pCrashHandler )
	{
		delete pCrashHandler;
		pCrashHandler = NULL;
	}

	return 0;
}
