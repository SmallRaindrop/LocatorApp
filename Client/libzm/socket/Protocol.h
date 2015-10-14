#ifndef __Protocol_h_
#define __Protocol_h_

#include "NetMsg.h"

struct st_Cmd_Null
{
	void read(stNetMsg& msg){}
	void write(stNetMsg& msg){ msg.command(1000); }
};

struct st_Cmd_Test
{
	uint8	a;
	uint16	b;
	uint32	c;
	uint64	d;
	string	str;

	void read(stNetMsg& msg)
	{
		msg >> a;
		msg >> b;
		msg >> c;
		msg >> d;
		msg >> str;
	}

	void write(stNetMsg& msg)
	{
		msg.command(1002);
		msg << a;
		msg << b;
		msg << c;
		msg << d;
		msg << str;
	}
};

#endif