#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteItemLink(stNetMsg& msg,ItemLink& value)
{
	msg << value.bagType;
	msg << value.itemId;
}
void ReadItemLink(stNetMsg& msg,ItemLink& value)
{
	msg >> value.bagType;
	msg >> value.itemId;
}
void WriteC2GS_Chat(stNetMsg& msg,C2GS_Chat& value)
{
	msg << value.channelId;
	msg << value.message;
	WriteArray(msg,ItemLink,value.vec);
	msg.command(MSG_C2GS_Chat);
}
void C2GS_Chat::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Chat(msg_s,*this);
	EndSend();
}
void ReadC2GS_Chat(stNetMsg& msg,C2GS_Chat& value)
{
	msg >> value.channelId;
	msg >> value.message;
	ReadArray(msg,ItemLink,value.vec);
}
void WriteC2GS_Private_Chat(stNetMsg& msg,C2GS_Private_Chat& value)
{
	msg << value.playerId;
	msg << value.message;
	msg.command(MSG_C2GS_Private_Chat);
}
void C2GS_Private_Chat::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Private_Chat(msg_s,*this);
	EndSend();
}
void ReadC2GS_Private_Chat(stNetMsg& msg,C2GS_Private_Chat& value)
{
	msg >> value.playerId;
	msg >> value.message;
}
void WriteGS2C_Monster_ChatMsg(stNetMsg& msg,GS2C_Monster_ChatMsg& value)
{
	msg << value.monsterId;
	msg << value.strId;
	msg << value.displayMs;
	msg.command(MSG_GS2C_Monster_ChatMsg);
}
void ReadGS2C_Monster_ChatMsg(stNetMsg& msg,GS2C_Monster_ChatMsg& value)
{
	msg >> value.monsterId;
	msg >> value.strId;
	msg >> value.displayMs;
}

};

