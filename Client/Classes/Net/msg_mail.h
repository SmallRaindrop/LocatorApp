
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_mail(stNetMsg& msg);
const int MSG_C2GS_Send_Mail			= 18002;
const int MSG_GS2C_Send_Mail_Result			= 18003;
const int MSG_C2GS_Read_Mail			= 18004;
const int MSG_GS2C_Read_Mail_Result			= 18005;
const int MSG_C2GS_Delete_Mail			= 18006;
const int MSG_GS2C_Delete_Mail_Result			= 18007;
const int MSG_C2GS_Delete_Mail_List			= 18008;
const int MSG_GS2C_Delete_Mail_List_Result			= 18009;
const int MSG_C2GS_Get_Attach			= 18010;
const int MSG_GS2C_Get_Attach_Result			= 18011;
const int MSG_C2GS_Get_Attach_List			= 18012;
const int MSG_GS2C_Get_Attach_List_Result			= 18013;
