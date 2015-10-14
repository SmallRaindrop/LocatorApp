#ifndef __NetMsg_h_
#define __NetMsg_h_

#include "../commonRef.h"

#define NetMsg_Max_Size	1024*4

//add by wenziyong
#define ReadArray(msg,t,data) {uint16 len = msg.read<uint16>(); data.clear(); data.resize(len); for(int i=0;i<len;i++){Read##t(msg,data[i]);}  }
#define WriteArray(msg,t, data) { size_t len=data.size(); msg.append<uint16>((uint16)len); for(size_t i=0;i<len;i++){ Write##t(msg,data[i]); }  }

#define BEING_DEAL()	uint16 cmd = msg.command();  switch(cmd) {
#define CMD_DEAL(cmd)	case MSG_##cmd:{	pk::cmd a; Read##cmd(msg,a); return pk::On##cmd(&a);		}
#define END_DEAL()		}

#define BeginSend() stNetMsg msg_s;
#define EndSend()   if(pIOSock){ pIOSock->send_pkt(msg_s); }
//end


typedef struct stNetMsgHead
{
 	//stNetMsgHead() : _size(0),_cmd(0),_time(0){
 	//	
 	//}
 	//stNetMsgHead(uint16 s,uint16 c,uint32 t) : _size(s),_cmd(c),_time(t){
 
 	//}
 	//stNetMsgHead(const stNetMsgHead& h) : _size(h._size),_cmd(h._cmd),_time(h._time){
 
 	//}
	uint16	_size;
	uint16	_cmd;
	//uint32	_time;
}*NetMsgHeadPtr;

struct stNetMsg
{
	stNetMsg() : offset(sizeof(stNetMsgHead)){
		h._size = sizeof(stNetMsgHead);
		h._cmd = 0;
		//h._time = 0;
	}
	stNetMsg(const stNetMsgHead& head) : offset(sizeof(stNetMsgHead)){
		h._size = head._size;
		h._cmd = head._cmd;
		//h._time = head._time;
	}
	union{
		stNetMsgHead	h;
		char			buf[NetMsg_Max_Size];
	};

	int		offset;

	void header(const stNetMsgHead& head){ 
		h._size = head._size;
		h._cmd = head._cmd;
		//h._time = head._time;
	}

	stNetMsg &operator<<(uint8 value)
	{
		append<uint8>(value);
		return *this;
	}

	stNetMsg &operator<<(uint16 value)
	{
		append<uint16>(value);
		return *this;
	}

	stNetMsg &operator<<(uint32 value)
	{
		append<uint32>(value);
		return *this;
	}

	stNetMsg &operator<<(uint64 value)
	{
		append<uint64>(value);
		return *this;
	}

	// signed as in 2e complement
	stNetMsg &operator<<(int8 value)
	{
		append<int8>(value);
		return *this;
	}

	stNetMsg &operator<<(int16 value)
	{
		append<int16>(value);
		return *this;
	}

	stNetMsg &operator<<(int32 value)
	{
		append<int32>(value);
		return *this;
	}

	stNetMsg &operator<<(int64 value)
	{
		append<int64>(value);
		return *this;
	}

	// floating points
	stNetMsg &operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	stNetMsg &operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	stNetMsg &operator<<(const std::string &value)
	{
		uint16 len = value.size();
		append<uint16>(len);
		memcpy(ptr_w(),value.c_str(),len);
		h._size += len;
		
		return *this;
	}

	stNetMsg &operator<<(const char *str)
	{
		size_t len =  str ? strlen(str) : 0;
		append<uint16>((uint16)len);
		memcpy(ptr_w(),str,len);
		h._size += len;
		return *this;
	}

	//add by wenziyong
	// write array, this will hanle the array which just include simple type
	template <typename T> stNetMsg &operator<<(vector<T>  &data)
	{
		size_t len=data.size();
		append<uint16>((uint16)len);
		
		for(size_t i=0;i<len;i++)
		{ 
			*this<<data[i];
		}
		return *this;
	}
	//end

	stNetMsg &operator>>(bool &value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	stNetMsg &operator>>(uint8 &value)
	{
		value = read<uint8>();
		return *this;
	}

	stNetMsg &operator>>(uint16 &value)
	{
		value = read<uint16>();
		return *this;
	}

	stNetMsg &operator>>(uint32 &value)
	{
		value = read<uint32>();
		return *this;
	}

	stNetMsg &operator>>(uint64 &value)
	{
		value = read<uint64>();
		return *this;
	}

	//signed as in 2e complement
	stNetMsg &operator>>(int8 &value)
	{
		value = read<int8>();
		return *this;
	}

	stNetMsg &operator>>(int16 &value)
	{
		value = read<int16>();
		return *this;
	}

	stNetMsg &operator>>(int32 &value)
	{
		value = read<int32>();
		return *this;
	}

	stNetMsg &operator>>(int64 &value)
	{
		value = read<int64>();
		return *this;
	}

	stNetMsg &operator>>(float &value)
	{
		value = read<float>();
		return *this;
	}

	stNetMsg &operator>>(double &value)
	{
		value = read<double>();
		return *this;
	}

	stNetMsg &operator>>(std::string& value)
	{
		value.clear();
		uint16 len = read<uint16>();
		for(uint16 i = 0;i<len;++i )
		{
			value.push_back(read<int8>());
		}
	
		return *this;
	}
	//add by wenziyong, this will hanle the array which just include simple type
	template <typename T> stNetMsg &operator>>(vector<T>  &data)
	{
		data.clear();
		uint16 len = read<uint16>();
		data.clear(); 
		data.resize(len);

		for(int i=0;i<len;i++)
		{ 
			*this>>data[i];
		}

		return *this;
	}
	//end


	template <typename T> void append(T value)
	{
		memcpy(ptr_w(),&value,sizeof(T));
		h._size += sizeof(T);
	}

	template <typename T> T read()
	{
		T r;
		memcpy(&r,buf+offset,sizeof(T));//= *((T*)ptr_r());
		offset += sizeof(T);
		return r;
	}

	inline char*	ptr_r(){ return buf+offset;}
	inline char*	ptr_w(){ return buf+h._size;}
	inline char*	ptr(){ return buf; }
	inline char*	ptr_no_head(){ return buf+sizeof(stNetMsgHead);}

	inline uint16	size() const { return h._size; }
	inline uint16	size_no_head() const { return h._size-sizeof(stNetMsgHead); }
	inline uint16	command() const { return h._cmd; }
	//inline uint32	time() const { return h._time; }
	inline void		command(uint16 cmd){ h._cmd = cmd; }
	//inline void		time(uint32 t){ h._time = t; }
};

#endif
