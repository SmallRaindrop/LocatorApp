#include "AppDelegate.h"
#include "GameScene/GameManager.h"
//#include "Common/AudioManager.h"
#include "SimpleAudioEngine.h"
#include "Common/DataPool.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// »°µ√CPU≥ß…Ã£®Vendor£©º∞CPU…Ã±Í£®brand£©≤‚ �?
int get_cpu_vendor_brand(char* pvendor,char* pbrand)
{
	FILE* fp = fopen("E:\\cpuinfo","r");
	if ( !fp )
	{
		return -1;
	}
	char buf[256] = {0};
	while ( !feof(fp) )
	{
		fgets(buf,sizeof(buf),fp);
		if ( strstr(buf,"vendor_id\t:") )
		{
			sscanf(buf,"vendor_id\t:%[^\n]s\n",pvendor);
		}
		if ( strstr(buf,"model name\t:") )
		{
			sscanf(buf,"model name\t:%[^\n]s\n",pbrand);
			break;
		}
	}
	return 0;
}

// »°µ√CPU≥ß…Ã£®Vendor£©
//
// result: ≥…π¶ ±∑µªÿ◊÷∑˚¥Æµƒ≥§∂»£®“ª∞„Œ™12£©°£ ß∞‹ ±∑µªÿ0°£
// pvendor: Ω” ’≥ß…Ã–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
int get_cpu_vendor(char* pvendor)
{
	INT32 dwBuf[4];
	if (NULL==pvendor)    return 0;
	// Function 0: Vendor-ID and Largest Standard Function
	__cpuid(dwBuf, 0);
	// save. ±£¥ÊµΩpvendor
	*(INT32*)&pvendor[0] = dwBuf[1];    // ebx: «∞Àƒ∏ˆ◊÷∑�?
	*(INT32*)&pvendor[4] = dwBuf[3];    // edx: ÷–º‰Àƒ∏ˆ◊÷∑�?
	*(INT32*)&pvendor[8] = dwBuf[2];    // ecx: ◊Ó∫ÛÀƒ∏ˆ◊÷∑�?
	pvendor[12] = '\0';
	return 12;
}

// »°µ√CPU…Ã±Í£®Brand£©
//
// result: ≥…π¶ ±∑µªÿ◊÷∑˚¥Æµƒ≥§∂»£®“ª∞„Œ™48£©°£ ß∞‹ ±∑µªÿ0°£
// pbrand: Ω” ’…Ã±Í–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™49◊÷Ω⁄°£
int get_cpu_brand(char* pbrand)
{
	INT32 dwBuf[4];
	if (NULL==pbrand)    return 0;
	// Function 0x80000000: Largest Extended Function Number
	__cpuid(dwBuf, 0x80000000);
	if (dwBuf[0] < 0x80000004)    return 0;
	// Function 80000002h,80000003h,80000004h: Processor Brand String
	__cpuid((INT32*)&pbrand[0], 0x80000002);    // «�?6∏ˆ◊÷∑�?
	__cpuid((INT32*)&pbrand[16], 0x80000003);    // ÷–º�?6∏ˆ◊÷∑�?
	__cpuid((INT32*)&pbrand[32], 0x80000004);    // ◊Ó∫Û16∏ˆ◊÷∑�?
	pbrand[48] = '\0';
	return 48;
}

// ªÒ»°≤Ÿ◊˜œµÕ≥√˚◊÷£¨»Áwindows 7  
// ≥…π¶∑µªÿœµÕ≥–≈œ¢£¨ ß∞‹∑µªÿ Unknown System  
// ≤Œø�?https://msdn.microsoft.com/en-us/library/ms724834(v=vs.85).aspx
std::string get_os_version()  
{  
	OSVERSIONINFO osvi;  
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));  
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);  
	if ( FALSE == GetVersionEx(&osvi) ) {  
		return "Unknown System";
	}  
	OSVERSIONINFOEX osviex;
	DWORDLONG dwlConditionMask = 0;
	// Initialize the OSVERSIONINFOEX structure.
	ZeroMemory(&osviex, sizeof(OSVERSIONINFOEX));
	osviex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osviex.dwMajorVersion = osvi.dwMajorVersion;
	osviex.dwMinorVersion = osvi.dwMinorVersion;
	osviex.wProductType = VER_NT_WORKSTATION;
	// Initialize the condition mask.
	VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL );
	VER_SET_CONDITION( dwlConditionMask, VER_PRODUCT_TYPE, VER_GREATER_EQUAL );

	// Perform the test.
	BOOL ret = VerifyVersionInfo(&osviex,VER_MAJORVERSION | VER_MINORVERSION | VER_PRODUCT_TYPE,dwlConditionMask);
	if (osvi.dwMajorVersion == 5) {  
		switch (osvi.dwMinorVersion){  
		case 0: return "Windows 2000";  
		case 1: return "Windows XP";  
		case 2: return GetSystemMetrics(SM_SERVERR2) == 0 ? "Windows Server 2003":"Windows Server 2003 R2";
		default:return "Unknown System";  
		} 
	}else if (osvi.dwMajorVersion == 6) {
		switch (osvi.dwMinorVersion) {
		case 0: return ret ? "Windows Vista" : "Windows Server 2008";  
		case 1: return ret ? "Windows 7" : "Windows Server 2008 R2";  
		case 2: return ret ? "Windows 8" : "Windows Server 2012";
		case 3: return ret ? "Windows 8.1" : "Windows Server 2012 R2";
		default:return "Unknown System";  
		}
	}else if (osvi.dwMajorVersion == 10) {
		switch (osvi.dwMinorVersion) {  
		case 0: return ret ? "Windows 10" : "Windows Server 2016 Technical Preview";
		default:return "Unknown System";  
		}  
	}
	else
	{
		return "Unknown System";
	}
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#define CLASS_NAME "zm/game/AClient/AppActivity"

// result: ≥…π¶ ±∑µªÿ◊÷∑˚¥Æµƒ≥§∂»£®“ª∞„Œ™12£©°£ ß∞‹ ±∑µªÿ0°£
// pvendor: Ω” ’≥ß…Ã–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
// pbrand: Ω” ’…Ã±Í–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
int get_cpu_info(char* vendor,char* brand)
{
	FILE* fp = fopen("/proc/cpuinfo","r");
	if ( !fp )
	{
		CCLOG("---------open /proc/cpuinfo failed.--------------");
		return -1;
	}
	char buf[256] = {0};
	while ( !feof(fp) )
	{
		fgets(buf,sizeof(buf),fp);
		CCLOG("---------line:%s--------------",buf);
		if ( strstr(buf,"Processor\t:") )
		{
			sscanf(buf,"Processor\t:%[^\n]s\n",brand);
		}
		if ( strstr(buf,"vendor_id\t:") )
		{
			sscanf(buf,"vendor_id\t:%[^\n]s\n",vendor);
		}
		if ( strstr(buf,"model name\t:") )
		{
			sscanf(buf,"model name\t:%[^\n]s\n",brand);
		}
	}
	return 0;
}

void get_machine_info(string& vendor,string& num,string& os,string& abi)
{
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDeviceVendor", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		vendor = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDeviceModel", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		num = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDeviceOS", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		os = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCpuABI", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		abi = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
		t.env->DeleteLocalRef(t.classID);
	}
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
// result: ≥…π¶ ±∑µªÿ◊÷∑˚¥Æµƒ≥§∂»£®“ª∞„Œ™12£©°£ ß∞‹ ±∑µªÿ0°£
// pvendor: Ω” ’≥ß…Ã–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
// pbrand: Ω” ’…Ã±Í–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
int get_cpu_info(char* vendor,char* brand)
{
    FILE* fp = fopen("/proc/cpuinfo","r");
    if ( !fp )
    {
        CCLOG("---------open /proc/cpuinfo failed.--------------");
        return -1;
    }
    char buf[256] = {0};
    while ( !feof(fp) )
    {
        fgets(buf,sizeof(buf),fp);
        CCLOG("---------line:%s--------------",buf);
        if ( strstr(buf,"Processor\t:") )
        {
            sscanf(buf,"Processor\t:%[^\n]s\n",brand);
        }
        if ( strstr(buf,"vendor_id\t:") )
        {
            sscanf(buf,"vendor_id\t:%[^\n]s\n",vendor);
        }
        if ( strstr(buf,"model name\t:") )
        {
            sscanf(buf,"model name\t:%[^\n]s\n",brand);
        }
    }
    return 0;
}
#endif

#define SCREEN_WIDTH	1334
#define SCREEN_HEIGHT	750

AppDelegate::AppDelegate() {
	initDeviceInfo();
}

AppDelegate::~AppDelegate() 
{
	
}

void AppDelegate::initDeviceInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// ªÒ»°ª˙∆˜–≈œ¢
	char buff[64] = "";
	get_cpu_vendor_brand(buff,buff);
	get_cpu_vendor(buff);
	gGameManager->GetMachineInfo()._cpu_vendor = buff;
	get_cpu_brand(buff);
	gGameManager->GetMachineInfo()._cpu_name = buff;
	gGameManager->GetMachineInfo()._os = get_os_version();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// »°µ√CPU≥ß…Ã£®Vendor£©º∞CPU…Ã±Í£®brand£©
	char cpu_vendor[128] = "";
	char cpu_name[128] = "";
	get_cpu_info(cpu_vendor,cpu_name);
	gGameManager->GetMachineInfo()._cpu_vendor = (cpu_vendor[0] == '\0' ? "Unknown" : cpu_vendor);
	gGameManager->GetMachineInfo()._cpu_name = (cpu_name[0] == '\0' ? "Unknown" : cpu_name);
	CCLOG("---------cpu_vendor=%s cpu_name=%s--------------",cpu_vendor,cpu_name);
	string vendor,num,os,abi;
	get_machine_info(vendor,num,os,abi);
	gGameManager->GetMachineInfo()._vendor = vendor;
	gGameManager->GetMachineInfo()._num = num;
	gGameManager->GetMachineInfo()._os = os;
	gGameManager->GetMachineInfo()._cpu_abi = abi;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        UIDevice *device = [[UIDevice alloc] int];
//        NSString *name = device.name;		//获取设备所有者的名称
//        NSString *model = [NSString stringWithFormat:@"%@,%@", device.model, device.localizedModel ];;    //获取设备的类�?+ //获取本地化版�?
//        NSString* os = [NSString stringWithFormat:@"%@,%@", device.systemName, device.systemVersion ];    //获取当前运行的系�?+ //获取当前系统的版�?
    
        gGameManager->GetMachineInfo()._vendor = "apple";
        gGameManager->GetMachineInfo()._num = "iphone";
        gGameManager->GetMachineInfo()._os = "ios";
    
        char cpu_vendor[128] = "";
        char cpu_name[128] = "";
        get_cpu_info(cpu_vendor,cpu_name);
        gGameManager->GetMachineInfo()._cpu_vendor = (cpu_vendor[0] == '\0' ? "Unknown" : cpu_vendor);
        gGameManager->GetMachineInfo()._cpu_name = (cpu_name[0] == '\0' ? "Unknown" : cpu_name);
#endif
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* pDirector = gDirector;
    
    GLView* pGLView = pDirector->getOpenGLView();
    if( NULL == pGLView )
    {
        pGLView = GLView::create("game(v1.0.0.0)---test for inner");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        pGLView->setFrameSize(1334, 750);
#endif
        
        pDirector->setOpenGLView(pGLView);
    }
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // resolution information  
    Size size;  
    size= pDirector->getWinSize();
	log("***IDONG: Director getWinSize:w=%f,h=%f",size.width,size.height);  

	size = pDirector->getWinSizeInPixels();  
	log("***IDONG: Director getWinSizeInPixels:w=%f,h=%f",size.width,size.height);  

	size = pDirector->getVisibleSize();  
	log("***IDONG: Director getVisibleSize:w=%f,h=%f",size.width,size.height);  

	Point point = pDirector->getVisibleOrigin();  
	log("***IDONG: Director getVisibleOrigin:x=%f,y=%f",point.x,point.y);  


	log("***IDONG: Director BS: getContentScaleFactor: scaleFactor=%f",pDirector->getContentScaleFactor());  

	auto framsize = pGLView->getFrameSize();
	auto dwinsize = pDirector->getWinSize();
	auto designsize = Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	auto widthRate = framsize.width/designsize.width;
	auto heightRate = framsize.height/designsize.height;

	auto  resolutionRate = 1.f;
	if(widthRate > heightRate) 
	{
		pGLView->setDesignResolutionSize(designsize.width,
		 designsize.height*heightRate/widthRate, ResolutionPolicy::NO_BORDER);
		 resolutionRate = heightRate/widthRate;
	}
	else
	{
		pGLView->setDesignResolutionSize(designsize.width*widthRate/heightRate, designsize.height,
		 ResolutionPolicy::NO_BORDER);
		 resolutionRate = widthRate/heightRate;
	}

	//pGLView->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::FIXED_HEIGHT);

	log("***IDONG:/n");  
	log("***IDONG: Director AS: getContentScaleFactor: scaleFactor=%f",pDirector->getContentScaleFactor());  

	size= pDirector->getWinSize();  
	log("***IDONG: Director getWinSize:w=%f,h=%f",size.width,size.height);  

	size = pDirector->getWinSizeInPixels();  
	log("***IDONG: Director getWinSizeInPixels:w=%f,h=%f",size.width,size.height);  

	size = pDirector->getVisibleSize();  
	log("***IDONG: Director getVisibleSize:w=%f,h=%f",size.width,size.height);  

	point = pDirector->getVisibleOrigin();  
	log("***IDONG: Director getVisibleOrigin:x=%f,y=%f",point.x,point.y);  

	// ‘ˆº”À—À˜¬∑æ∂
	gFileUtils->addSearchPath("assets");

	// …Ë÷√◊ ‘¥ƒø¬�?
	// ≥ı ºªØ◊ ‘¥ƒø¬�?dumpŒƒº˛…˙≥…ƒø¬�?
	string logfile = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	gGameManager->SetResourceRoot("/mnt/sdcard/com.zm.mszb/");
	gGameManager->CreateDirectory(gGameManager->GetResourceRoot());
	gGameManager->CreateDirectory(gGameManager->GetLogPath());
	logfile = gGameManager->GetLogPath()+"/log.txt";
	gLog->Open(logfile.c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	gGameManager->SetResourceRoot("");
	gGameManager->CreateDirectory(gGameManager->GetResourceRoot());
	gGameManager->CreateDirectory(gGameManager->GetLogPath());
	logfile = gGameManager->GetLogPath()+"/log.txt";
	gLog->Open(logfile.c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	gGameManager->SetResourceRoot(gFileUtils->getWritablePath());
	gGameManager->CreateDirectory(gGameManager->GetResourceRoot());
	gGameManager->CreateDirectory(gGameManager->GetLogPath());
	logfile = gGameManager->GetLogPath()+"/log.txt";
	gLog->Open(logfile.c_str());
#endif
	gGameManager->LogMachineInfo();
	// ø™ º∏¸–�?
	gGameManager->Start();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
