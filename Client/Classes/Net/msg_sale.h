
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_sale(stNetMsg& msg);
const int MSG_C2GS_PutOnItem			= 24002;
const int MSG_C2GS_PutOnGold			= 24003;
const int MSG_GS2C_PutOnGold_Result			= 24004;
const int MSG_C2GS_TakeDown			= 24005;
const int MSG_GS2C_TakeDown_Result			= 24006;
const int MSG_C2GS_Buy			= 24007;
const int MSG_GS2C_Buy			= 24008;
const int MSG_GS2C_Buy_Result			= 24009;
const int MSG_C2GS_Filter_Item			= 24010;
const int MSG_C2GS_Filter_Item_Next_Page			= 24011;
const int MSG_C2GS_Filter_Gold			= 24012;
const int MSG_C2GS_Filter_Gold_Next_Page			= 24013;
const int MSG_GS2C_Filter_Gold_Result			= 24015;
const int MSG_C2GS_Find_Item			= 24016;
const int MSG_C2GS_Find_Item_Next_Page			= 24017;
const int MSG_GS2C_Delete_Sale			= 24018;
